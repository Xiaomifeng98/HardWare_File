#ifndef SMARTPROTOCOL_H
#define SMARTPROTOCOL_H

#include <QJsonObject>
#include "userinformation.h"

class SmartProtocol
{
public:
    enum{
        USER_REGISTER  = 1,
        USER_LOGIN = 2,
        USER_DEVICE_CONTROL = 3,
        USER_RESET_PASSWORD = 4,
        USER_FORGET_PASSWORD = 5,
    };
    SmartProtocol(const UserInformation &user);
    SmartProtocol(const QByteArray &jsonData);
    SmartProtocol(const QString &username, const QString &password);
    SmartProtocol(const QString &clientId, int deviceId, int statu);
    SmartProtocol(const QString &username, const QString &oldPassword, const QString &newPassword);
    SmartProtocol(const QString &username, const QString &useremail, const QString &telphone, const QString &newPassword);
   void addFunctionId(int id);
    QByteArray toProtocolData(void);
    bool getSmartProtocolStatu();
    int getSmartProtocolFunctionId(void);
    QString getSmartProtocolError();
    QString getSmartProtocolClientId(void);

private:
    QJsonObject content;
};

#endif // SMARTPROTOCOL_H
