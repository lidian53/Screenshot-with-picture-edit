#include "controlwidget.h"
#include "ui_controlwidget.h"
#include <QPoint>
#include "screen.h"
#include <QDebug>
#include <QApplication>
#include <QClipboard>

ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget),
    screen(NULL)
{
    ui->setupUi(this);
    connectSignalAndSlot();

}

void ControlWidget::connectSignalAndSlot()
{
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtn_slot()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveBtn_slot()));
    connect(ui->finishBtn, SIGNAL(clicked()), this, SLOT(finishBtn_slot()));


}
//撤销截图按钮
void ControlWidget::cancelBtn_slot()
{
    if( screen )
    {
        screen->close();
        screen->Exit();
    }
}
//保存截图按钮
void ControlWidget::saveBtn_slot()
{
    screen->savePixmap();
    cancelBtn_slot();
}

//完成按钮将截图保存到剪贴板
void ControlWidget::finishBtn_slot()
{
    QClipboard *board = QApplication::clipboard();
    QPixmap pix = screen->getGrabPixmap();
    board->setImage(pix.toImage());
    cancelBtn_slot();
}


//保存Screen类的引用
void ControlWidget::setScreenQuote(Screen *screen)
{
    this->screen = screen;
}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::on_drawLineBtn_clicked()
{

    screen->drawline();
}



void ControlWidget::on_textEditBtn_clicked()
{
    screen->textedit();
}

void ControlWidget::on_rectangleBtn_clicked()
{
    screen->drawrectang();
}

void ControlWidget::on_drawRoundBtn_clicked()
{
    screen->drawround();
}

void ControlWidget::on_arrowBtn_clicked()
{
    screen->drawarrow();
}

void ControlWidget::on_mosaicBtn_clicked()
{
    //
}

void ControlWidget::on_returneditBtn_clicked()
{
    screen->returnEdit();
}

