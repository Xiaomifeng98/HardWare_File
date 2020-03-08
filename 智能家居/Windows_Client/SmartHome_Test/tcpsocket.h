#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include<QTcpSocket>
#include "userinformation.h"

class TcpSocket:public QObject
{

    Q_OBJECT

public:
    TcpSocket();

signals:
    void registerStatu(const QString &error);
    void functionStatu(const QString &error, const QString &clientId);
    void ResetStatu(const QString &error);
    void ForgetStatu(const QString &error);

public slots:
    void RecvTcpData(void);
    void registerUserByTcp(const UserInformation &user);
    void functionUserByTcp(const QString &username, const QString &password);
    void resetUserByTcp(const QString username, const QString oldPassword, const QString newPassword);
    void controlDeviceByTcp(int deviceId, int statu, const QString &clientId);//发送设备Id和状态
    void ForgetUserByTcp(const QString &username, const QString &useremail, const QString &telphone, const QString &newPassword);

private:
    QTcpSocket *tcp;
};

#endif // TCPSOCKET_H
