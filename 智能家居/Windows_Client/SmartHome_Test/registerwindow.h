#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include "userinformation.h"

namespace Ui {
class registerwindow;
}

class registerwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit registerwindow(QWidget *parent = 0);
    ~registerwindow();
    bool checkEmail(const QString &email);
    bool checkTelPhone(const QString &phone);

signals:
    void registerUserReady(const UserInformation &user);//点击注册的时候传送一个UserInformation对象的信号

private slots:
    void on_commitButton_clicked();
    void registerWindowShow();
    void showRegisterResult(const QString &error);

private:
    Ui::registerwindow *ui;
};

#endif // REGISTERWINDOW_H
