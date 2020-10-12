#include "mycard.h"

myCard::myCard(QWidget *parent)
    : QWidget(parent)
{

}

myCard::myCard(int index, int v, int su, int vis, QPixmap cardGroupPix[], int cardWidth, int cardHeight, QWidget *parent)
    : QWidget(parent)
{
    value=v;
    valueInShunZi=vis;
    suit=su;
    status=0;
    bePlayed=0;
    isInRound=0;
    isWildCard=0;
    standAlone=0;
    resize(cardWidth*SCALE,cardHeight*SCALE);
    setCardLabel(cardGroupPix,cardWidth,cardHeight);
    cardID=index;
    move(WINWIDTH/2-150/2+20,WINHEIGHT/2-150/2+20);
    hide();
}

void myCard::setCardLabel(QPixmap cardGroupPix[], int cardWidth, int cardHeight)
{
    for(int i=0;i<2;i++){
        cardLabel[i]=new QLabel(this);
        QPixmap tmp;
        //寻图算法找到对应图片
        if(value==14)
            tmp=cardGroupPix[i].copy(13*cardWidth,0,cardWidth,cardHeight);
        else if(value==15)
            tmp=cardGroupPix[i].copy(13*cardWidth,cardHeight,cardWidth,cardHeight);
        else
            tmp=cardGroupPix[i].copy((value-1)%13*cardWidth,suit*cardHeight,cardWidth,cardHeight);
        cardLabel[i]->resize(cardWidth*SCALE,cardHeight*SCALE);
        cardLabel[i]->setPixmap(tmp.scaled(cardLabel[i]->size()));
        cardLabel[i]->setVisible(false);
    }
}

void myCard::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked();
}

void myCard::setValue(int v)
{
    value=v;
}

void myCard::setSuit(int su)
{
    suit=su;
}

void myCard::setStatus(bool st)
{
    status=st;
}

void myCard::setPoint(int x, int y)
{
    point.setX(x);
    point.setY(y);
}

int myCard::getValue()
{
    return value;
}

int myCard::getVIS()
{
    return valueInShunZi;
}

int myCard::getSuit()
{
    return suit;
}

bool myCard::getStatus()
{
    return status;
}

QPropertyAnimation* myCard::setAnimation(QPoint &start, int t)
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");;
    QSize s=size();
    animation->setDuration(t);
    animation->setStartValue(QRect(start,s));
    animation->setEndValue(QRect(point,s));
    connect(animation,SIGNAL(finished()),this,SLOT(getAnimationFinishedSignal()));
    return animation;
}

void myCard::getAnimationFinishedSignal()
{
    emit animationFinished(cardID);
}
