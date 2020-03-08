#ifndef SERVERADDRESSDIALOG_H
#define SERVERADDRESSDIALOG_H

#include <QDialog>

namespace Ui {
class ServerAddressDialog;
}

class ServerAddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerAddressDialog(QWidget *parent = 0);
    ~ServerAddressDialog();

    void closeEvent(QCloseEvent *event);

    static QString getServerIP();
    static void setServerIP(const QString &value);

    static short getServerPort();
    static void setServerPort(short value);

private slots:
    void serverWindowShow();

private:
    Ui::ServerAddressDialog *ui;
    static QString serverIP;
    static short serverPort;
};

#endif // SERVERADDRESSDIALOG_H
