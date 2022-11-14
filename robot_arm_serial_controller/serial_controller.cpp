#include "serial_controller.h"
#include <iostream>

class Motor_Manager {
public:
    std::vector<int> motor_prev_positions;

    Motor_Manager() {
        motor_prev_positions = {1500, 1500, 1500, 1500, 1500, 1500};
    }

    void setMotorPosition(int index, int new_pos) {
        motor_prev_positions[index -1] = new_pos;
    }

    int calc_move_time(int index, int new_pos) {
        int move_range = abs(motor_prev_positions[index -1] - new_pos) * 2;
        //motor_prev_positions[index -1] = new_pos;

        return (move_range >= 200) ? 2000 : move_range;
    }
};


Serial_controller::Serial_controller(){
    m_port = new QSerialPort();
    m_portInfo = new QSerialPortInfo();
    m_motor_mgr = new Motor_Manager();
}

void Serial_controller::resetMotors() {
    if(m_port->isWritable()){
        for (int i = 1; i < 7; i++) {
            QString data = QString::number(i) + "," + QString::number(1500) + "," + QString::number(2000) + '\n';
            m_port->write(data.toUtf8());
            m_port->waitForBytesWritten();
            m_motor_mgr->setMotorPosition(i, 1500);
        }
    }
}

void Serial_controller::listPorts() {
    std::cout << "Ports number: ";
    m_port_list = QSerialPortInfo::availablePorts();
    std::cout << m_port_list.length() << std::endl;

    Q_FOREACH(QSerialPortInfo p, QSerialPortInfo::availablePorts()) {
        const QString label = p.portName();
        std::cout << label.toStdString() << std::endl;
        //const auto items = ui->listWidget->findItems(label, Qt::MatchExactly);
        //ui->portList->addItem(label);
        emit portFound(label);
        m_port_list_map.insert(std::make_pair(label, p));
    }
}

void Serial_controller::portListClickHandler(QListWidgetItem *item) {
    m_port = &m_port_list_map[item->text()];
}

void Serial_controller::portSelectClickHandler() {
    std::cout << "portselect" << std::endl;
    emit portSelected(m_port->portName());
    openPort();
}

void Serial_controller::sendMsg(int motorId, int toPosition, int time) {
    int t = m_motor_mgr->calc_move_time(motorId, toPosition);

    if(m_port->isWritable()){
        QString data = QString::number(motorId) + "," + QString::number(toPosition) + "," + QString::number(t) + '\n';
        std::cout << data.toStdString() << std::endl;
        m_port->write(data.toUtf8());
        m_port->waitForBytesWritten();
        std::cout <<  "it should sent" << std::endl;
        m_motor_mgr->setMotorPosition(motorId, toPosition);
    }
    else{
        std::cout <<  "device open failed" << std::endl;
        // if serial port not writable, new position should not be updated.
        //m_motor_mgr->setMotorPosition(motorId, toPosition);
    }
}

void Serial_controller::openPort() {
    m_port->setBaudRate(QSerialPort::Baud9600);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->open(QIODevice::ReadWrite);
    std::cout <<  "device open success" << std::endl;
}

void Serial_controller::closePort() {
    m_port->close();
}

Serial_controller::~Serial_controller(){
    closePort();
    delete m_port;
    delete m_portInfo;
}

