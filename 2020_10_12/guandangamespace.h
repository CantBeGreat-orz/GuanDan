#ifndef GUANDANGAMESPACE_H
#define GUANDANGAMESPACE_H

#include <QSequentialAnimationGroup>
#include <QPushButton>
#include <QMessageBox>
#include <algorithm>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <QList>
#include <QString>
#include <QSet>
#include <QMap>
#include "mytool.h"

class guanDanGamespace : public QWidget
{
    Q_OBJECT

private:

    QSequentialAnimationGroup* group[4];    //发牌串行动画

    QPushButton * startGameButton;          //开始游戏按钮->下一局按钮
    QPushButton * playCardsButton;          //出牌按钮
    QPushButton * skipButton;               //跳过按钮
    QPushButton * jinGongButton;            //进贡按钮
    QPushButton * kangGongButton;           //抗贡按钮
    QPushButton * huanPaiButton;            //还牌按钮

    QVector<myCard *> player[4];            //4个玩家                      player
    QVector<myCard *> chosenCards;          //被选中的牌
    QVector<myCard *> lastPlayedCards;      //上次被打出的牌
    QVector<myCard *> jinGongCards;         //进贡的牌
    QVector<myCard *> blinkCard;            //同花顺提示闪烁的牌

    QPixmap cardGroupPix[2];                //扑克组图

    QList<int> dealList;                    //随机分发列表，0-26属于一号玩家，以此类推

    myCard * cards[108];                    //存放108张牌

    QLabel * background;                    //背景图片
    QLabel * cardPile;                      //一摞纸牌
    QLabel * leftCards;                     //左侧扑克图片
    QLabel * rightCards;                    //右侧扑克图片
    QLabel * upCards;                       //上方扑克图片
    QLabel * wildCardTip[4];                //主牌提示

    QPoint * playCardsButtonPoint[4];       //出牌(抗贡)按钮的四个坐标         player
    QPoint * skipButtonPoint[4];            //跳过（与抗贡）按钮的四个坐标      player
    QPoint * huanPaiButtonPoint[4];         //还牌按钮坐标                    player
    QPoint huanPaiPoint;                    //被还牌的初始坐标
    QPoint* wildCardTipPoint[4];            //主牌提示的坐标
    QVector<QPoint> jinGongCardPoint;       //进贡牌的初始坐标

    int gameRound;
    int cardWidth;                          //扑克宽度
    int cardHeight;                         //扑克高度
    int whoseRound;                         //当前是哪个玩家的回合
    int lastPlayer;                         //上一个出牌的玩家
    int successPlayer;                      //成功上岸的玩家的个数
    int successOrder[4];                    //上岸的玩家顺序
    int winWay;                             //双下3，对手末游2，队友末游1
    int playerPlaceAndWay[4][2];            //四家扑克的摆放位置元素与方法      player
    int partner[4];                         //四家的对家                     player
    int hasJinGong;                         //已经进贡的人数
    int maxJingGongCard;                    //最大的进贡牌型
    int playerGrade[4];                     //玩家等级                      player
    int huanPaiPlayer;                      //需要还牌的玩家
    int huanPaiToWho;                       //需要被还牌的玩家
    int winFlag[4];                         //赛点局数                      player
    int wildCardCount;                      //选中牌中的主牌个数
    int standAloneCount[4];                 //单独出列的牌的组数                             player

    double cardRecord[3];                    //上家打出的牌的牌型与大小
    double curCards[3];                      //现在将打出的牌型与大小

    bool oneSuceed;                         //标记该回合有人上岸以实现接风功能
    bool finishedFlag[4];                   //动画组结束标记
    bool huanPaiFlag;                       //是否正在还牌
    bool jinGongFlag;                       //是否正在进贡
    bool jinGongAnimationFinished[4];       //进贡动画结束标志
    bool stopBlink;                         //是否停止闪烁提示

    static bool cmp0(myCard* a, myCard * b);                    //卡牌排序比较方法
    static bool cmp1(myCard* a, myCard * b);                    //卡牌排序比较方法
    static bool cmpInShunZi(myCard* a, myCard * b);             //卡牌排序比较方法
    void setCenterPoint1(QVector<myCard *> &v);                 //设置扑克牌使居中坐标                cardManageTool
    void setCenterPoint2(QVector<myCard *> &v);                 //设置扑克牌使居中坐标                cardManageTool
    void setInOrderPoint1(QVector<myCard *> &v, int h);         //设置上下扑克牌顺序排列坐标             cardManageTool
    void setInOrderPoint2(QVector<myCard *> &v, int x);         //设置左右扑克牌顺序排列坐标             cardManageTool
    void setRightPoint(QVector<myCard *> &v, int hOrX, int way);//设置最终摆放坐标                      cardManageTool
    void setInLine(QVector<myCard *> &v, int h);                //设置打出扑克牌顺序排列坐标             cardManageTool
    void setCurCards(double v1, double v2, double v3);          //设置当前要出的牌的牌型与大小
    void setCardRecord(double v1, double v2, double v3);        //设置上次出牌的牌型与大小
    void judgeCardsKind();                                      //判断当前要出的牌的牌型与大小
    void findAndEreaseCard(QVector<myCard *> &v, myCard * c);   //找到并移除目标扑克                 cardManageTool
    void setAnimationGroup(QVector<myCard *> &v,int player);    //创建动画组
    void moveTo(QVector<myCard *> &v);                          //移动扑克组
    void setInRound(QVector<myCard *> &v);                      //设置当前回合卡牌                  player
    void resetCards();                                          //重置坐标
    void resetGame();                                           //重置对局
    void resetPlayer();                                         //清空四家扑克                    player
    void movePlayAndSkipButton();                               //移动出牌与跳过按钮
    void setPlayerPlaceAndWay();                                //设置四家扑克的摆放位置元素与方法
    void setOneCard(int index, int value, int suit, int vis);   //创建一张扑克
    void successAssess();                                       //胜利情形评估
    void autoJinGong(int who);                                  //默认进贡
    void autoShowAfterAnimation();                              //默认动画结束后显示控件
    void setJinGongAnimation();                                 //设置进贡动画
    void setHuanPaiAnimation();                                 //设置还牌动画
    void jinGongJudge();                                        //进贡情形判断                                
    void playATimes(int player);                                //记录玩家打a轮数
    void tongHuaShunTip();                                      //同花顺提示
    void setBrightLabel(myCard * card);                         //设置为明亮的牌面
    void setBlinkCards(QVector<myCard *> &v, int begin, int suit, int needWildCard);
                                                                //设置同花顺提示的闪烁卡组

    bool haveShunZi(QVector<myCard *> &v);                      //判断有无顺子
    bool haveValue(QVector<myCard *> &v, int va);               //判断有无值为va的牌


public:

    explicit guanDanGamespace(QWidget *parent = nullptr);
    void setCards();                            //建立牌组
    void keyPressEvent(QKeyEvent * event);      //快捷键设置

signals:

    void animationAllFinished();                //发牌动画结束信号

public slots:

    void dealCards();                           //发牌
    void chooseAndJudge();                      //判断出牌是否合法
    void playCards();                           //出牌
    void skip();                                //跳过
    void getCardAnimationFinshedID(int id);     //所有动画都结束的信号
    void afterAnimation();                      //接受到动画结束信号后的操作
    void jinGong();                             //进贡
    void kangGong();                            //抗贡
    void huanPai();                             //还牌
    void blink();                               //闪烁提示

};

#endif // GUANDANGAMESPACE_H
