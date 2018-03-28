#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void plot_update(QCustomPlot *customPlot);
    QCustomPlot *customPlot;
    double tempnum[10];
    double n;

private slots:                                 //添加定义串口相关函数
    void on_pushButton_cmopen_clicked();
    void updateAA();
    char ConvertHexChar(char ch);
    void on_pushButton_send_clicked();
    void init_plot();
private:                                       //添加定义指针对象和数组变量
    Ui::Widget *ui;
    QSerialPort *my_serialport;
    QByteArray requestData;
    QCustomPlot *pCustomPlot;
    QTimer *timer;
};

#endif // WIDGET_H
