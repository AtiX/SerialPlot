#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
    void callUpdate();
signals:
    void paintOnMe(QPainter* p);
public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTWIDGET_H
