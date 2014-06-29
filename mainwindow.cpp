#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentPort = 0;
    plotter = 0;
    currentLine = QString("");

    //init values
    ui->cbBaudRates->addItems(defaultBaudRates());
    enumerateSerialPorts();

    connect(ui->bConnect,SIGNAL(clicked()),SLOT(connectClicked()));

    paintWidget = new PaintWidget(this);
    ui->paintLayout->addWidget(paintWidget);
    paintWidget->resize(paintWidget->width(), 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectClicked(){
    QSerialPortInfo portInfo = availablePorts.at(ui->cbPorts->currentIndex());

    if (currentPort != 0)
        delete currentPort;

    currentPort = new QSerialPort(portInfo);
    connect(currentPort,SIGNAL(readyRead()),SLOT(serialPortReadyRead()));

    plotter = new SerialPlotter(this);
    plotter->setDrawingWidget(paintWidget);

    if (!currentPort->open(QIODevice::ReadWrite)){
        QMessageBox msgBox;
        msgBox.setText("Nope. (Error opening serial port)");
        msgBox.exec();
    }

    currentPort->setBaudRate(ui->cbBaudRates->currentText().toInt());
}

QStringList MainWindow::defaultBaudRates(){
    QStringList l;
    l.append("2400");
    l.append("4800");
    l.append("9600");
    l.append("19200");
    l.append("38400");
    l.append("57600");
    l.append("115200");
    return l;
}

void MainWindow::enumerateSerialPorts(){
    availablePorts = QSerialPortInfo::availablePorts();

    for (int i=0; i<availablePorts.size(); i++){
        ui->cbPorts->addItem(availablePorts.at(i).portName());
    }
}

void MainWindow::serialPortReadyRead(){
    //read until '\n'
    QString line = QString(currentPort->readLine());
    currentLine.append(line);

    if (currentLine.indexOf("\n") >= 0){
        //Check if it begins with 'PLOT '
        if (!currentLine.startsWith(QString("PLOT ")))
            return;

        QString dataValues = currentLine.right(currentLine.length() - 5);
        plotter->inputDataValues(dataValues);
        currentLine = QString("");
    }
}
