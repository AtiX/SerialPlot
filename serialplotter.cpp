#include "serialplotter.h"

#include <QDebug>
#include <QPainter>

SerialPlotter::SerialPlotter(QObject *parent) :
    QObject(parent)
{
    minimumValue = 9999;
    maximumValue = 0;
    currentGraphX = 0;
}

void SerialPlotter::setDrawingWidget(PaintWidget *canvas){
    drawingWidget = canvas;
    connect(drawingWidget,SIGNAL(paintOnMe(QPainter*)),SLOT(paintGraph(QPainter*)));
}

void SerialPlotter::paintGraph(QPainter *p){
    p->setBrush(QBrush(Qt::black));
    p->fillRect(0,0,drawingWidget->width(), drawingWidget->height(),Qt::SolidLine);

    for (int i=0; i<dataValues.keys().count(); i++){
        QVector<float>* values = dataValues.value(dataValues.keys().at(i));
        int y = convertToY(values->last());

        //draw old values backwards to x=0
        p->setPen(getGraphColor(i));
        int oldy = -1;
        for (int j=0; j <= currentGraphX; j++){
            int index = values->size() - 1 - j;
            if (index >= 0){
                float v = values->at(values->size() - 1 -j);
                int newy = convertToY(v);

                if (oldy == -1){
                    oldy = newy;
                }

                p->drawLine(currentGraphX-j+1,oldy,currentGraphX-j,newy);
                oldy = newy;
            }
        }

        p->setPen(Qt::gray);
        p->drawText(0,y,150,20,0,dataValues.keys().at(i));

        p->setPen(Qt::white);
        p->drawPoint(currentGraphX,y);
        p->drawText(currentGraphX,y,150,20,0,QString::number(values->last()));
    }

    currentGraphX++;
    if (currentGraphX == drawingWidget->width())
        currentGraphX = 0;
}

QColor SerialPlotter::getGraphColor(int i){
    switch(i){
    case 0: return Qt::green; break;
    case 1: return Qt::blue; break;
    case 2: return Qt::red; break;
    case 3: return Qt::yellow; break;
    case 4: return Qt::cyan; break;
    case 5: return Qt::darkGreen; break;
    default: return Qt::white; break;
    }
}

int SerialPlotter::convertToY(float value){
    int border = 15;

    //widget coordiante system is upside down
    if (value < minimumValue)
        return drawingWidget->height() - border;
    if (value > maximumValue)
        return border;

    int height = drawingWidget->height() - 2*border;
    float valueSpan = maximumValue - minimumValue;
    float delta = value - minimumValue;

    //map delta to [0 ; height]
    float valPerc = delta / valueSpan;
    int relHeight = height * valPerc;

    return border + (height - relHeight);
}

void SerialPlotter::inputDataValues(QString data){
    //qDebug() << "Plotter got data: '" << data << "'";
    QHash<QString, float> values = parseSerialString(data);

    for (int i=0; i<values.keys().count(); i++){
        QString key = values.keys().at(i);
        float value = values.value(key);

        if (value > maximumValue)
            maximumValue = value;

        if (value < minimumValue)
            minimumValue = value;

        if(dataValues.contains(key)){
            QVector<float>* vec = dataValues.value(key);
            vec->append(value);
        } else {
            QVector<float>* v = new QVector<float>();
            v->append(value);
            dataValues.insert(key, v);
        }
    }

    drawingWidget->callUpdate();
}

QHash<QString,float> SerialPlotter::parseSerialString(QString data){
    QHash<QString, float> output;

    QString currentName;
    QString currentValue;

    int i=0;
    while (i < data.length()){
        currentName = QString("");
        currentValue = QString("");

        //parse identifier
        QChar c = data.at(i);
        while (c != QChar(':')){
            currentName.append(c);
            i++;
            c = data.at(i);
        }

        //skip ':'
        i++;
        c = data.at(i);

        //parse value
        while (c != QChar(' ') && c != QChar('\n')){
            currentValue.append(c);
            i++;
            c = data.at(i);
        }

        float val = currentValue.toFloat();
        output.insert(currentName.trimmed(), val);
        i++;
    }

    return output;
}
