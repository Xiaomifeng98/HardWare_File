#include "devicemanagewindow.h"
#include "ui_devicemanagewindow.h"
#include <QDebug>

DeviceManageWindow::DeviceManageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceManageWindow)
{
    ui->setupUi(this);
}

DeviceManageWindow::~DeviceManageWindow()
{
    delete ui;
}

//所有设备，statu为1为关闭，statu为0为打开
void DeviceManageWindow::on_ledpushButton1_clicked(bool checked)
{
    int statu;
    if(!checked){
        ui->ledwidget1->setStyleSheet("border-image: url(:/image/room/closeled_ico.png)");
        ui->ledpushButton1->setStyleSheet("border-image: url(:/image/room/OFF.png)");
        statu = 1;//close
    }else{
        ui->ledwidget1->setStyleSheet("border-image: url(:/image/room/openled_ico.png)");
        ui->ledpushButton1->setStyleSheet("border-image: url(:/image/room/ON.png)");
        statu = 0;//open
    }
    emit controlDevice(1, statu);
}

void DeviceManageWindow::on_ledpushButton2_clicked(bool checked)
{
    int statu;
    if(!checked){
        ui->ledwidget2->setStyleSheet("border-image: url(:/image/room/closeled_ico.png)");
        ui->ledpushButton2->setStyleSheet("border-image: url(:/image/room/OFF.png)");
        statu = 1;//close
    }else{
        ui->ledwidget2->setStyleSheet("border-image: url(:/image/room/openled_ico.png)");
        ui->ledpushButton2->setStyleSheet("border-image: url(:/image/room/ON.png)");
        statu = 0;//open
    }
    emit controlDevice(2, statu);
}

void DeviceManageWindow::on_fanpushButton_clicked(bool checked)
{
    int statu;
    if(!checked){
        ui->fanwidget->setStyleSheet("border-image: url(:/image/room/closefan_ico.png)");
        ui->fanpushButton->setStyleSheet("border-image: url(:/image/room/OFF.png)");
        statu = 1;//close
    }else{
        ui->fanwidget->setStyleSheet("border-image: url(:/image/room/openfan_ico.png)");
        ui->fanpushButton->setStyleSheet("border-image: url(:/image/room/ON.png)");
        statu = 0;//open
    }
    emit controlDevice(3, statu);
}

void DeviceManageWindow::on_doorpushButton_clicked(bool checked)
{
    int statu;
    if(!checked){
        ui->doorwidget->setStyleSheet("border-image: url(:/image/room/closedoor_ico.png)");
        ui->doorpushButton->setStyleSheet("border-image: url(:/image/room/OFF.png)");
        statu = 1;//close
    }else{
        ui->doorwidget->setStyleSheet("border-image: url(:/image/room/opendoor_ico.png)");
        ui->doorpushButton->setStyleSheet("border-image: url(:/image/room/ON.png)");
        statu = 0;//open
    }
    emit controlDevice(4, statu);
}
