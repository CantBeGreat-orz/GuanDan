#include "guandangamespace.h"

//比较方法：单独出列的在前，其余的小牌在前，牌值一样花色小在前（0-3对应黑桃，红心，梅花，方块）
bool guanDanGamespace::cmp0(myCard *a, myCard *b)
{
    if(a->standAlone!=b->standAlone){
        return a->standAlone > b->standAlone;
    }
    if(a->getValue()!=b->getValue()){
        return a->getValue() < b->getValue();
    }
    if(a->getSuit()!=b->getSuit()){
        return a->getSuit() < b->getSuit();
    }
}

//比较方法：小牌在前，牌值一样花色小在前（0-3对应黑桃，红心，梅花，方块）
bool guanDanGamespace::cmp1(myCard *a, myCard *b)
{
    if(a->getValue()!=b->getValue()){
        return a->getValue() < b->getValue();
    }
    if(a->getSuit()!=b->getSuit()){
        return a->getSuit() < b->getSuit();
    }
}

//比较方法：按照顺子牌值，小牌在前，牌值一样花色小在前（0-3对应黑桃，红心，梅花，方块）
bool guanDanGamespace::cmpInShunZi(myCard *a, myCard *b)
{
    if(a->getVIS()!=b->getVIS()){
        return a->getVIS() < b->getVIS();
    }
    if(a->getSuit()!=b->getSuit()){
        return a->getSuit() < b->getSuit();
    }
}

void guanDanGamespace::setCenterPoint1(QVector<myCard *> &v)
{
    if(v.size()==0) return;
    //计算应该横坐标应该偏移的量
    int distance=WINWIDTH/2-(v.back()->point.x()-v.front()->point.x()+cardWidth*SCALE)/2;
    for(int i=0;i<v.size();i++){
        v[i]->point.setX(v[i]->point.x()+distance);
        v[i]->cardLabel[0]->setVisible(true);
    }
}

void guanDanGamespace::setCenterPoint2(QVector<myCard *> &v)
{
    if(v.size()==0) return;
    //计算应该纵坐标应该偏移的量
    int distance=WINHEIGHT/2-(v.back()->point.y()-v.front()->point.y()+cardHeight*SCALE)/2;
    for(int i=0;i<v.size();i++){
        v[i]->point.setY(v[i]->point.y()+distance);
        v[i]->cardLabel[0]->setVisible(true);
    }
}

void guanDanGamespace::setInOrderPoint1(QVector<myCard *> &v, int h)
{
    if(v.size()==0) return;
//    std::sort(v.begin(),v.end(),cmp);
    v[0]->setPoint(0,h);
    v[0]->cardLabel[0]->setVisible(true);
    for(int i=1;i<v.size();i++){
        if(v[i]->standAlone){
            //接上一张牌的单独出列的顺子
            if(v[i]->standAlone==v[i-1]->standAlone){
                v[i]->setPoint(v[i-1]->point.x(),v[i-1]->point.y()-cardHeight*0.375*SCALE);
                v[i]->lower();
            }
            //下一组单独出列的顺子的第一张牌
            else{
                v[i]->setPoint(v[i-1]->point.x()+cardWidth*SCALE,h);
                v[i]->raise();
            }
        }
        else if(v[i]->getValue()==v[i-1]->getValue()){
            //如果牌值一样竖向排列
            v[i]->setPoint(v[i-1]->point.x(),v[i-1]->point.y()-cardHeight*0.375*SCALE);
            v[i]->lower();
        }
        else{
            //牌值不一样横向排列
            v[i]->setPoint(v[i-1]->point.x()+cardWidth*SCALE,h);
            v[i]->raise();
        }
        v[i]->cardLabel[0]->setVisible(true);
    }
}

void guanDanGamespace::setInOrderPoint2(QVector<myCard *> &v, int x)
{
    if(v.size()==0) return;
//    std::sort(v.begin(),v.end(),cmp);
    v[0]->setPoint(x,0);
    v[0]->cardLabel[0]->setVisible(true);
    for(int i=1;i<v.size();i++){
        if(v[i]->standAlone){
            if(v[i]->standAlone==v[i-1]->standAlone){
                v[i]->setPoint(v[i-1]->point.x()+cardWidth*SCALE/2,v[i-1]->point.y());
                v[i]->raise();
            }
            else{
                v[i]->setPoint(x,v[i-1]->point.y()+cardHeight*SCALE/2);
                v[i]->raise();
            }
        }
        else if(v[i]->getValue()==v[i-1]->getValue()){
            //如果牌值一样横向排列
            v[i]->setPoint(v[i-1]->point.x()+cardWidth*SCALE/2,v[i-1]->point.y());
            v[i]->raise();
        }
        else{
            v[i]->setPoint(x,v[i-1]->point.y()+cardHeight*SCALE/2);
            v[i]->raise();
        }
        v[i]->cardLabel[0]->setVisible(true);
    }
}

void guanDanGamespace::setRightPoint(QVector<myCard *> &v, int hOrX, int way)
{
    if(v.size()==0) return;
    if(way==1){
        //上下两名玩家管理手牌方式
        setInOrderPoint1(v,hOrX);
        setCenterPoint1(v);
    }
    else if (way==2) {
        //左右两名玩家手牌管理方式
        setInOrderPoint2(v,hOrX);
        setCenterPoint2(v);
    }
}

void guanDanGamespace::setInLine(QVector<myCard *> &v, int h)
{
    if(v.size()==0) return;
    v[0]->setPoint(0,h);
    for(int i=1;i<v.size();i++){
        v[i]->setPoint(v[i-1]->point.x()+cardWidth*4/5,h);
    }
}

void guanDanGamespace::setCurCards(double v1, double v2, double v3)
{
    curCards[0]=v1;
    curCards[1]=v2;
    curCards[2]=v3;
}

void guanDanGamespace::setCardRecord(double v1, double v2, double v3)
{
    cardRecord[0]=v1;
    cardRecord[1]=v2;
    cardRecord[2]=v3;
}

