#include "functionwindow.h"
#include "ui_functionwindow.h"
#include "tcpsocket.h"
#include "userinformation.h"
#include "loginwindow.h"
#include "devicemanagewindow.h"
#include "game.h"
#include <QDebug>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QTime>
#include <QDate>


FunctionWindow::FunctionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FunctionWindow)
{
    ui->setupUi(this);

    DevMwin = new DeviceManageWindow();
    connect(DevMwin, SIGNAL(controlDevice(int,int)), this, SLOT(controlDeviceSlot(int,int)));

    tcp = new TcpSocket;

    networkManager = new QNetworkAccessManager;
    QString httpUrl = "http://www.tianqiapi.com/api/";
    QNetworkRequest request(httpUrl);
    request.setRawHeader("version", "v1");
    networkReply = networkManager->get(request);
    connect(networkReply, SIGNAL(finished()), this, SLOT(displayReplyData()));

    camera = new Camera;

    game = new Game;
   this->startTimer(1000);
}

void FunctionWindow::timerEvent(QTimerEvent *event)
{
    QTime time = QTime::currentTime();
    ui->timeLabel->setText(time.toString("hh:mm:ss"));
    QDate date = QDate::currentDate();
    ui->dateLabel->setText(date.toString("yyyy-MM-dd dddd"));
}

FunctionWindow::~FunctionWindow()
{
    delete ui;
}

void FunctionWindow::on_HomeButton_clicked()
{
    //发送打开loginwindow窗口界面的信号
    emit showLoginWindow();
    this->close();//关掉function窗口
}

void FunctionWindow::on_DeviceManageButton_clicked()
{
    DevMwin->show();
}

void FunctionWindow::controlDeviceSlot(int deviceId, int statu)
{
    //通过tcp发送控制指令
    tcp->controlDeviceByTcp(deviceId, statu,clientId );
}

void FunctionWindow::displayReplyData()
{
    QByteArray jsonData = networkReply->readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if(jsonDoc.isEmpty() || jsonError.error != QJsonParseError::NoError){
        qDebug() << "Fail to form json." << jsonError.errorString();
        return;
    }
    QJsonObject jsonObject = jsonDoc.object();
    QJsonArray dataArray = jsonObject["data"].toArray();
    QJsonObject firstObject = dataArray[0].toObject();
    int humidity = firstObject["humidity"].toInt();
    QString tem = firstObject["tem"].toString();
    QString air_level = firstObject["air_level"].toString();

    QString temText = QString("%1：%2").arg(ui->temLabel->text()).arg(tem);
    ui->temLabel->setText(temText);

    QString humidityText = QString("%1：%2").arg(ui->humidityLabel->text()).arg(humidity);
    ui->humidityLabel->setText(humidityText);

    QString air_levelText = QString("%1：%2").arg(ui->airlevelLabel->text()).arg(air_level);
    ui->airlevelLabel->setText(air_levelText);
}

QString FunctionWindow::getClientId() const
{
    return clientId;
}

void FunctionWindow::setClientId(const QString &value)
{
    clientId = value;
}


void FunctionWindow::on_cameraPushButton_clicked()
{
    camera->show();
}



void FunctionWindow::on_gamePushButton_clicked()
{
    game->show();
}
