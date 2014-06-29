#ifndef SERIALPLOTTER_H
#define SERIALPLOTTER_H

#include <QObject>
#include <QHash>
#include <QWidget>
#include "paintwidget.h"

class SerialPlotter : public QObject
{
    Q_OBJECT
public:
    explicit SerialPlotter(QObject *parent = 0);
    void setDrawingWidget(PaintWidget* canvas);
    void inputDataValues(QString data);
public slots:
    void paintGraph(QPainter* p);
private:
    PaintWidget* drawingWidget;

    QHash<QString,QVector<float>*> dataValues;
    float minimumValue;
    float maximumValue;
    int currentGraphX;

    QHash<QString,float> parseSerialString(QString data);
    int convertToY(float value);
    QColor getGraphColor(int i);
};

#endif // SERIALPLOTTER_H
