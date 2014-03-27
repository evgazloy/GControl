#ifndef MDEVICE_H
#define MDEVICE_H

#include <QObject>
#include "mgsocket.h"
#include "tcpcommands.h"

class MDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pTemp READ pTemp WRITE setpTemp NOTIFY pTempChanged)
public:
    explicit MDevice(QObject *parent = 0);

    void setCertificate(const QString &file);
    void createConnection(const QString &host, const quint16 &port);

    QString pTemp() const;
    void setpTemp(const QString &temp);

private:
    MGSocket *m_socket = 0;
    QString m_temp = "123.0";

    void initSocket();
    void inData(QByteArray data);
    template <class CMD> void send(CMD cmd);

    void inRegistered(const cmdRegistration_s &data);
    void inTemp(const cmdTemp_s &data);

signals:
    void pTempChanged();

public slots:
    void socketReady();
    void socketError(QAbstractSocket::SocketError err);
    void getTemp();
};

#endif // MDEVICE_H
