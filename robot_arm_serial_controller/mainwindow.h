#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"

#include "serial_controller.h"
//#include <QSerialPort>
//#include <QSerialPortInfo>

//#include "motors.h"
#include <QSignalMapper>

#include <set>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Serial_controller *m_serial_controller;
    //int m_slider_value;

    QSignalMapper *m_mapper;
    std::map<QString, QSlider*> m_sliders;
    std::map<QString, int> m_slider_values;
    std::map<QString, QLabel*> m_slider_labels;

    void setInitValues();

private slots:
    // update serial port stuff.
    void updateFoundPort(QString portName);
    void updateSelectedPort(QString portName);

    void sliderMovedHandler(int position);
    void sliderReleasedHandler();

    void doClicked();
};
#endif // MAINWINDOW_H
