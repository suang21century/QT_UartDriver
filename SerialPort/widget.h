#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include "qcustomplot.h"

#define   _IQ24(A)     static_cast<int32_t>(((A) * 16777216.0))  //强制转换运算符

union byte_4
{
   int data;
   quint32 udata;
   float fdata;
   quint8 byte[sizeof(int)];//以一字节为单元
};

struct Status_Bits
{                               // bits description
quint16  Flag_Status : 2;             // 1:0 电机状态
quint16  Flag_Idc    : 1;             // 2 idc过流故障检测标志位
quint16  Flag_Drv    : 1;             // 3 驱动故障检测标志位
quint16  Flag_Ia     : 1;             // 4 Ia过流
quint16  Flag_Ib     : 1;             // 5 Ib过流
quint16  Flag_Sta2   : 1;             // 6 状态2堵转
quint16  Flag_Lock   : 1;             // 7 状态1堵转
quint16  Flag_Mode   : 1;             // 8 控制模式
quint16  rsvd1       : 7;             // 15:9  reserved
};
union Status_REG
{
  quint16 all;
  quint8 read[2];
  struct Status_Bits bit;
};

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

    byte_4 convn;
    Status_REG status_tmp;
private slots:                                 //添加定义串口相关函数
    void on_pushButton_cmopen_clicked();
    void updateAA();
    char ConvertHexChar(char ch);
    int  gettype(QString text);
    int  getid(QString text);
    void on_pushButton_send_clicked();
    void init_plot();
    void on_pushButton_zero_clicked();

    void on_pushButton_on_clicked();

    void on_pushButton_xy_clicked();

    void on_pushButton_id_clicked();

private:                                       //添加定义指针对象和数组变量
    Ui::Widget *ui;
    QSerialPort *my_serialport;
    QByteArray requestData;
    QCustomPlot *pCustomPlot;
    QTimer *timer;
};





#endif // WIDGET_H
