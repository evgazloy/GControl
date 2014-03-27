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
    connect(m_socket, &MGSocket::sig_inCmd, this, &MDevice::inData);
    m_socket->initSocket();
}

void MDevice::inData(QByteArray data)
{
    QDataStream in(data);
    quint8 cmd;
    in>>cmd;

    switch(cmd)
    {
    case cmdRegistration:
    {
        cmdRegistration_s data;
        this->inRegistered(data);
        break;
    }

    case cmdTemp:
    {
        cmdTemp_s data;
        this->inTemp(data);
        break;
    }

    }
}

void MDevice::inRegistered(const cmdRegistration_s &data)
{
    qDebug()<<"Device registered";
}

void MDevice::inTemp(const cmdTemp_s &data)
{
    if(data.set)
        m_temp = data.temp;
}

void MDevice::socketReady()
{
    qDebug()<<"Socket ready";
    cmdRegistration_s data;
    data.type = typeControl;
    this->send<cmdRegistration_s>(data);
}

void MDevice::socketError(QAbstractSocket::SocketError err)
{

}

void MDevice::getTemp()
{
    cmdTemp_s data;
    data.set = 0;
    this->send<cmdTemp_s>(data);
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
