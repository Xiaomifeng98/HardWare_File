#ifndef DEVICEMANAGEWINDOW_H
#define DEVICEMANAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class DeviceManageWindow;
}

class DeviceManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceManageWindow(QWidget *parent = 0);
    ~DeviceManageWindow();

signals:
    void controlDevice(int deviceId, int statu);

private slots:
    void on_ledpushButton1_clicked(bool checked);

    void on_ledpushButton2_clicked(bool checked);

    void on_fanpushButton_clicked(bool checked);

    void on_doorpushButton_clicked(bool checked);

private:
    Ui::DeviceManageWindow *ui;
};

#endif // DEVICEMANAGEWINDOW_H
