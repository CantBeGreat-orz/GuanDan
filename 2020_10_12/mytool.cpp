#include "mytool.h"


bool isEqual(int a, int b, int c)
{
    if(a==b && b==c) return true;
    return false;
}

bool isEqual(QVector<myCard *> &cc, int way)
{
    if(way==1){
        int base=0;
        for(int i=0;i<cc.size();i++){
            if(!cc[i]->isWildCard){
                base=cc[i]->getValue();
                break;
            }
        }
        for(int i=0;i<cc.size();i++){
            if(cc[i]->getValue()!=base && !cc[i]->isWildCard){
                return false;
            }
        }
        return true;
    }
    else if(way==2){
        int base=0;
        for(int i=0;i<cc.size();i++){
            if(!cc[i]->isWildCard){
                base=cc[i]->getSuit();
                break;
            }
        }
        for(int i=0;i<cc.size();i++){
            if(cc[i]->getSuit()!=base & !cc[i]->isWildCard) return false;
        }
        return true;
    }
    return false;
}
