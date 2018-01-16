#include "qslabel.h"
#include"controlwidget.h"
#include<QPalette>
#include"screen.h"
using namespace Qt;
QSLabel::QSLabel(QWidget* parent)
{
    setMouseTracking(true);
    ispressed=false;
    isdrawline=false;
    isdrawrectangle=false;
    isdrawround=false;
    istextedit=false;
    isdrawarrow=false;
    m_plaintextedit=new QTextEdit(this);
    m_plaintextedit->hide();
    m_plaintextedit->resize(60,40);
    QPalette p1=m_plaintextedit->palette();
    p1.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    m_plaintextedit->setPalette(p1);
    connect(m_plaintextedit,SIGNAL(textChanged()),this,SLOT(ontextchanged()));
    m_plaintextedit->setStyleSheet("QTextEdit{ border: 1px solid #dadada; }"
                                   "QTextEdit{font-family:'Microsoft YaHei'; font-size:14px;color:#ff0000;}"
                                   ""
                                   );
}

void QSLabel::ontextchanged()
{
    if(m_plaintextedit->toPlainText().size()<10)
       {
           m_plaintextedit->resize(m_plaintextedit->toPlainText().size()*10+50,40);
       }
       else
       {
           m_plaintextedit->resize(m_plaintextedit->toPlainText().size()*15+20,m_plaintextedit->document()->size().rheight()+10);

       }
}

void QSLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(isdrawline||isdrawrectangle||isdrawround||istextedit||isdrawarrow)
        {

            setCursor(CrossCursor);
        }
    if(ispressed)
       {
           if(isdrawline)
           {
               endPoint=event->pos();
               myLine *line=new myLine;
               line->startPoint=startPoint;
               line->endPoint=endPoint;
               lines.push_back(line);
               startPoint=endPoint;
           }
           else if(isdrawrectangle||isdrawround||isdrawarrow)
           {
               endPoint=event->pos();
           }
           update();
       }
}

void QSLabel::mousePressEvent(QMouseEvent *event)
{
        startPoint=event->pos();
        endPoint=event->pos();
        ispressed=true;
        if(istextedit)
        {
            if(m_plaintextedit->toPlainText().size())
            {
                myText *text=new myText;
                text->mRect=QRect(QPoint(m_plaintextedit->x(),m_plaintextedit->y()),QSize(m_plaintextedit->width(),m_plaintextedit->height()));
                text->mText=m_plaintextedit->toPlainText();
                texts.push_back(text);
                update();
            }
            m_plaintextedit->move(startPoint);
            m_plaintextedit->show();
            m_plaintextedit->clear();
        }
}

void QSLabel::mouseReleaseEvent(QMouseEvent *event)
{
    //setCursor(ArrowCursor);
    ispressed=false;
    if(isdrawrectangle)
    {
        endPoint=event->pos();
        myRectangle *rectangle=new myRectangle;
        rectangle->startPoint=startPoint;
        rectangle->endPoint=endPoint;
        rectangles.push_back(rectangle);
        update();
    }
    else if(isdrawround)
    {
        endPoint=event->pos();
        myRound *round=new myRound;
        round->startPoint=startPoint;
        round->endPoint=endPoint;
        rounds.push_back(round);
        update();
    }
    else if(isdrawarrow)
    {
        endPoint=event->pos();
        myArrow *arrow=new myArrow;
        arrow->startPoint=startPoint;
        arrow->endPoint=endPoint;
        arrows.push_back(arrow);
        update();
    }
}


void QSLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,selectimage); //表示是在selectimage上面做编辑
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(red);
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<lines.size();i++)
    {
        myLine *line=lines[i];
        painter.drawLine(line->startPoint,line->endPoint);

    }
    for(int j=0;j<rectangles.size();j++)
    {
        myRectangle *rectangle=rectangles[j];
        int x1 = rectangle->startPoint.x() < rectangle->endPoint.x() ? rectangle->startPoint.x() : rectangle->endPoint.x();
            int y1 = rectangle->startPoint.y() < rectangle->endPoint.y() ? rectangle->startPoint.y() : rectangle->endPoint.y();
        painter.drawRect(x1, y1, abs(rectangle->endPoint.x() - rectangle->startPoint.x()), abs(rectangle->endPoint.y() - rectangle->startPoint.y()));

    }
    for (int k = 0; k < rounds.size(); k++)
    {
        myRound *round = rounds[k];
        int x2 = round->startPoint.x() < round->endPoint.x() ? round->startPoint.x() : round->endPoint.x();
        int y2 = round->startPoint.y() < round->endPoint.y() ? round->startPoint.y() : round->endPoint.y();
        painter.drawEllipse(x2, y2, abs(round->endPoint.x() - round->startPoint.x()), abs(round->endPoint.y() - round->startPoint.y()));

    }
    for(int m=0;m<arrows.size();m++)
    {
        myArrow *arrow=arrows[m];

        drawarrow(arrow->startPoint,arrow->endPoint,painter);

    }
    for (int l = 0; l < texts.size(); l++)
    {
           myText *text = texts[l];
           QRect rect = text->mRect;
           painter.drawText(rect, Qt::TextWrapAnywhere, text->mText);
    }
       int xx = startPoint.x() < endPoint.x() ? startPoint.x() : endPoint.x();
       int yy = startPoint.y() < endPoint.y() ? startPoint.y() : endPoint.y();
       if (isdrawrectangle)
       {
           painter.drawRect(xx, yy, abs(endPoint.x() - startPoint.x()), abs(endPoint.y() - startPoint.y()));
       }
       else if (isdrawround)
       {
           painter.drawEllipse(xx, yy, abs(endPoint.x() - startPoint.x()), abs(endPoint.y() - startPoint.y()));
       }
       else if(isdrawarrow)
       {
           drawarrow(startPoint,endPoint,painter);
       }
}

void QSLabel::drawarrow(QPoint startpoint, QPoint endpoint, QPainter &p)
{
        double par=15.0;
        double slopy=atan2((endpoint.y()-startpoint.y()),(endpoint.x()-startpoint.x()));
        double cosy=cos(slopy);
        double siny=sin(slopy);
        QPoint point1 = QPoint(endpoint.x() + int(-par*cosy - (par / 2.0*siny)), endpoint.y() + int(-par*siny + (par / 2.0*cosy)));
        QPoint point2 = QPoint(endpoint.x() + int(-par*cosy + (par / 2.0*siny)), endpoint.y() - int(par / 2.0*cosy + par*siny));
        QPoint points[3]={endpoint,point1,point2};
        p.setRenderHint(QPainter::Antialiasing,true);
        QPen drawtrianglepen;
        drawtrianglepen.setColor(Qt::red);
        drawtrianglepen.setWidth(1);
        p.setPen(drawtrianglepen);
        p.drawPolygon(points,3);
        int offsetx=int(par*siny/3);
        int offsety=int(par*cosy/3);
        QPoint point3,point4;
        point3 = QPoint(endpoint.x() + int(-par*cosy - (par / 2.0*siny)) + offsetx, endpoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsety);
        point4 = QPoint(endpoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetx), endpoint.y() - int(par / 2.0*cosy + par*siny) + offsety);
        QPoint arrbodypoints[3]={startpoint,point3,point4};
        p.drawPolygon(arrbodypoints,3);

}

void QSLabel::setimagetolabel(const QImage &image)
{
    selectimage=image;

    endPoint=QPoint(0,0);
    startPoint=QPoint(0,0);
}


void QSLabel::setdrawlineenable()
{
    settextedittovector();

    isdrawline=true;
        isdrawrectangle=false;
        isdrawround=false;
        istextedit=false;
        isdrawarrow=false;
        m_plaintextedit->hide();
}

void QSLabel::setrectangleenable()
{
      settextedittovector();
    isdrawline=false;
        isdrawrectangle=true;
        isdrawround=false;
        istextedit=false;
        isdrawarrow=false;

        m_plaintextedit->hide();
}

void QSLabel::setdrawarrowenable()
{
       settextedittovector();
    isdrawline=false;
       isdrawarrow=true;
       isdrawrectangle=false;
       isdrawround=false;
       istextedit=false;

       m_plaintextedit->hide();
}

void QSLabel::setroundenable()
{
       settextedittovector();
    isdrawline=false;
       isdrawrectangle=false;
       isdrawround=true;
       isdrawarrow=false;
       istextedit=false;

       m_plaintextedit->hide();
}

void QSLabel::settexteditenable()
{
     settextedittovector();
    isdrawline=false;
       isdrawrectangle=false;
       isdrawround=false;
       isdrawarrow=false;
       istextedit=true;

       m_plaintextedit->hide();
}

void QSLabel::settextedittovector()
{
    if (istextedit&&m_plaintextedit->toPlainText().size())
    {
        myText *text = new myText;
        text->mRect = QRect(QPoint(m_plaintextedit->x(), m_plaintextedit->y()), QSize(m_plaintextedit->width(), m_plaintextedit->height()));
        text->mText = m_plaintextedit->toPlainText();
        texts.push_back(text);
        update();
    }
}

QImage QSLabel::resultimage()
{
    return QImage(QPixmap::grabWidget(this).toImage());

}
