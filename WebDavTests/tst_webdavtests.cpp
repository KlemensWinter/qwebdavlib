#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QDirIterator>
#include <qwebdav.h>

namespace {
void emptyLocalRoot(const QString& localRoot) {
    QDirIterator iter(localRoot, QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot|QDir::NoSymLinks);
    while(iter.hasNext()) {
        iter.next();
        if(iter.fileInfo().isDir()) {
            qDebug()<<"removing directory"<<iter.filePath();
            QDir(iter.filePath()).removeRecursively();
            continue;
        }
        qDebug()<<"removing file"<<iter.filePath();
        QFile(iter.filePath()).remove();
    }
}
}//ns

class WebDavTests : public QObject
{
    Q_OBJECT
    QString m_localRoot;

public:
    WebDavTests();

private Q_SLOTS:
    void testGet();
    void testList();
    void testCopy();
    void testMove();
};

WebDavTests::WebDavTests()
    :m_localRoot(qgetenv("QWEBDAV_EXAMPLE_LOCAL_ROOT"))
{
    Q_ASSERT(!qgetenv("QWEBDAV_EXAMPLE_URL").isEmpty() && "QWEBDAV_EXAMPLE_ROOT not defined");
    Q_ASSERT(!m_localRoot.isEmpty() && "QWEBDAV_EXAMPLE_LOCAL_URL not defined");
}

void WebDavTests::testGet() {
    ::emptyLocalRoot(m_localRoot);
    QDir(m_localRoot).mkpath("subdir");
    {
        QFile f(m_localRoot + "/subdir/thefile");
        QVERIFY(f.open(QFile::WriteOnly));
        f.write("blubb");
    }
    QWebdav webdav;
    webdav.setConnectionSettings(QUrl(qgetenv("QWEBDAV_EXAMPLE_URL")), "USERNAME", "PASSWORD");
    QByteArray ba;
    QBuffer* buf = new QBuffer(&ba);
    buf->open(QBuffer::WriteOnly);
    QNetworkReply* reply = webdav.get("/subdir/thefile", buf);
    QSignalSpy spy(reply, SIGNAL(finished()));
    QVERIFY(spy.wait());
    QVERIFY(ba == "blubb");
}

void WebDavTests::testCopy() {
    ::emptyLocalRoot(m_localRoot);
    {
        QFile f(m_localRoot + "/thefile");
        QVERIFY(f.open(QFile::WriteOnly));
        f.write("blubb");
    }
    QWebdav webdav;
    webdav.setConnectionSettings(QUrl(qgetenv("QWEBDAV_EXAMPLE_URL")), "USERNAME", "PASSWORD");
    {
        auto reply = webdav.copy("/thefile", "/thecopy");
        QSignalSpy spy(reply, SIGNAL(finished()));
        QVERIFY(spy.wait());
        QVERIFY(reply->error() == QNetworkReply::NoError);
        QCOMPARE(reply->errorString(), QString("Unknown error"));
    }
    {
        QFile f(m_localRoot + "/thecopy");
        QVERIFY(f.open(QFile::ReadOnly));
        QByteArray ba(f.readAll());
        QCOMPARE(ba, QByteArray("blubb"));
    }
}

void WebDavTests::testMove() {
    ::emptyLocalRoot(m_localRoot);
    {
        QFile f(m_localRoot + "/thefile");
        QVERIFY(f.open(QFile::WriteOnly));
        f.write("blubb");
    }
    QWebdav webdav;
    webdav.setConnectionSettings(QUrl(qgetenv("QWEBDAV_EXAMPLE_URL")), "USERNAME", "PASSWORD");
    {
        auto reply = webdav.move("/thefile", "/thecopy");
        QSignalSpy spy(reply, SIGNAL(finished()));
        QVERIFY(spy.wait());
        QVERIFY(reply->error() == QNetworkReply::NoError);
        QCOMPARE(reply->errorString(), QString("Unknown error"));
    }
    {
        QFile f(m_localRoot + "/thecopy");
        QVERIFY(f.open(QFile::ReadOnly));
        QByteArray ba(f.readAll());
        QCOMPARE(ba, QByteArray("blubb"));
    }
    {
        QVERIFY(!QFile(m_localRoot + "/thefile").exists());
    }
}

void WebDavTests::testList()
{
    ::emptyLocalRoot(m_localRoot);

    QWebdav webdav;
    webdav.setConnectionSettings(QUrl(qgetenv("QWEBDAV_EXAMPLE_URL")), "USERNAME", "PASSWORD");
    QNetworkReply* reply = webdav.list("/");
    QSignalSpy spy(reply, SIGNAL(finished()));
    QVERIFY(spy.wait());
    QVERIFY(reply->error() == QNetworkReply::NoError);
}

QTEST_MAIN(WebDavTests)

#include "tst_webdavtests.moc"
