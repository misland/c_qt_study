#include "server.h"
#include "QCoreApplication"
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>

Server::Server(QObject *parent) : QObject(parent)
{
    m_piserver = new QTcpServer;
    m_pisocket = new QTcpSocket;
    StartListen(2016);
}

void Server::StartListen(int nPort)
{
    if(m_piserver->listen(QHostAddress::Any,nPort))
        qDebug() << "listen ok";
    else
        qDebug() << "listen err";
    connect(m_piserver,SIGNAL(newConnection()),this,SLOT(newClientConnect()));
}

void Server::newClientConnect()
{
    qDebug() << "new client connect";
    m_pisocket = m_piserver->nextPendingConnection();
    connect(m_pisocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(m_pisocket,SIGNAL(disconnected()),this,SLOT(disConnect()));
}

void Server::readMessage()
{
    qDebug() << "read client message";
    QByteArray buf;
    buf = m_pisocket->readAll();
    QString str=buf;
    QJsonDocument doc=QJsonDocument::fromJson(str.toLocal8Bit().data());
    QJsonObject obj=doc.object();
    qDebug()<<obj.value("name").toString();
    QThread::sleep(2);
    m_pisocket->write("got message");
    qDebug() << buf;
}

void Server::disConnect()
{
    qDebug() << "client disconnect";
}
