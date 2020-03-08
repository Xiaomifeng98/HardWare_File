#include "game.h"
#include "ui_game.h"
#include <QFont>
#include <QFile>

typedef struct{
  short value;
  char color[50];
}BGCOLORSTURCT;
BGCOLORSTURCT bgcolor[12]={ //12种颜色卡片
   {0,   "background-color:rgb(209,209,209)"},
   {2,   "background-color:rgb(173,217,216)"  },
   {4,   "background-color:rgb(159,220,212)"  },
   {8,   "background-color:rgb(145,224,208)"  },
   {16,  "background-color:rgb(131,227,204)" },
   {32,  "background-color:rgb(117,231,200)" },
   {64,  "background-color:rgb(103,234,196)" },
   {128, "background-color:rgb(88,237,192)" },
   {256, "background-color:rgb(74,241,188)" },
   {512, "background-color:rgb(60,244,184)" },
   {1024,"background-color:rgb(46,248,180)"},
   {2048,"background-color:rgb(18,255,172)"}
};

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    setFixedSize(327,416);//固定窗口大小 不可拉伸
    //将16个按钮加入一个组 方便遍历操作
    pushbtnGroup=new QButtonGroup(this);
    pushbtnGroup->addButton(ui->pushButton_1,0);
    pushbtnGroup->addButton(ui->pushButton_2,1);
    pushbtnGroup->addButton(ui->pushButton_3,2);
    pushbtnGroup->addButton(ui->pushButton_4,3);
    pushbtnGroup->addButton(ui->pushButton_5,4);
    pushbtnGroup->addButton(ui->pushButton_6,5);
    pushbtnGroup->addButton(ui->pushButton_7,6);
    pushbtnGroup->addButton(ui->pushButton_8,7);
    pushbtnGroup->addButton(ui->pushButton_9,8);
    pushbtnGroup->addButton(ui->pushButton_10,9);
    pushbtnGroup->addButton(ui->pushButton_11,10);
    pushbtnGroup->addButton(ui->pushButton_12,11);
    pushbtnGroup->addButton(ui->pushButton_13,12);
    pushbtnGroup->addButton(ui->pushButton_14,13);
    pushbtnGroup->addButton(ui->pushButton_15,14);
    pushbtnGroup->addButton(ui->pushButton_16,15);
    memset(gamevalue,0,sizeof(gamevalue));//清零
    QFont font("Microsoft YaHei",15,75);//设置字体 微软、15号
    QAbstractButton * btn1;
    for(char i=0;i<16;i++){ //设置16个按钮显示的字体格式和背景颜色
         btn1=pushbtnGroup->button(i);
         btn1->setFont(font);
         btn1->setStyleSheet(QString(bgcolor[0].color));
    }
    ui->label_3->setAlignment(Qt::AlignHCenter);//提示框格式 居中
    ui->label_3->setStyleSheet("color:green;");//提示框字体  绿色
    QFile file("./2048.cfg");//判断是否有游戏记录
    if(!file.exists())
    {
        ui->pushButton_18->setEnabled(false);
    }
    gamestaues=0;
}

Game::~Game()
{
    delete ui;
}

int Game::CheckGame()
{
    int i=0,ret=0;
    for(;i<16;i++){
        if(gamevalue[i]==2048){//出现2048，即胜利
            return 2;
        }
        if(gamevalue[i]==0){
            ret=1;
        }
    }
    return ret;
}

void arrycpy(short *des,short **src,int len)//数组复制
{
    for(int i=0;i<len;i++){
        des[i]=*(src[i]);
    }
}

void arryset(short **des,short value,int len)
{
    for(int i=0;i<len;i++){
        *(des[i])=value;
    }
}

void ArryAlign(short **pAry) //往一边靠
{
    short tmp[4];
    int count=0;
    arrycpy(tmp,pAry,4);
    arryset(pAry,0,4);//数组清零
    for(int i=0;i<4;i++){
        if(tmp[i]){
            *(pAry[count++])=tmp[i];
        }
    }
}

void ArryMerge(short **pAry)//融合
{
    for(int i=0;i<3;i++){
        if(*(pAry[i])==*(pAry[i+1])){
            *(pAry[i])*=2;
            *(pAry[i+1])=0;
        }
    }
}

int ArrySum(short *ary,int len)//数组个元素求和
{
    int sum=0;
    for(int i=0;i<len;i++){
        sum+=ary[i];
    }
    return sum;
}

void Game::AddRandomNumber()
{
    QTime time;
    QAbstractButton * btn1;
    int btnid,value;
    while(1){
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        btnid = qrand() % 16;       //产生（0~15）以内的随机数 (位置随机)
        value = (qrand() % 2)*2+2;  //产生2或4 （值随机）
        if(gamevalue[btnid]==0) break; //找到空的位置为止
    }
    //qDebug("随机数出现所在的按钮id=%d,随机数的值为%d.",btnid,value);
    btn1=pushbtnGroup->button(btnid);
    gamevalue[btnid]=value;
    btn1->setText(QString::number(gamevalue[btnid],10));//把新的随机数显示出来
    for(int j=1;j<12;j++){ //设置对应的颜色
        if(gamevalue[btnid]==bgcolor[j].value){
            btn1->setStyleSheet(QString(bgcolor[j].color));
            break;
        }
    }
    ui->label_2->setText(QString::number(ArrySum(gamevalue,16),10));//计算得分


}

