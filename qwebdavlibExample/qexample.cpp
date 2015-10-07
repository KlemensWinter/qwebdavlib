#include "qexample.h"

QExample::QExample(QObject *parent) :
    QObject(parent)
  ,m_path(qgetenv("QWEBDAV_EXAMPLE_PATH"))
{
    Q_ASSERT(!qgetenv("QWEBDAV_EXAMPLE_ROOT").isEmpty() && "QWEBDAV_EXAMPLE_ROOT not defined");
    int port = qgetenv("QWEBDAV_EXAMPLE_ROOT").toInt();
    w.setConnectionSettings(QWebdav::HTTP, "127.0.0.1", qgetenv("QWEBDAV_EXAMPLE_ROOT"), "USERNAME", "PASSWORD", port);
    connect(&p, SIGNAL(finished()), this, SLOT(printList()));
    connect(&p, SIGNAL(errorChanged(QString)), this, SLOT(printError(QString)));
    connect(&w, SIGNAL(errorChanged(QString)), this, SLOT(printError(QString)));
}

void QExample::printList()
{
    QList<QWebdavItem> list = p.getList();

    QWebdavItem item;
    foreach(item, list) {
        qDebug() << item.name();

        QNetworkReply *reply = w.get(item.path());
        connect(reply, SIGNAL(readyRead()), this, SLOT(replySkipRead()));
        m_replyList.append(reply);
    }
}

void QExample::printError(QString errorMsg)
{
    qDebug() << "QWebdav::printErrors()  errorMsg == " << errorMsg;
}

void QExample::replySkipRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply==0)
        return;

    QByteArray ba = reply->readAll();

    qDebug() << "QWebdav::replySkipRead()   skipped " << ba.size() << " reply->url() == " << reply->url().toString(QUrl::RemoveUserInfo);
}

void QExample::start()
{
    p.listDirectory(&w, m_path);
}
