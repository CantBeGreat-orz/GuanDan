#ifndef MYTOOL_H
#define MYTOOL_H

#include <QVector>
#include "mycard.h"

bool isEqual(int a, int b, int c);              //
bool isEqual(QVector<myCard *> &cc, int way);     //way=1,判断牌值是否相等；way==2，判断花色是否一致


#endif // MYTOOL_H
