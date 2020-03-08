#include "smartprotocol.h"
#include <QJsonDocument>
#include <QDebug>
#include <QJsonParseError>

//将用户信息转换为JSON格式
SmartProtocol::SmartProtocol(const UserInformation &user)
{
    content.insert("username", user.getName());
    content.insert("password", user.getPassword());
    content.insert("email", user.getEmail());
    //content.insert("telphone", user.getTelphone());
    content["telphone"] = user.getTelphone();
}

//将JSON格式地信息转换为常规信息
SmartProtocol::SmartProtocol(const QByteArray &jsonData)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if(jsonDoc.isEmpty() || jsonError.error != QJsonParseError::NoError){
        qDebug() << "fail to from json"  << jsonError.errorString();
        return;
    }
    content = jsonDoc.object();
}

SmartProtocol::SmartProtocol(const QString &username, const QString &password)
{
    content.insert("username",username);
    content.insert("password",password);
}

SmartProtocol::SmartProtocol(const QString &clientId, int deviceId, int statu)
{
    content["clientId"] = clientId;
    content["deviceId"] = deviceId;
    content["controlStatu"] = statu;
}

SmartProtocol::SmartProtocol(const QString &username, const QString &oldPassword, const QString &newPassword)
{
    content["username"] = username;
    content["oldPassword"] = oldPassword;
    content["newPassword"] = newPassword;
}

SmartProtocol::SmartProtocol(const QString &username, const QString &useremail, const QString &telphone, const QString &newPassword)
{
    content["username"] = username;
    content["useremail"] = useremail;
    content["telphone"] = telphone;
    content["newPassword"] = newPassword;
}

void SmartProtocol::addFunctionId(int id)
{
    content["functionId"] = id;
}

QByteArray SmartProtocol::toProtocolData()
{
    QJsonDocument jsonDoc(content);
    return jsonDoc.toJson();
}

//获取协议状态
bool SmartProtocol::getSmartProtocolStatu()
{
    int ret = content["statu"].toInt();
    if(ret != 0){
        return false;
    }

    return true;
}

int SmartProtocol::getSmartProtocolFunctionId()
{
    return content["functionId"].toInt();
}

QString SmartProtocol::getSmartProtocolError()
{
    QString errorString = content["error"].toString();
    return errorString;
}

QString SmartProtocol::getSmartProtocolClientId()
{
    return content["clientId"].toString();
}