void Game::DisplayAllValue()
{
    QAbstractButton * btn1;
    for(char i=0;i<16;i++){
         btn1=pushbtnGroup->button(i);
         if(gamevalue[i]){
             btn1->setText(QString::number(gamevalue[i],10));
             for(int j=1;j<12;j++){
                 if(gamevalue[i]==bgcolor[j].value){
                     btn1->setStyleSheet(QString(bgcolor[j].color));
                     break;
                 }
             }
         }else{
             btn1->setText("");
             btn1->setStyleSheet(QString(bgcolor[0].color));
         }
    }

}

void Game::TurnLeftHandle()
{
    short *pArry[4]={0},count=0;

    for(int i=0;i<16;i++){
        pArry[count++]=&gamevalue[i];
        if(count==4){
            count=0;
            //1.先往左靠
            ArryAlign(pArry);
            //2.合并
            ArryMerge(pArry);
            //3.再往左靠
            ArryAlign(pArry);
        }
    }

}

void Game::TurnRightHandle()
{
    short *pArry[4]={0},count=3;

    for(int i=0;i<16;i++){
        pArry[count--]=&gamevalue[i];
        if(count<0){
            count=3;
            //1.先往右靠
            ArryAlign(pArry);
            //2.合并
            ArryMerge(pArry);
            //3.再往右靠
            ArryAlign(pArry);
        }
    }

}

void Game::TurnUpHandle()
{
    short *pArry[4]={0},count=0;

    for(int i=0;i<4;i++){
         for(int j=0;j<i+13;j+=4){
             pArry[count++]=&gamevalue[i+j];
             if(count==4){
                 count=0;
                 //1.先往上靠
                 ArryAlign(pArry);
                 //2.合并
                 ArryMerge(pArry);
                 //3.再往上靠
                 ArryAlign(pArry);
             }
         }
     }

}

void Game::TurnDownHandle()
{
    short *pArry[4]={0},count=3;

    for(int i=0;i<4;i++){
        for(int j=0;j<i+13;j+=4){
            pArry[count--]=&gamevalue[i+j];
            if(count<0){
                count=3;
                //1.先往下靠
                ArryAlign(pArry);
                //2.合并
                ArryMerge(pArry);
                //3.再往下靠
                ArryAlign(pArry);
            }
        }
    }

}

void Game::keyReleaseEvent(QKeyEvent *ev)
{
    if(!gamestaues) return ;
   switch(ev->key()){
   case Qt::Key_Up:
       TurnUpHandle();
       //qDebug("Key_Up");
       break;
   case Qt::Key_Down:
       TurnDownHandle();
       //qDebug("Key_Down");
       break;
   case Qt::Key_Right:
       TurnRightHandle();
       //qDebug("Key_Right");
       break;
   case Qt::Key_Left:
       TurnLeftHandle();
       //qDebug("Key_Left");
       break;
   default://其他按键退出函数
       return;
   }
    DisplayAllValue();   //刷新显示全部卡片

   //判断游戏是否结束
   int flag=CheckGame();
   switch (flag) { //return  2：胜利 1:未结束 0：结束
   case 0:
       ui->label_3->setText("游戏结束！");
       ui->label_3->setStyleSheet("color:red;");
       QMessageBox::warning(NULL, tr("提示信息"), tr("游戏结束，请重新开始！"));
       break;
   case 1:
        AddRandomNumber();
       break;
   case 2:
       QMessageBox::warning(NULL, tr("提示信息"), tr("游戏胜利,请重新开始！！"));
       qDebug("游戏胜利,请重新开始！");
       break;
   default:
       break;
   }


}

void Game::on_pushButton_20_clicked()
{
    qApp->quit();

}

void Game::on_pushButton_17_clicked()
{
    if(gamestaues){
        qDebug("重新开始");
        ui->label_3->setStyleSheet("color:green;");
        memset(gamevalue,0,sizeof(gamevalue));
        DisplayAllValue();
        AddRandomNumber();
    }else{
        gamestaues=1;
        ui->pushButton_17->setText("重新开始");
        AddRandomNumber();
    }
    ui->label_3->setText("退出前记得保存游戏！");

}

void Game::on_pushButton_18_clicked()
{
    QFile file("./2048.cfg");
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    short a;
    for(int i=0;i<16;i++){
        stream >> a ;
        gamevalue[i]=a;
    }
    //file.remove();
    file.close();
    DisplayAllValue();
    ui->pushButton_18->setEnabled(false);
    QMessageBox::warning(NULL, tr("提示信息"), tr("读取成功！"));

}

void Game::on_pushButton_19_clicked()
{
    QFile file("./2048.cfg");
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    for(int i=0;i<16;i++){
        stream << gamevalue[i];
    }
    file.close();
    ui->pushButton_18->setEnabled(true);
    QMessageBox::warning(NULL, tr("提示信息"), tr("保存成功！"));

}