void guanDanGamespace::judgeCardsKind()
{
    if(chosenCards.size()==0){
        setCurCards(0,0,0);                                                 //非法（没有牌）
        return;
    }
    std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
    if(chosenCards.size()==1){
        if(chosenCards[0]->isWildCard){
            setCurCards(1,1,13.5);                                          //单张主牌
        }
        else{
            setCurCards(1,1,chosenCards[0]->getValue());                    //单张
        }
    }
    else if(chosenCards.size()==2){
        if(chosenCards[0]->isWildCard && chosenCards[1]->isWildCard){
            setCurCards(1,2,13.5);                                          //主牌对子
        }
        else if(chosenCards[0]->getValue()==chosenCards[1]->getValue() ||
                (chosenCards[0]->isWildCard && chosenCards[1]->getValue()<14) ||
                (chosenCards[1]->isWildCard && chosenCards[0]->getValue()<14)){
            setCurCards(1,2,chosenCards[0]->getValue());                    //对子
        }
        else{
            setCurCards(0,0,0);                                             //非法
        }
    }
    else if(chosenCards.size()==3){
        if(isEqual(chosenCards,1)){
            setCurCards(1,3,chosenCards[0]->getValue());                    //三张
        }
        else{
            setCurCards(0,0,0);                                             //非法
        }
    }
    else if(chosenCards.size()==4){
        if(isEqual(chosenCards[0]->getValue(),chosenCards[1]->getValue(),14) &&
           isEqual(chosenCards[2]->getValue(),chosenCards[3]->getValue(),15))
        {
             setCurCards(8,1,1);                                            //四鬼
        }
        else if(isEqual(chosenCards,1)){
            setCurCards(2,1,chosenCards[0]->getValue());                    //四炸
        }
        else{
            setCurCards(0,0,0);                                             //非法
        }
    }
    else if(chosenCards.size()==5){
        if(isEqual(chosenCards,1)){
            setCurCards(3,1,chosenCards[0]->getValue());                    //五炸
         }
        else if(chosenCards[0]->getValue()==chosenCards[1]->getValue() &&
                chosenCards[3]->getValue()==chosenCards[4]->getValue() &&
                (chosenCards[2]->getValue()==chosenCards[0]->getValue() ||
                chosenCards[2]->getValue()==chosenCards[3]->getValue()))
        {
            if(wildCardCount){
                setCurCards(1,4,chosenCards[4]->getValue());                //三带二,有主牌
            }
            else{
                setCurCards(1,4,chosenCards[2]->getValue());                //三带二
            }
            if(chosenCards[2]->getValue()==chosenCards[3]->getValue()){ //如果三张值大，重新排序
                for(int i=0;i<2;i++){
                    myCard* tmp;
                    tmp=chosenCards[0];
                    chosenCards.append(tmp);
                    chosenCards.pop_front();
                 }
            }
            else if(chosenCards[2]->getValue()==chosenCards[0]->getValue() && wildCardCount){   //如果主牌在三张中且三张值小，重新排序
                for(int i=0;i<2;i++){
                    myCard* tmp;
                    tmp=chosenCards[0];
                    chosenCards.append(tmp);
                    chosenCards.pop_front();
                 }
            }
        }
        else if(haveShunZi(chosenCards)){
            int v3=0;                   //牌值判断，存放于v3
            bool cardValue[18]={0};     //牌值为i的是否存在
            int dp[14]={0};             //dp[i]:牌值为i~i+4中有几个存在
            for(int i=0;i<5;i++){
                if(chosenCards[i]->getValue()<14){
                    if(!chosenCards[i]->isWildCard){
                        cardValue[chosenCards[i]->getValue()]=1;
                        if(chosenCards[i]->getValue()+13<18){
                           cardValue[chosenCards[i]->getValue()+13]=1;
                        }
                    }
                }
            }
            for(int i=1;i<=5;i++){
                if(cardValue[i]){
                    dp[1]++;
                }
            }
            if(dp[1]==5-wildCardCount){
                v3=1+2;
            }
            for(int i=2;i<=13;i++){
                dp[i]=dp[i-1]-cardValue[i-1]+cardValue[i+4];
                //qDebug()<<"dp["<<i+2<<"]="<<dp[i];
                if(dp[i]==5-wildCardCount && (i<=8 || i>=12)){  //起始牌限定于（3 ~ 10 和 A、2）
                    v3=(i+2)%13;
                }
            }
            if(isEqual(chosenCards,2)){
                setCurCards(4,1,v3);                                        //同花顺
            }
            else{
                setCurCards(1,6,v3);                                        //顺子
            }
            if(v3==1 || v3==2){                         //2,3,4,5,6 or A,2,3,4,5情况重新排序
                std::sort(chosenCards.begin(),chosenCards.end(),cmpInShunZi);
            }
        }
        else if(wildCardCount==2){                      //有两张主牌且天然不构成三带二和顺子
            QSet<int> vs;
            for(int i=0;i<5;i++){
                if(!chosenCards[i]->isWildCard){
                    vs.insert(chosenCards[i]->getValue());
                }
            }
            QSet<int>::iterator it=vs.begin();
            it++;
            int va=*it;
            if(vs.size()==2){                       //如果非主牌的牌值只有两种，构成逢人配条件
                setCurCards(1,4,va);
            }
            QVector<myCard*> vtmp;                  //重新排序
            for(int i=0;i<chosenCards.size();i++){
                if(chosenCards[i]->getValue()==va){
                    vtmp.append(chosenCards[i]);
                }
            }
            for(int i=0;i<chosenCards.size();i++){
                if(chosenCards[i]->isWildCard){
                    vtmp.append(chosenCards[i]);
                }
            }
            for(int i=0;i<chosenCards.size();i++){
                if(chosenCards[i]->getValue()!=va && !chosenCards[i]->isWildCard){
                    vtmp.append(chosenCards[i]);
                }
            }
            chosenCards.clear();
            chosenCards=vtmp;
        }
        else if(wildCardCount==1){                                  //如果有一张主牌且天然不构成三带二和顺子
            QMap<int,int> vm;
            for(int i=0;i<5;i++){
                if(!chosenCards[i]->isWildCard){
                    if(vm.find(chosenCards[i]->getValue())!=vm.end()){
                        vm[chosenCards[i]->getValue()]++;
                    }
                    else{
                         vm[chosenCards[i]->getValue()]=1;
                    }
                }
            }
            QMap<int,int>::iterator it=vm.begin();
            if((it.value()==3 || it.value()==1) && vm.size()==2){   //除主牌外牌值个数分配3 1
                int va;
                if(it.value()==3) va=it.key();
                else{
                    it++;
                    va=it.key();
                }
                setCurCards(1,4,va);                                //取个数为3的牌值为三带二大小
                QVector<myCard*> vtmp;
                //重新排序
                for(int i=0;i<chosenCards.size();i++){
                    if(chosenCards[i]->getValue()==va){
                        vtmp.append(chosenCards[i]);
                    }
                }
                for(int i=0;i<chosenCards.size();i++){
                    if(chosenCards[i]->getValue()!=va){
                        vtmp.append(chosenCards[i]);
                    }
                }
                chosenCards.clear();
                chosenCards=vtmp;
            }
            else if(vm.size()==2 && it.value()==2){                 //除主牌外牌值个数分配2 2
                it++;
                int va=it.key();
                setCurCards(1,4,va);                                //取非主牌中较大牌值为三带二大小
                QVector<myCard*> vtmp;
                //重新排序
                for(int i=0;i<chosenCards.size();i++){
                    if(chosenCards[i]->getValue()==va){
                        vtmp.append(chosenCards[i]);
                    }
                }
                for(int i=0;i<chosenCards.size();i++){
                    if(chosenCards[i]->isWildCard){
                        vtmp.append(chosenCards[i]);
                        break;
                    }
                }
                it--;
                va=it.key();
                for(int i=0;i<chosenCards.size();i++){
                    if(chosenCards[i]->getValue()==va){
                        vtmp.append(chosenCards[i]);
                    }
                }
                chosenCards.clear();
                chosenCards=vtmp;
            }
        }
        else{
            setCurCards(0,0,0);                                             //非法
        }
    }
    else if(chosenCards.size()<9){
        if(isEqual(chosenCards,1)){
            setCurCards(chosenCards.size()-1,1,chosenCards[0]->getValue()); //六炸、七炸、八炸
        }
        else if(chosenCards.size()==6){
            std::sort(chosenCards.begin(),chosenCards.end(),cmpInShunZi);
            QMap<int,int> cardMap;
            for(int i=0;i<6;i++){
                if(!chosenCards[i]->isWildCard){
                    if(cardMap.find(chosenCards[i]->getVIS())!=cardMap.end()){
                        cardMap[chosenCards[i]->getVIS()]++;
                    }
                    else{
                        cardMap[chosenCards[i]->getVIS()]=1;
                    }
                }
            }
            QMap<int,int>::iterator it=cardMap.begin();
            if(wildCardCount==0){
                if(cardMap.size()==2){
                    if(it.key()+1==(it+1).key() && it.value()==3){
                        setCurCards(1,5,it.key());                              //三顺
                    }
                    else if(it.key()==-1 && (it+1).key()==11 && it.value()==3){
                        std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                        setCurCards(1,5,11);                                    //kkkaaa
                    }
                    else{
                        setCurCards(0,0,0);
                    }
                }
                else if(cardMap.size()==3){
                    if(it.key()+1==(it+1).key() && (it+1).key()+1==(it+2).key() &&
                       it.value()==2 && (it+1).value()==2){
                        setCurCards(1,7,it.key());                              //三连对
                    }
                    else if(it.key()==-1 && (it+1).key()==10 && (it+2).key()==11 &&
                            it.value()==2 && (it+1).value()==2){
                        std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                        setCurCards(1,7,10);                                    //qqkkaa
                    }
                    else{
                        setCurCards(0,0,0);
                    }
                }
                else{
                    setCurCards(0,0,0);
                }
            }
            else if(wildCardCount==1){
                if(cardMap.size()==2){
                    if(it.key()+1==(it+1).key() && (it.value()==3 || it.value()==2)){   //3+2+1主牌情况
                        setCurCards(1,5,it.key());                              //三顺
                    }
                    else if(it.key()==-1 && (it+1).key()==11 && (it.value()==3 || it.value()==2)){
                        std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                        setCurCards(1,5,11);                                    //kkkaaa
                    }
                    else{
                        setCurCards(0,0,0);
                    }
                }
                else if(cardMap.size()==3){
                    if(it.key()+1==(it+1).key() && (it+1).key()+1==(it+2).key() &&
                       it.value()<=2 && (it+1).value()<=2 && (it+2).value()<=2){    //2+2+1+1主牌情况
                        setCurCards(1,7,it.key());                              //三连对
                    }
                    else if(it.key()==-1 && (it+1).key()==10 && (it+2).key()==11 &&
                            it.value()<=2 && (it+1).value()<=2 && (it+2).value()<=2){
                        std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                        setCurCards(1,7,10);                                    //qqkkaa
                    }
                    else{
                        setCurCards(0,0,0);
                    }
                }
                else{
                    setCurCards(0,0,0);
                }
            }
            else if(wildCardCount==2){
                if(cardMap.size()==2){                  //2+2+2主牌情况
                    if(it.value()==2){
                        int v2=0;
                        if(cardRecord[0]==0){           //无上家选择打三顺还是三连对
                            QPushButton *sanShunbtn = new QPushButton("三顺");
                            QPushButton *sanLianDuibtn = new QPushButton("三连对");
                            QMessageBox *mymsgbox = new QMessageBox;
                            mymsgbox->setIcon(QMessageBox::Warning);
                            mymsgbox->setWindowTitle("提示");
                            mymsgbox->setText("你想打出三顺还是三连对？");
                            mymsgbox->addButton(sanShunbtn, QMessageBox::AcceptRole);
                            mymsgbox->addButton(sanLianDuibtn, QMessageBox::RejectRole);
                            mymsgbox->show();
                            mymsgbox->exec();                           //阻塞等待用户输入
                            if (mymsgbox->clickedButton()==sanShunbtn)  //点击了OK按钮
                            {
                                v2=5;
                            }
                            else{
                                v2=7;
                            }
                        }
                        else if(cardRecord[1]==5.0){            //接上家的三顺
                            v2=5;
                        }
                        else{                                   //其余情况默认三连对
                            v2=7;
                        }
                        if(v2==5){
                            if(it.key()+1==(it+1).key()){
                                setCurCards(1,5,it.key());      //三顺
                            }
                            else if(it.key()==-1 && (it+1).key()==11){
                                std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                                setCurCards(1,5,11);            //kkkaaa
                            }
                            else{
                                setCurCards(0,0,0);
                            }
                        }
                        else if(v2==7){
                            if(it.key()+1==(it+1).key()){
                                setCurCards(1,7,it.key());      //三连对
                            }
                            else if(it.key()==-1 && ((it+1).key()==10 || (it+1).key()==11)){
                                std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                                setCurCards(1,7,10);            //qqkkaa
                            }
                            else{
                                setCurCards(0,0,0);
                            }
                        }
                    }
                    else if(it.value()==3 || it.value()==1){
                        if(it.key()+1==(it+1).key()){
                            setCurCards(1,5,it.key());
                        }
                        else if(it.key()==-1 && (it+1).key()==11){
                            std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                            setCurCards(1,5,11);
                        }
                        else{
                            setCurCards(0,0,0);
                        }
                    }
                    else{
                        setCurCards(0,0,0);
                    }
                }
                else if(cardMap.size()==3){
                    if(it.key()+1==(it+1).key() && (it+1).key()+1==(it+2).key()){
                        setCurCards(1,7,it.key());
                    }
                    else if(it.key()==-1 && (it+1).key()==10 && (it+1).key()==11){
                        std::sort(chosenCards.begin(),chosenCards.end(),cmp1);
                        setCurCards(1,7,10);
                    }
                    else{
                        setCurCards(0,0,0);
                    }
                }
                else{
                    setCurCards(0,0,0);
                }
            }
            else{
                setCurCards(0,0,0);
            }
        }
        else{
            setCurCards(0,0,0);                                             //非法
        }
    }
    else{
        setCurCards(0,0,0);                                                 //非法
    }
}

