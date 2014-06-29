#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
}

void PaintWidget::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    emit paintOnMe(&painter);
    painter.end();
}

void PaintWidget::callUpdate(){
    update();
}
