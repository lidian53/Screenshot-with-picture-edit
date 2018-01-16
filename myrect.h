#ifndef MYRECT_H
#define MYRECT_H
#include <QObject>
#include <QRectF>
#include <QString>
#include<QVector>
class QPainter;

//显示当前的width和height
class MyRect : public QObject
{
        Q_OBJECT
public:
    MyRect();

    MyRect(QRectF rect);

    void setText(QString str);
    //绘制自身
    void drawMe(QPainter &);

    void setLocation(qreal x, qreal y);

private:
    QRectF rect;    //保存的一个Rect
    QString str;


};

#endif // MYRECT_H
