#ifndef FUNCTIONWINDOW_H
#define FUNCTIONWINDOW_H

#include <QMainWindow>
#include "userinformation.h"
#include "tcpsocket.h"
#include "devicemanagewindow.h"
#include "camera.h"
#include "game.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class FunctionWindow;
}

class FunctionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FunctionWindow(QWidget *parent = 0);
    void timerEvent(QTimerEvent *event);
    ~FunctionWindow();

    QString getClientId() const;
    void setClientId(const QString &value);

signals:
    void functionUserReady(UserInformation);
    void showLoginWindow();

private slots:
    //void FunctionWindowshow();

    void on_HomeButton_clicked();

    void on_DeviceManageButton_clicked();

    void controlDeviceSlot(int deviceId, int statu);

    void displayReplyData();

    void on_cameraPushButton_clicked();

    void on_gamePushButton_clicked();

private:
    Ui::FunctionWindow *ui;
    DeviceManageWindow *DevMwin;
    QString clientId;//客户端唯一识别码
    TcpSocket *tcp;
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
    Camera *camera;
    Game *game;


};

#endif // FUNCTIONWINDOW_H
