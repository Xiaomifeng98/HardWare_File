#ifndef RESETPASSWORDWINDOW_H
#define RESETPASSWORDWINDOW_H

#include <QMainWindow>

namespace Ui {
class resetPasswordWindow;
}

class resetPasswordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit resetPasswordWindow(QWidget *parent = 0);
    ~resetPasswordWindow();
    void showresetPassWordWindow();

signals:
    void resetUserReady(const QString username, const QString oldPassword, const QString newPassword);//将QString用户名，QString旧密码，QString新密码通过tcp--->resetUserByTcp()发送出去

private slots:
    void on_commitButton_clicked();
    void showResetResult(const QString &error);//从服务器端收到

private:
    Ui::resetPasswordWindow *ui;
};

#endif // RESETPASSWORDWINDOW_H
