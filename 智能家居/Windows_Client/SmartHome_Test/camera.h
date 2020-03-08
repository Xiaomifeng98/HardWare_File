#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QFile>
#include <QImage>

namespace Ui {
class Camera;
}

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = 0);
    ~Camera();

    enum process{
      START,
      NEXT1,
      NEXT2,
      END,
    };

private slots:
    void readHttpCameraData();
    void finishedHttp();

    void on_pushButton_clicked();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QFile file;
    QImage image;
    qint32 currentLen;
    qint32 totalLen;
    QByteArray buf;
    QByteArray boundary;
    enum process statu;
    Ui::Camera *ui;
    QNetworkAccessManager *netwokManger;
    QNetworkReply *networkReply;
};

#endif // CAMERA_H
