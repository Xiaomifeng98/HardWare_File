#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "tcpsocket.h"
#include "userinformation.h"
#include "functionwindow.h"
#include "loginwindow.h"
#include <QDebug>
#include <QMessageBox>

registerwindow::registerwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registerwindow)
{
    ui->setupUi(this);

   TcpSocket *tcpSocket = new TcpSocket;
   connect(this, SIGNAL(registerUserReady(UserInformation)), tcpSocket, SLOT(registerUserByTcp(UserInformation)));//将用户信息提交到服务器
   connect(tcpSocket, SIGNAL(registerStatu(QString)), this, SLOT(showRegisterResult(QString)));//从服务器获取是否注册成功地信息
}

registerwindow::~registerwindow()
{
    delete ui;
}

//判断email是否为空
bool registerwindow::checkEmail(const QString &email)
{
    bool ok = email.contains("@" ) && email.endsWith(".com");
    if(!ok){
        return false;
    }
    QString str1 = email.section('@', 0, 0);
    if(str1.isEmpty()){
        return false;
    }
    QString str2 = email.section('@', 1, 1);
    if(str2 == ".com"){
        return false;
    }
    return true;
}

//判断电话是否正确
bool registerwindow::checkTelPhone(const QString &phone)
{
    if(phone.length() != 11){
        return false;
    }
    for(int i = 0; i < phone.size(); i++){
        QChar ch = phone.at(i);
        if(ch >= '0' && ch <= '9'){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

//点击了注册按钮，警告错误信息
void registerwindow::on_commitButton_clicked()
{
    QString errorString;
    QString username = ui->username->text();
    if(username.isEmpty()){
        errorString += "1.用户名不能为空。\n";
    }

    QString password = ui->password->text();
    if(password.isEmpty()){
        errorString += "2.密码不能为空\n";
    }

    QString email = ui->email->text();
    bool ok  = checkEmail(email);
    if(!ok){
        errorString += "3.邮箱格式错误，请输入正确的邮箱\n";
    }
    QString telPhone = ui->phone->text();
    ok = checkTelPhone(telPhone);
    if(!ok){
        errorString += "4.电话号码格式错误，请输入正确的电话号码\n";
    }

    if(!errorString.isEmpty()){
        QMessageBox::warning(NULL, "输入信息有误", errorString, QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    UserInformation user(username, password, email, telPhone);

    emit registerUserReady(user);//发送信号，将user信息传给服务器
    return;
}

//点击了注册用户地功能栏中的按钮之后，清除输入框并显示注册界面
void registerwindow::registerWindowShow()
{
    ui->username->clear();
    ui->password->clear();
    ui->email->clear();
    ui->phone->clear();
    this->show();
}

void registerwindow::showRegisterResult(const QString &error)
{
    if(error.isEmpty()){
         QMessageBox::information(NULL, "注册用户", "恭喜您，注册成功", QMessageBox::Yes, QMessageBox::Yes);
    }else{
        QString str = QString("很遗憾，注册失败(%1)").arg(error);
         QMessageBox::warning(NULL, "注册用户", str, QMessageBox::Yes, QMessageBox::Yes);
    }
}