void guanDanGamespace::findAndEreaseCard(QVector<myCard *> &v, myCard *c)
{
    int id=c->cardID;
    for(int i=0;i<v.size();i++){
        if(v[i]->cardID==id){
            v.erase(v.begin()+i,v.begin()+i+1);
            return;
        }
    }
    qDebug()<<"error: no cards of this id: "<<id;
}

void guanDanGamespace::setAnimationGroup(QVector<myCard *> &v, int player)
{
    group[player]->clear();
    for(int i=0;i<v.size();i++){
        QPoint start(900,500);
        group[player]->addAnimation(v[i]->setAnimation(start,150));
    }
    group[player]->start();
}

void guanDanGamespace::moveTo(QVector<myCard *> &v)
{
    for(int i=0;i<v.size();i++){
        v[i]->move(v[i]->point);
    }
    background->lower();
}

void guanDanGamespace::setInRound(QVector<myCard *> &v)
{
    for(int i=0;i<v.size();i++){
        v[i]->isInRound=1-v[i]->isInRound;
    }
}

void guanDanGamespace::resetCards()
{
    for(int i=0;i<108;i++){
        cards[i]->setPoint(900,500);
        cards[i]->move(cards[i]->point);
        cards[i]->bePlayed=false;
        cards[i]->setStatus(false);
        cards[i]->isInRound=false;
        cards[i]->standAlone=0;
        cards[i]->hide();
        cards[i]->isWildCard=0;
    }
}


