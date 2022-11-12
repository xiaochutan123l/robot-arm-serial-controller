#include "mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_port = new QSerialPort();
    m_portInfo = new QSerialPortInfo();
    ui->setupUi(this);
    connect(ui->portList, &QListWidget::itemClicked, this, &MainWindow::portListClickHandler);
    connect(ui->selectPort, &QAbstractButton::clicked, this, &MainWindow::portSelectClickHandler);
    connect(ui->showPorts, &QAbstractButton::clicked, this, &MainWindow::listPorts);
    connect(ui->slider, &QAbstractSlider::sliderMoved, this, &MainWindow::sliderMovedHandler);
    connect(ui->slider, &QAbstractSlider::sliderReleased, this, &MainWindow::sliderReleasedHandler);
}

MainWindow::~MainWindow()
{
    m_port->close();
    delete ui;
}



void MainWindow::portListClickHandler(QListWidgetItem *item) {
    m_port = &m_port_list_map[item->text()];
}

void MainWindow::portSelectClickHandler() {
    std::cout << "portselect" << std::endl;
    ui->selectedport->setText(m_port->portName());
    m_port->setBaudRate(QSerialPort::Baud9600);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->open(QIODevice::ReadWrite);

    ui->slider->setValue(1500);
}

void MainWindow::listPorts() {
    std::cout << "m_port_list.length()" << std::endl;
    m_port_list = QSerialPortInfo::availablePorts();
    std::cout << m_port_list.length() << std::endl;

    Q_FOREACH(QSerialPortInfo p, QSerialPortInfo::availablePorts()) {

        const QString label = p.portName();
        std::cout << label.toStdString() << std::endl;
        //const auto items = ui->listWidget->findItems(label, Qt::MatchExactly);
        ui->portList->addItem(label);
        m_port_list_map.insert(std::make_pair(label, p));
    }
}

void MainWindow::sliderMovedHandler(int position) {
    ui->sliderValue->setText(QString::number(position));
    m_slider_value = position;
}

void MainWindow::sliderReleasedHandler() {
    std::cout << m_slider_value << std::endl;

    if(m_port->isWritable()){
        std::cout <<  "device open success" << std::endl;
        QString data = QString("6,") + QString::number(m_slider_value) + "," + QString::number(1500) + '\n';
        std::cout << data.toStdString() << std::endl;
        m_port->write(data.toUtf8());
        m_port->waitForBytesWritten();
        std::cout <<  "it should sent" << std::endl;
    }
    else{
        std::cout <<  "device open failed" << std::endl;
    }

}
