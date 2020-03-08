#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include "resetpasswordwindow.h"
#include "serveraddressdialog.h"
#include "functionwindow.h"
#include "forgetpasswordwindow.h"
#include "tcpsocket.h"
#include "userinformation.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    registerwindow *regWin = new registerwindow;
    connect(this, SIGNAL(showRegisterWindow()), regWin, SLOT(registerWindowShow()));

    ServerAddressDialog *serDia = new ServerAddressDialog;
    connect(this, SIGNAL(showServerAction()), serDia, SLOT(serverWindowShow()));

    funwin = new FunctionWindow;
    //connect(this, SIGNAL(showFunctionWindow()), funwin, SLOT(FunctionWindowshow()));//服务器返回2（登陆正确）后，显示窗口
    connect(funwin, SIGNAL(showLoginWindow()), this, SLOT(LoginWindowshow()));

    TcpSocket *tcpSocket = new TcpSocket;
    connect(this, SIGNAL(functionUserReady(QString, QString)), tcpSocket, SLOT(functionUserByTcp(QString, QString)));//将用户(姓名、密码)信息提交到服务器
    connect(tcpSocket, SIGNAL(functionStatu(QString, QString)), this, SLOT(showFunctionResult(QString, QString)));//从服务器获取是否登录成功信息

    resetwin = new resetPasswordWindow;
    forgetwin = new forgetPasswordWindow;

    bool ok = QFile::exists("user.txt");
    if(ok){
        displayRememLoginberUser();
        ui->checkButton->setText("√");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete funwin;
    delete resetwin;
    delete forgetwin;
}

void LoginWindow::saveLoginUser(QString &username, QString &password)
{
    QFile file("user.txt");
    bool ok = file.open(QFile::WriteOnly);
    if(!ok){
        qDebug() << "Fail to open user.txt:" << file.errorString();
        return;
    }
    username += "\n";
    password += "\n";
    file.write(username.toUtf8());
    file.write(password.toUtf8());

    file.close();

    return;
}

void LoginWindow::displayRememLoginberUser()
{
    QFile file("user.txt");
    bool ok = file.open(QFile::ReadOnly);
    if(!ok){
        qDebug() << "Fail to open user.txt:" << file.errorString();
        return;
    }

    QString username = file.readLine();
    username.remove("\n");
    QString password = file.readLine();
    password.remove("\n");
    ui->Name_lineEdit->setText(username);
    ui->Password_lineEdit->setText(password);

    file.close();
    return;
}

void LoginWindow::on_checkButton_clicked(bool checked)
{
    if(checked == true){
        //flag = 1;
        QString name = ui->Name_lineEdit->text();
        QString password = ui->Password_lineEdit->text();
        saveLoginUser(name, password);
        ui->checkButton->setText("√");
    }else{
        //flag = 0;
        ui->checkButton->setText("");
        QFile::remove("user.txt");//如果没有记住密码，那么删除这个文件
    }
}

void LoginWindow::on_registeraction_triggered()
{
    qDebug() << "registeraction";
    emit showRegisterWindow();
}

void LoginWindow::on_serverAction_triggered()
{
    qDebug() << "serverAction";
    emit showServerAction();
}

//当点击了登录，发送showFunctionWindow()信号，与FunctionWindowshow()连接，显示function窗口
//在这里，可以将信息（用户名、密码）发送给服务器端
void LoginWindow::on_LoginButton_clicked()
{
    qDebug() << "loginAction";
    QString username = ui->Name_lineEdit->text();
    QString password = ui->Password_lineEdit->text();
    QString errorString;

    //判断用户名
    if(username.isEmpty()){
        errorString += "1.登陆前请输入用户名！\n";
    }

    //判断密码
    if(password.isEmpty()){
        errorString += "2.请输入密码！\n";
    }

    if(!errorString.isEmpty()){
        QMessageBox::warning(NULL, "警告", errorString, QMessageBox::Yes, QMessageBox::Yes);
        return;
    }else{
        emit functionUserReady(username, password);
    }

    //UserInformation user(name, password);



}

void LoginWindow::showFunctionResult(const QString &error, const QString &clientId)
{
    if(error.isEmpty()){
         QMessageBox::information(NULL, "登录", "恭喜您，登录成功", QMessageBox::Yes, QMessageBox::Yes);
        funwin->setClientId(clientId);
         qDebug() << clientId;//输出身份识别码

         this->hide();//将窗口隐藏
         funwin->show();

    }else{
        QString str = QString("很遗憾，登陆失败(%1)").arg(error);
         QMessageBox::warning(NULL, "登录",str, QMessageBox::Yes, QMessageBox::Yes);
    }
}

void LoginWindow::LoginWindowshow()
{
    //ui->Name_lineEdit->clear();
//    if(flag == 0)
//        ui->Password_lineEdit->clear();
    this->show();
}

void LoginWindow::on_resetPasswordpushButton_clicked()
{
    resetwin->showresetPassWordWindow();
}

void LoginWindow::on_forgetPasswprdpushButton_clicked()
{
    forgetwin->showforgetPasswordWindow();
}