void guanDanGamespace::resetGame()
{
    resetCards();
    resetPlayer();
    memset(finishedFlag,0,sizeof(finishedFlag));
    memset(jinGongAnimationFinished,0,sizeof(jinGongAnimationFinished));
    memset(cardRecord,0,sizeof(cardRecord));
    memset(standAloneCount,0,sizeof(standAloneCount));
    chosenCards.clear();
    lastPlayedCards.clear();
    jinGongCards.clear();
    jinGongCardPoint.clear();
    hasJinGong=0;
    successPlayer=0;
    oneSuceed=0;
    wildCardCount=0;
    maxJingGongCard=0;
}

void guanDanGamespace::resetPlayer()
{
    for(int i=0;i<4;i++){
        player[i].clear();
//        wildCards[i].clear();
    }
}

void guanDanGamespace::movePlayAndSkipButton()
{
    playCardsButton->move(*playCardsButtonPoint[whoseRound]);
    skipButton->move(*skipButtonPoint[whoseRound]);
}

void guanDanGamespace::setPlayerPlaceAndWay()
{
    playerPlaceAndWay[0][0]=WINHEIGHT-cardHeight*SCALE-20;
    playerPlaceAndWay[0][1]=1;
    playerPlaceAndWay[1][0]=20;
    playerPlaceAndWay[1][1]=2;
    playerPlaceAndWay[2][0]=cardHeight*SCALE*2+20;
    playerPlaceAndWay[2][1]=1;
    playerPlaceAndWay[3][0]=WINWIDTH-cardWidth*SCALE*4-20;
    playerPlaceAndWay[3][1]=2;

}

void guanDanGamespace::setOneCard(int index, int value, int suit, int vis)
{
    cards[index]= new myCard(index,value,suit,vis,cardGroupPix,cardWidth,cardHeight,this);
    connect(cards[index],SIGNAL(clicked()),this,SLOT(chooseAndJudge()));
    connect(cards[index],SIGNAL(animationFinished(int)),this,SLOT(getCardAnimationFinshedID(int)));
}

void guanDanGamespace::successAssess()
{
    successOrder[successPlayer-1]=whoseRound;                       //记录上岸顺序
    if((player[0].empty() && player[2].empty()) || (player[1].empty() && player[3].empty())){   //单局获胜条件
        gameRound++;                                                                            //对局场数加一
        if(playerGrade[successOrder[0]]==12){   //游戏结束
            QMessageBox::information(nullptr, "-。-", "whole game over!", QMessageBox::Yes);
        }
        QMessageBox::information(nullptr, "-。-", "game over", QMessageBox::Yes);
        if(successPlayer==2){   //双下情况
            winWay=3;
            if(player[0].empty() && player[2].empty()){
                successOrder[2]=1;
                successOrder[3]=3;
            }
            else{
                successOrder[2]=0;
                successOrder[3]=2;
            }
            playATimes(successOrder[2]);
        }
        else if(successPlayer==3){
            if(player[partner[successOrder[0]]].empty()){   //对手有一家是末游
                winWay=2;
                successOrder[3]=partner[successOrder[1]];
                playATimes(successOrder[1]);
            }
            else{                                           //赢家自己对门是末游
                winWay=1;
                successOrder[3]=partner[successOrder[0]];
                playATimes(successOrder[1]);
            }           
        }
        playerGrade[successOrder[0]]+=winWay;
        if(playerGrade[successOrder[0]]>12){
            playerGrade[successOrder[0]]=12;
            winFlag[successOrder[0]]=1;
        }
        playerGrade[partner[successOrder[0]]]=playerGrade[successOrder[0]];
        winFlag[partner[successOrder[0]]]=winFlag[successOrder[0]];
        playCardsButton->hide();
        skipButton->hide();
        whoseRound=successOrder[0];                         //将第一个上岸的人变为下一把先手的人
        startGameButton->setText("开始下一把");
        startGameButton->show();
        startGameButton->raise();
        qDebug()<<"0: "<<playerGrade[0]<<endl<<"1: "<<playerGrade[1]<<endl<<"2: "<<playerGrade[2]<<endl<<"3: "<<playerGrade[3];
        return;
    }
    else oneSuceed=true;                                    //单局未结束，设置当前回合有人上岸为true
}

void guanDanGamespace::autoJinGong(int who)
{
    jinGongCards.clear();
    jinGongCardPoint.clear();
    if(player[who].back()->getValue()>maxJingGongCard){     //如果进贡的牌比已经进贡的所有牌都大，则设置进贡方为下局先手玩家
        maxJingGongCard=player[who].back()->getValue();
        whoseRound=who;
    }
    player[successOrder[0]].append(player[who].back());
    qDebug()<<"card (value"<<player[who].back()->getValue()<<") of player"<<who<<" is given to "<<"the first(player "<<successOrder[0]<<")";
    jinGongCards.append(player[who].back());
    jinGongCardPoint.append(player[who].back()->point);
    player[who].pop_back();
    setRightPoint(player[successOrder[0]],playerPlaceAndWay[successOrder[0]][0],playerPlaceAndWay[successOrder[0]][1]);
    moveTo(player[successOrder[0]]);
    if(winWay==3){                                          //如果是双下情况，则还需进贡一张牌
        player[successOrder[1]].append(player[who].back());
        qDebug()<<"card (value"<<player[who].back()->getValue()<<") of player"<<who<<" is given to "<<"the first(player "<<successOrder[1]<<")";
        jinGongCards.append(player[who].back());
        jinGongCardPoint.append(player[who].back()->point);
        player[who].pop_back();
        setRightPoint(player[successOrder[1]],playerPlaceAndWay[successOrder[1]][0],playerPlaceAndWay[successOrder[1]][1]);
        moveTo(player[successOrder[1]]);
    }
    setRightPoint(player[who],playerPlaceAndWay[who][0],playerPlaceAndWay[who][1]);
    moveTo(player[who]);
    background->lower();
}

void guanDanGamespace::autoShowAfterAnimation()
{
    jinGongFlag=0;
    movePlayAndSkipButton();
    playCardsButton->setEnabled(false);
    skipButton->setEnabled(false);
    playCardsButton->show();
    skipButton->show();
    jinGongButton->hide();
    kangGongButton->hide();
    setInRound(player[whoseRound]);
    tongHuaShunTip();
    for(int i=0;i<4;i++){
        std::sort(player[i].begin(),player[i].end(),cmp1);
        setRightPoint(player[i],playerPlaceAndWay[i][0],playerPlaceAndWay[i][1]);
        moveTo(player[i]);
    }
//    cardPile->hide();
    background->lower();
}

void guanDanGamespace::setJinGongAnimation()
{
    memset(jinGongAnimationFinished,0,sizeof(jinGongAnimationFinished));
    QPropertyAnimation * anim[4];
    for(int i=0;i<jinGongCards.size();i++){
        anim[i]=jinGongCards[i]->setAnimation(jinGongCardPoint[i],1000);
        anim[i]->start();
    }
}

