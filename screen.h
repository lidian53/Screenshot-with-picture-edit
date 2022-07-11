#ifndef SCREEN_H
#define SCREEN_H
#include <QWidget>
#include "myrect.h"
#include"qslabel.h"
#include"controlwidget.h"
#include"qpainterpath.h"
enum Type {
    RECT1, RECT2, RECT3, RECT4, RECT, NO
};


class QSLabel;
class ControlWidget;

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = 0);
    void drawline();
    void textedit();
    void drawarrow();
    void drawround();
    void drawrectang();
    void returnEdit();
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void setselectimagelabel(QMouseEvent* event);

    void keyPressEvent(QKeyEvent *e);
    //绘制控制选区，也就是四个小三角
    void drawControlArea(QPainter &);

    bool comparePoint(QPoint &p1, QPoint &p2);

    bool compareRect(QRectF &r1, QRectF &r2);

    Type pointInWhere(QPoint p);
    //返回截取之后的图片
    QPixmap getGrabPixmap();

    QPainterPath getPath();
    //保存截图
    void savePixmap();

    virtual ~Screen();
    void Exit();


private:
    bool   pointInRect(QPoint &p, QRectF &r);

private:
    QPixmap pixmap;               //全屏
    QPoint pressedPoint;          //鼠标左键按下后的坐标
    QPoint movePoint;             //终点坐标
    QPainterPath globalPath;      //保存全局路径
    bool         oncePress;       //是不是第一次左键按下
    MyRect       widthInfoRect;//截取区域的长宽信息矩形
    //控制选区变化的正方形
    QRectF       rect1;           //第一象限的正方形
    QRectF       rect2;           //第二象限的正方形
    QRectF       rect3;           //第三象限的正方形
    QRectF       rect4;           //第四象限的正方形
    QRectF       rect;            //代表选区的正方形
    Type         type;
    QPoint       oldPoint;        //原先的坐标
    QWidget     *control;
    ControlWidget *controlUi;
    QRect rec;
    QSLabel *labelimage;

};

#endif // SCREEN_H
