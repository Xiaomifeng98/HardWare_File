#include "resetpasswordwindow.h"
#include "ui_resetpasswordwindow.h"
#include "tcpsocket.h"
#include "functionwindow.h"
#include <QMessageBox>
#include <QDebug>

resetPasswordWindow::resetPasswordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::resetPasswordWindow)
{
    ui->setupUi(this);

    TcpSocket *tcp = new TcpSocket;

    //重置密码会向服务器发送用户名，旧密码，新密码，然后服务器返回状态号，error
    connect(this, SIGNAL(resetUserReady(QString, QString, QString)), tcp, SLOT(resetUserByTcp(QString, QString, QString)));//将信息提交到服务器
    connect(tcp, SIGNAL(ResetStatu(QString)), this, SLOT(showResetResult(QString)));//从服务器获取信息
}

resetPasswordWindow::~resetPasswordWindow()
{
    delete ui;
}

void resetPasswordWindow::showresetPassWordWindow()
{
    ui->usernamelineEdit->setText("");
    ui->oldpasswordlineEdit->setText("");
    ui->ackpasswordlineEdit->setText("");
    ui->newpasswordlineEdit->setText("");

    this->show();
}


void resetPasswordWindow::on_commitButton_clicked()
{
    QString username = ui->usernamelineEdit->text();
    QString oldPassword = ui->oldpasswordlineEdit->text();
    QString ackPassword = ui->ackpasswordlineEdit->text();
    QString newPassword = ui->newpasswordlineEdit->text();
    QString errorString;

    if(username.isEmpty()){
        errorString += "1.请输入用户名\n";
    }
    if(oldPassword.isEmpty()){
        errorString += "2.请输入旧密码\n";
    }
    if(newPassword.isEmpty()){
        errorString += "3.请输入新密码\n";
    }else{
        if(ackPassword.isEmpty()){
            errorString += "4.请确认新密码\n";
        }else{
            if(newPassword != ackPassword){
                errorString += "5.新密码不匹配，请重新输入\n";
            }
        }
    }
    if(!errorString.isEmpty()){
        QMessageBox::warning(NULL, "输入信息有误", errorString, QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    emit resetUserReady(username, oldPassword, newPassword);
    return;

}

void resetPasswordWindow::showResetResult(const QString &error)
{
    if(error.isEmpty()){
         QMessageBox::information(NULL, "密码服务", "重置密码成功", QMessageBox::Yes, QMessageBox::Yes);
    }else{
        QString str = QString("重置密码失败(%1)").arg(error);
         QMessageBox::warning(NULL, "密码服务", str, QMessageBox::Yes, QMessageBox::Yes);
    }
}
