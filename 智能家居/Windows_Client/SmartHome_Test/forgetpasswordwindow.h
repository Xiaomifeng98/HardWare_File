#ifndef FORGETPASSWORDWINDOW_H
#define FORGETPASSWORDWINDOW_H

#include <QMainWindow>


namespace Ui {
class forgetPasswordWindow;
}

class forgetPasswordWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void ForgetUserReady(const QString &username, const QString &useremail, const QString &telphone, const QString &newPassword);

public:
    explicit forgetPasswordWindow(QWidget *parent = 0);
    ~forgetPasswordWindow();
    void showforgetPasswordWindow();
    bool checkEmail(const QString &email);
    bool checkTelPhone(const QString &phone);

private slots:
    void on_commotpushButton_clicked();
    void showForgetResult(const QString &error);

private:
    Ui::forgetPasswordWindow *ui;
};

#endif // FORGETPASSWORDWINDOW_H
