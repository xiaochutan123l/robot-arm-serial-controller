#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

#include <map>

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
    QSerialPortInfo *m_portInfo;
    QSerialPort *m_port;
    QList<QSerialPortInfo> m_port_list;
    std::map<QString, QSerialPort> m_port_list_map;
    int m_slider_value;

private slots:
    void portListClickHandler(QListWidgetItem *item);
    void listPorts();
    void portSelectClickHandler();
    void sliderMovedHandler(int position);
    void sliderReleasedHandler();
};
#endif // MAINWINDOW_H