void guanDanGamespace::setHuanPaiAnimation()
{
    QPropertyAnimation * anim;
    anim=chosenCards[0]->setAnimation(huanPaiPoint,1000);
    anim->start();
}

void guanDanGamespace::jinGongJudge()
{
    int count=0;
    if(winWay==3){
        //双下情况，计算大王数量
        for(int i=2;i<4;i++){
            for(int j=player[successOrder[i]].size()-1;j>0;j--){
                if(player[successOrder[i]][j]->getValue()<15) break;
                count++;
            }
        }
    }
    else{
        //单下情况，计算大王数量
        for(int i=player[successOrder[3]].size()-1;i>0;i--){
            if(player[successOrder[3]][i]->getValue()<15) break;
            count++;
        }
    }
    if(count>1){
        //有两张大王可抗贡
        kangGongButton->setEnabled(true);
    }
    else{
        kangGongButton->setEnabled(false);
    }
    kangGongButton->move(*skipButtonPoint[successOrder[3]]);
    kangGongButton->show();
    jinGongButton->move(*playCardsButtonPoint[successOrder[3]]);
    jinGongButton->show();
}

void guanDanGamespace::playATimes(int player)
{
    if(winFlag[player]){
        if(winFlag[player]<3){      //记录打A的局数
            winFlag[player]++;
            winFlag[partner[player]]++;
        }
        else{                       //三局未成功上岸返回打2
            winFlag[player]=0;
            winFlag[partner[player]]=0;
            playerGrade[player]=0;
            playerGrade[partner[player]]=0;
        }
    }
}

void guanDanGamespace::tongHuaShunTip()
{
    for(int i=0;i<blinkCard.size();i++){
        blinkCard[i]->show();
    }
    blinkCard.clear();
    if(haveShunZi(player[whoseRound])){
        QVector<myCard* > &v=player[whoseRound];
        bool cardSuit[18][4];                   //cardSuit[i][j]记录牌值为i(i-13)的各花色存在情况
        memset(cardSuit,0,sizeof(cardSuit));
        int suitDp[14][4];                      //suitDp[i][j]:牌值i~i+4各花色的存在个数
        memset(suitDp,0,sizeof(suitDp));
        int wildCount=0;                        //主牌单独计算个数
        for(int i=0;i<v.size();i++){
            if(v[i]->getValue()<14){
                if(v[i]->isWildCard){
                    wildCount++;
                }
                else{
                    cardSuit[v[i]->getValue()][v[i]->getSuit()]=1;
                    if(v[i]->getValue()+13<18){
                       cardSuit[v[i]->getValue()+13][v[i]->getSuit()]=1;
                    }
                }
            }
        }
        for(int i=1;i<=5;i++){
            for(int j=0;j<4;j++){
                suitDp[1][j]+=cardSuit[i][j];
            }
        }
        for(int i=2;i<=13;i++){
            for(int j=0;j<4;j++){
                suitDp[i][j]=suitDp[i-1][j]-cardSuit[i-1][j]+cardSuit[i+4][j];
            }
        }
        //默认提示最大的同花顺
        for(int i=8;i>=1;i--){
            for(int j=0;j<4;j++){
                if(suitDp[i][j]+wildCount>=5){
                    qDebug()<<"has tongHuaShun i:"<<i;
                    if(suitDp[i][j]>=5){
                        setBlinkCards(v,i,j,0); //0标记不需要取主牌
                    }
                    else{
                        setBlinkCards(v,i,j,5-suitDp[i][j]);
                    }
                    return;
                }
            }
        }
        for(int i=12;i<=13;i++){            //最小的A,3,4,5,6 与 2,3,4,5.6最后考虑
            for(int j=0;j<4;j++){
                if(suitDp[i][j]+wildCount>=5){
                    qDebug()<<"has tongHuaShun i:"<<i;
                    if(suitDp[i][j]>=5){
                        setBlinkCards(v,i,j,0);
                    }
                    else{
                        setBlinkCards(v,i,j,5-suitDp[i][j]);
                    }
                    return;
                }
            }
        }
    }
}

void guanDanGamespace::setBrightLabel(myCard *card)
{
    card->cardLabel[0]->setVisible(true);
    card->cardLabel[1]->setVisible(false);
    card->setStatus(false);
}

void guanDanGamespace::setBlinkCards(QVector<myCard *> &v, int begin, int suit, int needWildCard)
{
    int value=begin;
    int end=begin+4;
    while(value<=end){
        bool flag=1;
        for(int i=0;i<v.size();i++){
            if(v[i]->getSuit()==suit && v[i]->getValue()==((value-1)%13+1)){
                value++;
                flag=0;
                blinkCard.append(v[i]);
                break;
            }
        }
        if(flag) value++;
    }
    if(needWildCard){           //将所需要的主牌加入提示
        for(int i=0;i<v.size();i++){
            if(v[i]->isWildCard){
                blinkCard.append(v[i]);
                needWildCard--;
                if(needWildCard==0) break;
            }
        }
    }
    stopBlink=0;
}

bool guanDanGamespace::haveShunZi(QVector<myCard *> &v)
{
    if(v.size()<5) return false;
    bool cardValue[18]={0};
    int dp[14]={0};                         //以当前值为起始，前面5个（包括自己）牌值中有几个存在
    int wildCount=0;                        //主牌个数
    int max;                                //dp最大值
    for(int i=0;i<v.size();i++){
        if(v[i]->getValue()<14){
            if(v[i]->isWildCard){
                wildCount++;
            }
            else{
                cardValue[v[i]->getValue()]=1;
                if(v[i]->getValue()+13<18){
                   cardValue[v[i]->getValue()+13]=1;
                }
            }
        }
    }
//    qDebug()<<"wildCount: "<<wildCount;
    for(int i=1;i<=5;i++){
        if(cardValue[i]){
            dp[1]++;
        }
    }
    max=dp[1];
    for(int i=2;i<=13;i++){
        dp[i]=dp[i-1]-cardValue[i-1]+cardValue[i+4];
        if(i<=8 || i>=12) max=max<dp[i]?dp[i]:max;
    }
    if(max+wildCount>=5) return true;
    return false;
}

bool guanDanGamespace::haveValue(QVector<myCard *> &v, int va)
{
    for(int i=0;i<v.size();i++){
        if(v[i]->getValue()==va) return true;
    }
    return false;
}

