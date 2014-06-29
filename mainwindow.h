#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>

#include "serialplotter.h"
#include "paintwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void connectClicked();
    void serialPortReadyRead();
private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> availablePorts;
    PaintWidget* paintWidget;
    QSerialPort* currentPort;
    SerialPlotter* plotter;
    QString currentLine;

    QStringList defaultBaudRates();
    void enumerateSerialPorts();
};

#endif // MAINWINDOW_H
