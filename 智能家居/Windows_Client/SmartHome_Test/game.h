#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QButtonGroup>
#include <QTime>
#include <QMessageBox>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    int CheckGame(void);
    void AddRandomNumber(void);
    void DisplayAllValue(void);
    void TurnLeftHandle(void);
    void TurnRightHandle(void);
    void TurnUpHandle(void);
    void TurnDownHandle(void);
protected:
    virtual void keyReleaseEvent(QKeyEvent *ev);
private slots:
    void on_pushButton_20_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::Game *ui;
    QButtonGroup* pushbtnGroup;
    short gamevalue[16];//记录16张卡片上面的数字
    int gamestaues; //0:stop  1:start 2：victory
};

#endif // GAME_H
