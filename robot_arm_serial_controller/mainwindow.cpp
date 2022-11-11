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
    delete ui;
}



void MainWindow::portListClickHandler(QListWidgetItem *item) {
    m_port = &m_port_list_map[item->text()];
}

void MainWindow::portSelectClickHandler() {
    std::cout << "portselect" << std::endl;
    ui->selectedport->setText(m_port->portName());
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

    //TODO check port baudrate ... para

    if(m_port->open(QIODevice::ReadWrite)){
        std::cout <<  "device open success" << std::endl;
    }
    else{
        std::cout <<  "device open failed" << std::endl;
    }
    m_port->close();
}