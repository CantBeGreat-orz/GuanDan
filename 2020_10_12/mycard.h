#ifndef MYCARD_H
#define MYCARD_H

#define SCALE 0.7
#define WINWIDTH  1764
#define WINHEIGHT 972

#include <QPropertyAnimation>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QtDebug>
#include <QPoint>
#include <QRect>
#include <QSize>

class myCard : public QWidget
{
    Q_OBJECT

private:

    int  value;                         //1-15,3-大王
    int  suit;                          //0-3，黑桃，红心，梅花，方块;小王0，大王1
    int  x;                             //左上横坐标
    int  y;                             //左上纵坐标
    int valueInShunZi;
    bool status;                        //标注选中状态，选中为1

public:

    QLabel * cardLabel[2];              //扑克图片
    QPoint point;                       //扑克坐标
    int cardID;                         //扑克id
    bool bePlayed;                      //被打出
    bool isInRound;                     //属于当前回合
    bool isWildCard;                    //为当前主牌
    int standAlone;

    explicit myCard(QWidget *parent = nullptr);
    myCard(int index, int v, int su, int vis, QPixmap cardGroupPix[], int cardWidth, int cardHeight, QWidget *parent = nullptr);

    void setCardLabel(QPixmap cardGroupPix[], int cardWidth, int cardHeight);   //设置扑克图片
    void mouseReleaseEvent(QMouseEvent * event);    //重写鼠标释放事件
    void setValue(int v);               //设置牌值
    void setSuit(int su);               //设置花色
    void setStatus(bool st);            //设置选中状态
    void setPoint(int x, int y);        //设置坐标
    int  getValue();                    //读取牌值
    int  getVIS();
    int  getSuit();                     //读取花色
    bool getStatus();                   //读取是否被选中
    QPropertyAnimation* setAnimation(QPoint &start, int t); //设置发牌动画

signals:

    void clicked();                     //单击信号
    void animationFinished(int id);     //动画结束信号，传递cardID

public slots:

    void getAnimationFinishedSignal();  //发送动画结束信号

};

#endif // MYCARD_H
