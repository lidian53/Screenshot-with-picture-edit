#include "myrect.h"
#include <QPainter>
#include <QDebug>
#include <QPen>

MyRect::MyRect()
{

}

MyRect::MyRect(QRectF rect) : rect(rect.x(), rect.y(), rect.width(), rect.height())
{

}

void MyRect::setText(QString str)
{
    this->str = str;
}

void MyRect::setLocation(qreal x, qreal y)
{
    //设置左边界的坐标，右边界保持不变
    rect.setX(x);
    rect.setY(y - 21);
    //设置长度为正,相当于设置右边界
    rect.setWidth(71);
    rect.setHeight(21);
}

void MyRect::drawMe(QPainter &painter)
{


    painter.save();
    painter.setPen(QPen());
    painter.setBrush(QColor(0, 0, 0, 150));
    painter.drawRect(rect);
    //设置白色文字
    painter.setPen(QColor(255, 255, 255));
    //居中画出文字
    painter.drawText(rect, Qt::AlignCenter, str);
    painter.restore();

}