guanDanGamespace::guanDanGamespace(QWidget *parent) : QWidget(parent)
{
    //设置键盘焦点，以便响应快捷键
    setFocusPolicy(Qt::StrongFocus);
    //设置大小
    setFixedSize(WINWIDTH,WINHEIGHT);
    //设置背景
    background= new QLabel(this);
    background->resize(WINWIDTH,WINHEIGHT);
    background->setPixmap(QPixmap(":/imag/image/basebackground0.png").scaled(background->size()));
    background->setFocusPolicy(Qt::NoFocus);
    //设置开始按钮
    startGameButton = new QPushButton("开始游戏",this);
    startGameButton->move(WINWIDTH/2-80,WINHEIGHT/2-40);
    startGameButton->resize(160,80);
    startGameButton->setStyleSheet("QPushButton{font-family:'宋体';font-size:32px;color:rgb(0,0,0,255);}\
                                    QPushButton:hover{background-color:rgb(50, 170, 200)}\
                                    QPushButton{background-color:rgb(170,200,50)}");
    //设置出牌按钮
    playCardsButton = new QPushButton("出牌",this);
    playCardsButton->hide();
    playCardsButton->resize(80,50);
    //设置跳过按钮
    skipButton = new QPushButton("不出",this);
    skipButton->hide();
    skipButton->resize(80,50);
    //设置抗贡按钮
    kangGongButton = new QPushButton("抗贡",this);
    kangGongButton->hide();
    kangGongButton->resize(80,50);
    kangGongButton->setEnabled(true);
    //设置进贡按钮
    jinGongButton = new QPushButton("进贡",this);
    jinGongButton->hide();
    jinGongButton->resize(80,50);
    jinGongButton->setEnabled(true);
    //设置还牌按钮
    huanPaiButton = new QPushButton("还牌",this);
    huanPaiButton->hide();
    huanPaiButton->resize(80,50);
    //设置扑克参数
    cardGroupPix[0].load(":/imag/image/cards.png");         //获取扑克组图
    cardGroupPix[1].load(":/imag/image/cards_shadow.png");  //获取被选中状态的扑克图组
    cardWidth=cardGroupPix[0].width()/14;                   //获取单张扑克的宽度
    cardHeight=cardGroupPix[0].height()/4;
    setCards();
    //设置牌堆图片
    cardPile=new QLabel(this);
    cardPile->resize(150,150);
    cardPile->move(WINWIDTH/2-20,WINHEIGHT/2);
    cardPile->setPixmap(QPixmap(":/imag/image/cardsss.png"));
//    qDebug()<<QPixmap(":/imag/image/cardsss.png").width()<<' '<<QPixmap(":/imag/image/cardsss.png").height();
    cardPile->hide();
    //设置四家扑克的摆放位置元素与方法
    setPlayerPlaceAndWay();
    //设置出牌按钮的四个坐标
    playCardsButtonPoint[0]=new QPoint(WINWIDTH/2-80*1.5,playerPlaceAndWay[0][0]-cardHeight*SCALE*2-20);
    playCardsButtonPoint[1]=new QPoint(playerPlaceAndWay[1][0]+cardWidth*SCALE*4+20,WINHEIGHT/2-50*1.5);
    playCardsButtonPoint[2]=new QPoint(WINWIDTH/2-80*1.5,playerPlaceAndWay[2][0]+cardHeight*SCALE+20);
    playCardsButtonPoint[3]=new QPoint(playerPlaceAndWay[3][0]-40-80,WINHEIGHT/2-50*1.5);
    //设置跳过按钮的四个坐标
    skipButtonPoint[0]=new QPoint(WINWIDTH/2+80*0.5,playerPlaceAndWay[0][0]-cardHeight*SCALE*2-20);
    skipButtonPoint[1]=new QPoint(playerPlaceAndWay[1][0]+cardWidth*SCALE*4+20,WINHEIGHT/2+50*0.5);
    skipButtonPoint[2]=new QPoint(WINWIDTH/2+80*0.5,playerPlaceAndWay[2][0]+cardHeight*SCALE+20);
    skipButtonPoint[3]=new QPoint(playerPlaceAndWay[3][0]-40-80,WINHEIGHT/2+50*0.5);
    //设置还牌按钮的四个坐标
    huanPaiButtonPoint[0]=new QPoint(WINWIDTH/2-80/2,playerPlaceAndWay[0][0]-cardHeight*SCALE*2-20);
    huanPaiButtonPoint[1]=new QPoint(playerPlaceAndWay[1][0]+cardWidth*SCALE*4+20,WINHEIGHT/2-50/2);
    huanPaiButtonPoint[2]=new QPoint(WINWIDTH/2-80/2,playerPlaceAndWay[2][0]+cardHeight*SCALE+20);
    huanPaiButtonPoint[3]=new QPoint(playerPlaceAndWay[3][0]-40-80,WINHEIGHT/2-50/2);
    //设置串行动画组
    for(int i=0;i<4;i++){
        group[i]=new QSequentialAnimationGroup;
    }
    //第一轮随机选择先手玩家
    QTime t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    whoseRound=qrand()%4;
    lastPlayer=whoseRound;
    //设置队友
    partner[0]=2;
    partner[1]=3;
    partner[2]=0;
    partner[3]=1;
    //初始化
    jinGongFlag=0;
    huanPaiFlag=0;
    gameRound=0;
    wildCardCount=0;
    stopBlink=1;
    maxJingGongCard=0;
    memset(playerGrade,0,sizeof(playerGrade));
    memset(cardRecord,0,sizeof(cardRecord));
    memset(curCards,0,sizeof(curCards));
    memset(winFlag,0,sizeof(winFlag));
    memset(standAloneCount,0,sizeof(standAloneCount));
    //设置计时器
    QTimer *blinkTimer = new QTimer();
    blinkTimer->start(300);
    //信号与槽函数
    connect(blinkTimer,SIGNAL(timeout()),this,SLOT(blink()));                   //连接计时器和闪烁功能
    connect(startGameButton,SIGNAL(clicked()),this,SLOT(dealCards()));          //连接单击开始按钮和发牌功能
    connect(playCardsButton,SIGNAL(clicked()),this,SLOT(playCards()));          //连接单击出牌按钮与出牌功能
    connect(skipButton,SIGNAL(clicked()),this,SLOT(skip()));                    //连接单击跳过按钮与跳过功能
    connect(jinGongButton,SIGNAL(clicked()),this,SLOT(jinGong()));              //连接单击进贡按钮与进贡功能
    connect(kangGongButton,SIGNAL(clicked()),this,SLOT(kangGong()));            //连接单击抗贡按钮与抗贡功能
    connect(huanPaiButton,SIGNAL(clicked()),this,SLOT(huanPai()));              //连接单击抗贡按钮与抗贡功能
    connect(this,SIGNAL(animationAllFinished()),this,SLOT(afterAnimation()));   //连接动画结束信号与显示控件功能
}

void guanDanGamespace::setCards()
{
    //设置3~2的牌
    for(int i=0;i<4;i++){
        for(int j=1;j<=13;j++){
            for(int k=0;k<2;k++){
                int index=(i*13+j-1)*2+k;
                int vis=(j>=12?j-13:j);
                setOneCard(index,j,i,vis);
            }
        }
    }
    //小王
    for(int i=104;i<106;i++){
        setOneCard(i,14,0,14);
    }
    //大王
    for(int i=106;i<108;i++){
        setOneCard(i,15,1,15);
    }
}

