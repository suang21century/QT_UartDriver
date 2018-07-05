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
    quint16  Mode         : 4;             //工作模式
    quint16  MotorStatus  : 4;             //电机工作状态
    quint16  rsvd1        : 8;             // 15:8  reserved
};
union Status_REG
{
  quint16 all;
  struct Status_Bits bit;
};
struct Err_Bits
{                               // bits description
    quint16  Err_OverCurrent  : 1;             //过流  0
    quint16  Err_Tem          : 1;             //过温
    quint16  Err_OverV        : 1;             // 过压
    quint16  Err_Locked       : 1;             //堵转
    quint16  Err_Driver       : 1;    //驱动故障
    quint16  Err_Feed         : 1;    //反馈故障
    quint16  Err_Com          : 1;    //通讯错误
    quint16  Com_Read         : 1;    //接收一帧标志   6
    quint16  rsvd1        : 8;             // 15:8  reserved
};
union Err_REG
{
  quint16 all;
  struct Err_Bits bit;
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
    Err_REG  Err;

private slots:                                 //添加定义串口相关函数
    void on_pushButton_cmopen_clicked();
    void updateAA();
    void signalsend();
    int  getmode(QString text);
    void on_pushButton_send_clicked();
    void init_plot();
    void on_pushButton_zero_clicked();

    void on_pushButton_on_clicked();

    void on_pushButton_xy_clicked();

    void on_pushButton_mode_clicked();

    void on_pushButton_com_clicked();

    void on_pushButton_dir_clicked();

    void on_pushButton_write_clicked();

    void on_pushButton_para_clicked();

    void on_pushButton_Loc1_clicked();

    void on_pushButton_Loc2_clicked();

    void on_pushButton_Spd1_clicked();

    void on_pushButton_Spd2_clicked();

    void on_pushButton_I1_clicked();

    void on_pushButton_I2_clicked();

    void on_checkBox_clicked();

    void on_pushButton_Sine_clicked();

private:                                       //添加定义指针对象和数组变量
    Ui::Widget *ui;
    QSerialPort *my_serialport;
    QByteArray requestData;
    QCustomPlot *pCustomPlot;
    QTimer *timer;
};





#endif // WIDGET_H
