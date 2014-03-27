#include "mdevice.h"

MDevice::MDevice(QObject *parent) :
    QObject(parent)
{
    this->initSocket();
}

void MDevice::initSocket()
{
    m_socket = new MGSocket(typeDevice);
    Q_CHECK_PTR(m_socket);
    connect(m_socket, SIGNAL(sig_ready()), SLOT(socketReady()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(sig_socketError(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
    m_socket->initSocket();
}

void MDevice::socketReady()
{
    qDebug()<<"Socket ready";

    Q_CHECK_PTR(m_socket);
    m_socket->send("adsfasd");
}

void MDevice::socketError(QAbstractSocket::SocketError err)
{

}

void MDevice::getTemp()
{
    cmdRegistration_s data;
    this->send<cmdRegistration_s>(data);
    emit pTempChanged();
}

void MDevice::setCertificate(const QString &file)
{
    Q_CHECK_PTR(m_socket);
    m_socket->setCertificate(file);
}

void MDevice::createConnection(const QString &host, const quint16 &port)
{
    Q_CHECK_PTR(m_socket);
    m_socket->createConnection(host, port);
}
QString MDevice::pTemp() const
{
    return m_temp;
}

void MDevice::setpTemp(const QString &temp)
{
    m_temp = temp;
}

template<class CMD> void MDevice::send(CMD cmd)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out<<cmd;
    Q_CHECK_PTR(m_socket);
    m_socket->send(data);
}