void guanDanGamespace::keyPressEvent(QKeyEvent *event)
{
    if((curCards[0]==1.0 && curCards[1]==6.0) || curCards[0]==4.0){
        if(event->key()==Qt::Key_Shift){        //顺子单独出列快捷键shitf
            int standAloneTmp=0;
            if(chosenCards[0]->standAlone){     //取消出列的情况
                standAloneCount[whoseRound]--;
            }
            else{                               //出列的情况
                standAloneCount[whoseRound]++;
                standAloneTmp=standAloneCount[whoseRound];
            }
            qDebug()<<"standAloneCount["<<whoseRound<<"] "<<standAloneCount[whoseRound];
            for(int i=0;i<chosenCards.size();i++){
                chosenCards[i]->standAlone=standAloneTmp;
                setBrightLabel(chosenCards[i]);
            }
            chosenCards.clear();
            memset(curCards,0,sizeof(curCards));
            std::sort(player[whoseRound].begin(),player[whoseRound].end(),cmp0);
            setRightPoint(player[whoseRound],playerPlaceAndWay[whoseRound][0],playerPlaceAndWay[whoseRound][1]);
            moveTo(player[whoseRound]);
            playCardsButton->setEnabled(false);
        }
    }
    else if(event->key()==Qt::Key_T){           //同花顺提示快捷键T
        stopBlink=1-stopBlink;
    }
}

void guanDanGamespace::dealCards()
{
    resetGame();                //重置对局
    startGameButton->hide();
    cardPile->show();
    int count=107;
    dealList.clear();
    QTime t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    //创建随机列表
    while(count>=0){
        int cardId=qrand()%108;
        if(!dealList.contains(cardId)){
            dealList.append(cardId);
            count--;
        }
    }
    //四个玩家获取牌
    int index;
    for(int i=0;i<108;i++){
        index=i/27;
        player[index].append(cards[dealList[i]]);
        if(playerGrade[index]==0 && cards[dealList[i]]->getValue()==13 && cards[dealList[i]]->getSuit()==1){
            cards[dealList[i]]->isWildCard=1;
            qDebug()<<"card id: "<<cards[dealList[i]]->cardID<<" value: "<<cards[dealList[i]]->getValue()<<" is wild card";
        }
        else if(cards[dealList[i]]->getValue()==playerGrade[index] && cards[dealList[i]]->getSuit()==1){
            cards[dealList[i]]->isWildCard=1;
            qDebug()<<"card id: "<<cards[dealList[i]]->cardID<<" value: "<<cards[dealList[i]]->getValue()<<" is wild card";
        }
        cards[dealList[i]]->show();
    }
    //扑克排序 and 设置初始坐标 and 生成四个串行动画组
    for(int i=0;i<4;i++){
        std::sort(player[i].begin(),player[i].end(),cmp1);
        setRightPoint(player[i],playerPlaceAndWay[i][0],playerPlaceAndWay[i][1]);
        setAnimationGroup(player[i],i);
    }
    cardPile->raise();
    background->lower();
}

void guanDanGamespace::chooseAndJudge()
{
    stopBlink=1;
    myCard* chosenCard=(myCard*) sender();                  //获取发送信号的扑克
    if(!chosenCard->bePlayed && chosenCard->isInRound){     //判断是否 是已经被打出的牌 或者 是不在当前回合玩家的牌
        bool status=chosenCard->getStatus();
        status=1-status;
        chosenCard->cardLabel[status]->setVisible(true);    //改变显示的扑克图片
        chosenCard->cardLabel[1-status]->setVisible(false);
        chosenCard->setStatus(status);                      //改变选中状态
        if(status){
            chosenCards.append(chosenCard);                 //如果选中则加入选中卡牌组
            if(chosenCard->isWildCard){
                wildCardCount++;
            }
        }
        else{
            findAndEreaseCard(chosenCards,chosenCard);      //如果是取消选择就从选中卡牌组中删除
            if(chosenCard->isWildCard){
                wildCardCount--;
            }
        }
        if(huanPaiFlag){
            if(chosenCards.size()!=1 || chosenCards[0]->getValue()>8){
                huanPaiButton->setEnabled(false);
            }
            else{
                huanPaiButton->setEnabled(true);
                huanPaiPoint=chosenCards[0]->point;
            }
            return;
        }
        judgeCardsKind();                                   //判断选中卡牌组的牌型
        for(int i=0;i<3;i++){
            qDebug()<<"curCard v"<<i<<" :"<<curCards[i];
        }
        if(curCards[0]==0.0){
            playCardsButton->setEnabled(false);             //非法情况，禁用出牌按钮
        }
        else if(cardRecord[0]==0.0){
            playCardsButton->setEnabled(true);              //为回合第一个出牌情况，允许出任意牌
        }
        else if(curCards[0]>cardRecord[0]){
            playCardsButton->setEnabled(true);              //牌型大于上家，允许出牌
        }
        else if(curCards[0]==cardRecord[0] && curCards[1]==cardRecord[1] && curCards[2]>cardRecord[2]){
            playCardsButton->setEnabled(true);              //牌值大于上家，允许出牌
        }
        else{
            playCardsButton->setEnabled(false);             //其他情况，禁用出牌按钮
        }
    }
}

void guanDanGamespace::playCards()
{
    int gameRoundTemp=gameRound;
    if(oneSuceed) oneSuceed=0;                                  //如果有人这回合上岸而被人接住了牌，则状态置0
    for(int i=0;i<lastPlayedCards.size();i++){                  //上一次打出的牌隐藏
        lastPlayedCards[i]->hide();
    }
    lastPlayedCards.clear();                                    //清空上次打出的牌的记录
    for(int i=0;i<chosenCards.size();i++){
        setBrightLabel(chosenCards[i]);
        chosenCards[i]->bePlayed=1;                             //设置为已被打出的牌
        findAndEreaseCard(player[whoseRound],chosenCards[i]);   //从玩家手中移除打出的牌
        lastPlayedCards.append(chosenCards[i]);                 //记录到上一次打出的牌中
    }
    setCardRecord(curCards[0],curCards[1],curCards[2]);         //当前打出的牌型牌值设置为上一次打出的牌型牌值
    setInLine(chosenCards,500);
    setCenterPoint1(chosenCards);
    moveTo(chosenCards);
    if(!player[whoseRound].empty()){                            //如果打出牌的玩家还有牌就整理ta的牌
        setRightPoint(player[whoseRound],playerPlaceAndWay[whoseRound][0],playerPlaceAndWay[whoseRound][1]);
        moveTo(player[whoseRound]);
    }
    else{                                                       //如果打出牌的玩家没牌了则成功上岸
        successPlayer++;
        successAssess();
    }
    if(gameRoundTemp==gameRound){                               //如果当前这局没有结束
        lastPlayer=whoseRound;                                  //当前出牌的人设为上一个出牌的人
        setInRound(player[whoseRound]);                         //使当前玩家不处于回合
        whoseRound=(whoseRound+1)%4;                            //取顺位下家
        while(player[whoseRound].empty()){
            whoseRound=(whoseRound+1)%4;                        //找到还有牌的下家
        }
        chosenCards.clear();                                    //清空选中卡牌
        wildCardCount=0;
        setInRound(player[whoseRound]);                         //使下家处于回合
        tongHuaShunTip();
        movePlayAndSkipButton();
        playCardsButton->setEnabled(false);
        skipButton->setEnabled(true);
    }
}

