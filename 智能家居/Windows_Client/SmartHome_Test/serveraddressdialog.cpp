#include "serveraddressdialog.h"
#include "ui_serveraddressdialog.h"
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include<QCloseEvent>

QString ServerAddressDialog::serverIP;
short ServerAddressDialog::serverPort;

ServerAddressDialog::ServerAddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerAddressDialog)
{
    ui->setupUi(this);
}

ServerAddressDialog::~ServerAddressDialog()
{
    delete ui;
}

void ServerAddressDialog::closeEvent(QCloseEvent *event)
{
    QString errorString;
    QString ip = ui->iplineEdit->text();
    QString port = ui->portlineEdit->text();
    if(ip.isEmpty() || ip.isNull()){
        errorString += "1.请输入正确的IP地址\n";
    }

    //判断是否为空，空返回true，非空返回false
    QHostAddress ipAddress(ip);

    //判断端口号的有效性，转换错误为假，转换正确为真
    bool ok;
    port.toShort(&ok);
    if(port.isEmpty() || !ok){
        errorString += "2.请输入正确的服务器端口号\n";
    }

    if(!errorString.isEmpty()){
        int ret = QMessageBox::warning(NULL, "输入的信息有误", errorString, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        if(ret == QMessageBox::Yes){
            event->ignore();//忽略关闭事件
        }
        return;
    }
    serverIP = ip;
    serverPort = port.toShort(&ok);
}

void ServerAddressDialog::serverWindowShow()
{
    this->show();
}

short ServerAddressDialog::getServerPort()
{
    return serverPort;
}

void ServerAddressDialog::setServerPort(short value)
{
    serverPort = value;
}

QString ServerAddressDialog::getServerIP()
{
    return serverIP;
}

void ServerAddressDialog::setServerIP(const QString &value)
{
    serverIP = value;
}
