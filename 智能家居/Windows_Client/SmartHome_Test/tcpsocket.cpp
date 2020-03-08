#include "tcpsocket.h"
#include "serveraddressdialog.h"
#include "userinformation.h"
#include "smartprotocol.h"
#include "functionwindow.h"
#include "loginwindow.h"
#include "resetpasswordwindow.h"
#include <QHostAddress>
#include <QMessageBox>

TcpSocket::TcpSocket()
{
    tcp = new QTcpSocket(this);

    connect(tcp, SIGNAL(readyRead()), this, SLOT(RecvTcpData()));
}

void TcpSocket::RecvTcpData()
{
    QString errorString;
    QByteArray tcpData = tcp->readAll();
    qDebug() << "Register_RecvTcpData()" << tcpData;
    SmartProtocol smartProtocol(tcpData);
    if(smartProtocol.getSmartProtocolStatu() == true){
        errorString = "";
    }else{
        errorString = smartProtocol.getSmartProtocolError();
    }

    switch (smartProtocol.getSmartProtocolFunctionId()) {
    case SmartProtocol::USER_REGISTER:
        emit  registerStatu(errorString);
        break;
    case SmartProtocol::USER_LOGIN:
        emit functionStatu(errorString, smartProtocol.getSmartProtocolClientId());
        break;
    case SmartProtocol::USER_RESET_PASSWORD:
        emit ResetStatu(errorString);
        break;
    case SmartProtocol::USER_FORGET_PASSWORD:
        emit ForgetStatu(errorString);
        break;
    default:
        break;
    }

    return;
}

//槽函数的实现，将信息发送给服务器端，并转换为JSON格式
void TcpSocket::registerUserByTcp(const UserInformation &user)
{
    QString serverIp = ServerAddressDialog::getServerIP();
    short serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
        QMessageBox::warning(NULL, "没有服务器地址信息", "请输入服务器端地址信息以后再注册！", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        return;
    }

    //如果没有连接IP，那么连接
    if(tcp->state() == QTcpSocket::UnconnectedState){
        tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    //新建一个对象，初始化用户信息，将用户信息转换为JSON格式
    SmartProtocol smartProtocol(user);
    smartProtocol.addFunctionId(SmartProtocol::USER_REGISTER);
    tcp->write(smartProtocol.toProtocolData());

    return;
}

void TcpSocket::functionUserByTcp(const QString &username, const QString &password)
{
    //获取输入的IP地址和端口号
    QString serverIp = ServerAddressDialog::getServerIP();
    short serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
        QMessageBox::warning(NULL, "没有服务器地址信息", "请输入服务器端地址信息以后再注册！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    //如果没有连接IP，那么连接
    if(tcp->state() == QTcpSocket::UnconnectedState){
        tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    //新建一个对象，初始化用户信息，将用户信息转换为JSON格式
    SmartProtocol smartProtocol(username, password);
    smartProtocol.addFunctionId(SmartProtocol::USER_LOGIN);
    tcp->write(smartProtocol.toProtocolData());
    return;
}

void TcpSocket::resetUserByTcp(const QString username, const QString oldPassword, const QString newPassword)
{
    QString serverIp = ServerAddressDialog::getServerIP();
    short serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
        QMessageBox::warning(NULL, "没有服务器地址信息", "请输入服务器端地址信息以后再注册！", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        return;
    }

    //如果没有连接IP，那么连接
    if(tcp->state() == QTcpSocket::UnconnectedState){
        tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    //新建一个对象，初始化用户信息，将用户信息转换为JSON格式
    SmartProtocol smartProtocol(username, oldPassword, newPassword);
    smartProtocol.addFunctionId(SmartProtocol::USER_RESET_PASSWORD);
    tcp->write(smartProtocol.toProtocolData());

    return;
}

void TcpSocket::ForgetUserByTcp(const QString &username, const QString &useremail, const QString &telphone, const QString &newPassword)
{
    QString serverIp = ServerAddressDialog::getServerIP();
    short serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
        QMessageBox::warning(NULL, "没有服务器地址信息", "请输入服务器端地址信息以后再注册！", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        return;
    }

    //如果没有连接IP，那么连接
    if(tcp->state() == QTcpSocket::UnconnectedState){
        tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    //新建一个对象，初始化用户信息，将用户信息转换为JSON格式
    SmartProtocol smartProtocol(username, useremail, telphone, newPassword);
    smartProtocol.addFunctionId(SmartProtocol::USER_FORGET_PASSWORD);
    tcp->write(smartProtocol.toProtocolData());

    return;
}

void TcpSocket::controlDeviceByTcp(int deviceId, int statu, const QString &clientId)
{
    QString serverIp = ServerAddressDialog::getServerIP();
    short serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
        QMessageBox::warning(NULL, "没有服务器地址信息", "请输入服务器端地址信息以后再注册！", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        return;
    }

    //如果没有连接IP，那么连接
    if(tcp->state() == QTcpSocket::UnconnectedState){
        tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

    //新建一个对象，初始化用户信息，将用户信息转换为JSON格式
    SmartProtocol smartProtocol(clientId, deviceId, statu);
    smartProtocol.addFunctionId(SmartProtocol::USER_DEVICE_CONTROL);
    tcp->write(smartProtocol.toProtocolData());
    //tcp->close();

    return;
}