void guanDanGamespace::skip()
{
    //恢复选中牌的显示
    for(int i=0;i<chosenCards.size();i++){
        setBrightLabel(chosenCards[i]);
    }
    chosenCards.clear();
    setInRound(player[whoseRound]);                             //使当前玩家不处于回合
//    int tmp=whoseRound;
    whoseRound=(whoseRound+1)%4;                                //取顺位下家
    if(oneSuceed){                                              //如果是有人上岸的回合
        while(player[whoseRound].empty() && whoseRound!=lastPlayer){
            whoseRound=(whoseRound+1)%4;                        //找到还有牌的下家 或者 已经回到上岸的玩家
        }
        if(whoseRound==lastPlayer){                             //如果回到上岸的玩家
            oneSuceed=0;
            //接风功能
            if(whoseRound==0 || whoseRound==2){
                whoseRound=2-whoseRound;
            }
            else{
                whoseRound=4-whoseRound;
            }
            lastPlayer=whoseRound;
        }
//        else if(player[whoseRound].empty() && (whoseRound+1)%4==lastPlayer){
//            lastPlayer=tmp;
//            whoseRound=tmp;
//        }
    }
    else{
        while(player[whoseRound].empty()){
            whoseRound=(whoseRound+1)%4;                        //找到还有牌的下家
        }
    }
    if(lastPlayer==whoseRound){                                 //如果回到上次出牌的人
        for(int i=0;i<lastPlayedCards.size();i++){
            lastPlayedCards[i]->hide();                         //隐藏上次打出的牌
        }
        memset(cardRecord,0,sizeof(cardRecord));                //重置牌型牌值记录
        skipButton->setEnabled(false);                          //第一个出牌的不能跳过
    }
    setInRound(player[whoseRound]);                             //设置下家为在回合玩家
    tongHuaShunTip();
    playCardsButton->setEnabled(false);
    movePlayAndSkipButton();
}

void guanDanGamespace::getCardAnimationFinshedID(int id)
{
    if(huanPaiFlag){                                //还牌动画
        if(winWay<3){
            huanPaiFlag=0;                          //如果不是双下则结束进贡、还牌阶段
        }
        else if(huanPaiPlayer==successOrder[1]){    //双下且是第二名还牌
            huanPaiFlag=0;
            if(hasJinGong==1){                      //进贡阶段未结束，进入第二个进贡
                jinGongFlag=1;
            }
        }
        else if(huanPaiPlayer==successOrder[0]){
            huanPaiPlayer=successOrder[1];          //双下且是头家还牌结束，进入第二名还牌阶段
        }
        chosenCards.clear();
        emit animationAllFinished();
    }
    else if(jinGongFlag){                           //进贡动画
        bool flag=1;                                //标记进贡动画结束
        for(int i=0;i<jinGongCards.size();i++){
            if(id==jinGongCards[i]->cardID){
                jinGongAnimationFinished[i]=1;
                break;
            }
        }
        for(int i=0;i<jinGongCards.size();i++){
            if(jinGongAnimationFinished[i]==0){
                flag=0;
                break;
            }
        }
        if(flag){
            huanPaiFlag=1;
            jinGongFlag=0;
            huanPaiPlayer=successOrder[0];
//            qDebug()<<"huan pai player "<<huanPaiPlayer;
            emit animationAllFinished();            //所有动画已经结束
        }
    }
    else{                                           //发牌动画
        if(id==player[0][26]->cardID){
            finishedFlag[0]=1;                      //玩家一动画结束
        }
        else if(id==player[1][26]->cardID){
            finishedFlag[1]=1;                      //玩家二动画结束
        }
        if(id==player[2][26]->cardID){
            finishedFlag[2]=1;                      //玩家三动画结束
        }
        if(id==player[3][26]->cardID){
            finishedFlag[3]=1;                      //玩家四动画结束
        }
        if(finishedFlag[0] && finishedFlag[1] && finishedFlag[2] && finishedFlag[3]){
            if(gameRound>0) jinGongFlag=1;
            cardPile->hide();
            emit animationAllFinished();            //所有动画已经结束
        }
    }
}

void guanDanGamespace::afterAnimation()
{
    if(jinGongFlag && hasJinGong==0){       //下一阶段为首次进贡
        jinGongJudge();
    }
    else if(jinGongFlag){                   //下一阶段为二次进贡
        kangGongButton->move(*skipButtonPoint[successOrder[2]]);
        kangGongButton->show();
        kangGongButton->raise();
        jinGongButton->move(*playCardsButtonPoint[successOrder[2]]);
        jinGongButton->show();
        jinGongButton->raise();
    }
    else if(huanPaiFlag){                   //下一阶段为还牌
        if(hasJinGong==1){                  //第一次进贡后设置末游为还牌对象
            huanPaiToWho=successOrder[3];
        }
        else{                               //第二次进贡后设置第三名为还牌对象
            huanPaiToWho=successOrder[2];
        }
        qDebug()<<"huan pai player "<<huanPaiPlayer;
        huanPaiButton->move(*huanPaiButtonPoint[huanPaiPlayer]);
        huanPaiButton->setEnabled(false);
        huanPaiButton->show();
        huanPaiButton->raise();
        setInRound(player[huanPaiPlayer]);
    }
    else{
        autoShowAfterAnimation();           //进贡完成，开始对局
//        rightCards->show();
//        leftCards->show();
    }

}

void guanDanGamespace::jinGong()
{
    hasJinGong++;
    if(hasJinGong==1){                  //末游进贡
        autoJinGong(successOrder[3]);
        jinGongButton->hide();
        kangGongButton->hide();
        setJinGongAnimation();
    }
    else{                               //第三名进贡
        autoJinGong(successOrder[2]);
        jinGongButton->hide();
        kangGongButton->hide();
        setJinGongAnimation();
    }
}

void guanDanGamespace::kangGong()
{
    hasJinGong++;
    if(winWay==3 && hasJinGong==1){ //双下情况到第三名选择是否进贡
        jinGongButton->move(*playCardsButtonPoint[successOrder[2]]);
        kangGongButton->move(*skipButtonPoint[successOrder[2]]);
    }
    else{
        autoShowAfterAnimation();
    }
}

void guanDanGamespace::huanPai()
{
    qDebug()<<"card (value"<<chosenCards[0]->getValue()<<") of player"<<huanPaiPlayer<<" is given to "<<"the player "<<huanPaiToWho;
    setBrightLabel(chosenCards[0]);
    setInRound(player[huanPaiPlayer]);
    player[huanPaiToWho].append(chosenCards[0]);
    findAndEreaseCard(player[huanPaiPlayer],chosenCards[0]);
    setRightPoint(player[huanPaiPlayer],playerPlaceAndWay[huanPaiPlayer][0],playerPlaceAndWay[huanPaiPlayer][1]);
    setRightPoint(player[huanPaiToWho],playerPlaceAndWay[huanPaiToWho][0],playerPlaceAndWay[huanPaiToWho][1]);
    moveTo(player[huanPaiPlayer]);
    moveTo(player[huanPaiToWho]);
    setHuanPaiAnimation();
    huanPaiButton->hide();
}

void guanDanGamespace::blink()
{
    if(!stopBlink){
        for(int i=0;i<blinkCard.size();i++){
            if(blinkCard[i]->isVisible()){
                blinkCard[i]->hide();
            }
            else{
                blinkCard[i]->show();
            }
        }
    }
    else{
        for(int i=0;i<blinkCard.size();i++){
            blinkCard[i]->show();
        }
    }
}
