#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

//#include "mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QListWidgetItem>

#include <map>

struct MotorPara {
  int motorId;
  int toPosition;
  int time;
};

class Serial_controller : public QObject{
    Q_OBJECT

public:
    Serial_controller();
    ~Serial_controller();

signals:
    // add selected port name
    void portSelected(QString portName);
    // add found port item name
    void portFound(QString portName);

public slots:
    void portListClickHandler(QListWidgetItem *item);
    void listPorts();
    void portSelectClickHandler();

    void sendMsg(MotorPara *para);
private:
    void openPort();
    void closePort();

    //Ui::MainWindow *ui;
    QSerialPortInfo *m_portInfo;
    QSerialPort *m_port;
    QList<QSerialPortInfo> m_port_list;
    std::map<QString, QSerialPort> m_port_list_map;
    //int m_slider_value;
};

#endif // SERIAL_CONTROLLER_H
