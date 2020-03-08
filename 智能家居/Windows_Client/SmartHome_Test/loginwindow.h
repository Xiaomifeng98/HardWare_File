#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "userinformation.h"
#include "functionwindow.h"
#include "resetpasswordwindow.h"
#include "forgetpasswordwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void saveLoginUser(QString &username, QString &password);
    void displayRememLoginberUser();

signals:
    void showRegisterWindow(void);
    void showServerAction(void);
    //void showFunctionWindow(void);
    void functionUserReady(const QString &username, const QString &password);

private slots:
    void on_checkButton_clicked(bool checked);

    void on_registeraction_triggered();

    void on_serverAction_triggered();

    void on_LoginButton_clicked();

    void showFunctionResult(const QString &error, const QString &clientId);

    void LoginWindowshow();

    void on_resetPasswordpushButton_clicked();

    void on_forgetPasswprdpushButton_clicked();

private:
    Ui::LoginWindow *ui;
    FunctionWindow *funwin;
    resetPasswordWindow *resetwin;
    forgetPasswordWindow *forgetwin;

};

#endif // LOGINWINDOW_H
