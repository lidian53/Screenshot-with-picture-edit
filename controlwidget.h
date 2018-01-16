#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QImage>
#include"qslabel.h"

namespace Ui {
    class ControlWidget;
}

class Screen;

//仿照QQ截图的控制面板
class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = 0);

    void connectSignalAndSlot();

    void setScreenQuote(Screen *screen);

    ~ControlWidget();

public slots:
    void cancelBtn_slot();

    void saveBtn_slot();

    void finishBtn_slot();








public slots:
    void on_textEditBtn_clicked();


    void on_rectangleBtn_clicked();

    void on_drawRoundBtn_clicked();

    void on_arrowBtn_clicked();

    void on_mosaicBtn_clicked();

    void on_returneditBtn_clicked();

    void on_drawLineBtn_clicked();

private:
    Ui::ControlWidget *ui;
    Screen *screen;
    QPainter pt;
    QImage bg_gray;



};

#endif // CONTROLWIDGET_H
