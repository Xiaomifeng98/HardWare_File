#include "forgetpasswordwindow.h"
#include "ui_forgetpasswordwindow.h"
#include "tcpsocket.h"
#include "functionwindow.h"
#include "sendpasswordemail.h"
#include <QMessageBox>

forgetPasswordWindow::forgetPasswordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::forgetPasswordWindow)
{
    ui->setupUi(this);

    FunctionWindow *funwin = new FunctionWindow;

    TcpSocket *tcp = new TcpSocket;
    connect(this, SIGNAL(ForgetUserReady(QString, QString, QString, QString)), tcp, SLOT(ForgetUserByTcp(QString, QString, QString, QString)));//将信息提交到服务器
    connect(this, SIGNAL(VerificationUserReady()), tcp, SLOT(VerificationUserByTcp()));//点击发送验证码，让服务器端向邮箱发送数据
    connect(tcp, SIGNAL(ForgetStatu(QString)), this, SLOT(showForgetResult(QString)));//从服务器获取
}

forgetPasswordWindow::~forgetPasswordWindow()
{
    delete ui;
}

void forgetPasswordWindow::showforgetPasswordWindow()
{
    ui->usernamelineEdit->setText("");
    ui->emaillineEdit->setText("");
    ui->newPasswordlineEdit->setText("");
    ui->ackPasswordlineEdit->setText("");
    ui->telphonelineEdit->setText("");

    this->show();
}


//判断email是否为空
bool forgetPasswordWindow::checkEmail(const QString &email)
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
bool forgetPasswordWindow::checkTelPhone(const QString &phone)
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



void forgetPasswordWindow::on_commotpushButton_clicked()
{
    QString username = ui->usernamelineEdit->text();
    QString useremail = ui->emaillineEdit->text();
    QString telphone = ui->telphonelineEdit->text();
    QString newPassword = ui->newPasswordlineEdit->text();
    QString ackPassword = ui->ackPasswordlineEdit->text();
    QString errorString;

    if(username.isEmpty()){
        errorString += "1.请输入您的用户名\n";
    }
    if(useremail.isEmpty()){
        errorString += "2.请输入您注册时使用的邮箱\n";
    }
    bool ok = checkEmail(useremail);
    if(!ok){
        errorString += "3.邮箱格式错误，请输入正确的邮箱\n";
    }
    ok = checkTelPhone(telphone);
    if(!ok){
        errorString += "4.电话号码格斯错误，请输入正确的电话号码\n";
    }
    if(telphone.isEmpty()){
        errorString += "5.请输入您注册时使用的号码\n";
    }
    if(newPassword.isEmpty()){
        errorString += "6.请输入新密码\n";
    }else{
        if(ackPassword.isEmpty()){
            errorString += "7.请确认新密码\n";
        }else{
            if(newPassword != ackPassword){
                errorString += "8.新密码不匹配，请重新输入\n";
            }
        }
    }

    if(!errorString.isEmpty()){
        QMessageBox::warning(NULL, "输入信息有误", errorString, QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    emit ForgetUserReady(username, useremail, telphone, newPassword);
    return;


}

void forgetPasswordWindow::showForgetResult(const QString &error)
{
    if(error.isEmpty()){
         QMessageBox::information(NULL, "密码服务", "密码已成功设置，请牢记您的密码", QMessageBox::Yes, QMessageBox::Yes);
         ///////////////////////////////////////
         SendPasswordEmail *sendmail = new SendPasswordEmail("smtp.qq.com", "1138803648@qq.com", "rhvqqbwfaceljeic");
         QString username = ui->usernamelineEdit->text();
         QString useremail = ui->emaillineEdit->text();
         QString subject = "Password";
         QString password = ui->newPasswordlineEdit->text();
         QString PasswordText = QString("%1先生/女士：<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;您的智能家居密码已被改为：<strong> %2</strong>").arg(username).arg(password);
         if(sendmail->Send(useremail, subject, PasswordText)){
             if(sendmail->PutSendLine()){
                 qDebug() << "Success!";
             }else{
                 qDebug() << "Failed";
             }
         }
         ///////////////////////////////////////
    }else{
        QString str = QString("找回密码失败(%1)").arg(error);
         QMessageBox::warning(NULL, "密码服务", str, QMessageBox::Yes, QMessageBox::Yes);
    }
}

