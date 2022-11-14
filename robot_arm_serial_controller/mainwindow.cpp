#include "mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_sliders.insert(std::make_pair(ui->slider_1->objectName(), ui->slider_1));
    m_sliders.insert(std::make_pair(ui->slider_2->objectName(), ui->slider_2));
    m_sliders.insert(std::make_pair(ui->slider_3->objectName(), ui->slider_3));
    m_sliders.insert(std::make_pair(ui->slider_4->objectName(), ui->slider_4));
    m_sliders.insert(std::make_pair(ui->slider_5->objectName(), ui->slider_5));
    m_sliders.insert(std::make_pair(ui->slider_6->objectName(), ui->slider_6));

    m_slider_labels.insert(std::make_pair(ui->slider_1->objectName(), ui->sliderValue_1));
    m_slider_labels.insert(std::make_pair(ui->slider_2->objectName(), ui->sliderValue_2));
    m_slider_labels.insert(std::make_pair(ui->slider_3->objectName(), ui->sliderValue_3));
    m_slider_labels.insert(std::make_pair(ui->slider_4->objectName(), ui->sliderValue_4));
    m_slider_labels.insert(std::make_pair(ui->slider_5->objectName(), ui->sliderValue_5));
    m_slider_labels.insert(std::make_pair(ui->slider_6->objectName(), ui->sliderValue_6));

    m_serial_controller = new Serial_controller();

    for (auto& slider : m_sliders) {
        std::cout << "conncet " << slider.first.toStdString() << std::endl;
        connect(slider.second, &QAbstractSlider::sliderReleased, this, &MainWindow::doClicked);
        slider.second->setValue(1500);
        // initialize the slider values map as well, set all to 1500 als default.
        // TODO add a variable for 1500 and max, min.
        m_slider_values.insert(std::make_pair(slider.first, 1500));
        // connect slider label as well
        connect(slider.second, &QAbstractSlider::sliderMoved, this, &MainWindow::sliderMovedHandler);


    }
    // connect ui port related movement to serial port controller.
    connect(ui->portList, &QListWidget::itemClicked, m_serial_controller, &Serial_controller::portListClickHandler);
    connect(ui->selectPort, &QAbstractButton::clicked, m_serial_controller, &Serial_controller::portSelectClickHandler);
    connect(ui->showPorts, &QAbstractButton::clicked, m_serial_controller, &Serial_controller::listPorts);


    //connect(ui->slider_1, &QAbstractSlider::sliderMoved, this, &MainWindow::sliderMovedHandler);
   // connect(ui->slider_1, &QAbstractSlider::sliderReleased, this, &MainWindow::sliderReleasedHandler);


    setInitValues();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doClicked() {
    //std::cout << "clicked: " << text.toStdString() << std::endl;

    QAbstractSlider* s = qobject_cast<QAbstractSlider*>(sender());
    std::cout << s->objectName().toStdString() << " positon: ";
    std::cout << m_slider_values[s->objectName()] << std::endl;
}

void MainWindow::setInitValues() {
    //ui->slider_1->setValue(1500);
}

// change to lambda later
void MainWindow::updateFoundPort(QString portName) {
    ui->portList->addItem(portName);
}

// change to lambda later
void MainWindow::updateSelectedPort(QString portName) {
    ui->selectedport->setText(portName);
}



void MainWindow::sliderMovedHandler(int position) {
    //ui->sliderValue_1->setText(QString::number(position));
    //m_slider_value = position;
    QAbstractSlider* s = qobject_cast<QAbstractSlider*>(sender());
    m_slider_labels[s->objectName()]->setText(QString::number(position));
    m_slider_values[s->objectName()] = position;

}

void MainWindow::sliderReleasedHandler() {
    //std::cout << m_slider_value << std::endl;
}


