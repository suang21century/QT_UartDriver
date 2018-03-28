#include "widget.h"
#include "ui_widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include "qcustomplot.h"
#include "math.h"

int readcnt=0;//此次buffer的字符数
int readcnt1=0;//帧数计数
int Sid=0,Cid=0,Ver=0,ErrH=0,ErrL=0,StatusH=0,StatusL=0,check=0;
int data1H=0,data1L=0;
int data2H=0,data2L=0;
int data3H=0,data3L=0;
int data4H=0,data4L=0;
int data5H=0,data5L=0;
int data1[2000];
int data2[2000];
int data3[2000];
int data4[2000];
int data5[2000];

double ts=0.01;//采样时间为100Hz
int timercnt=0;//时间事件计数器

void Widget:: init_plot()  //plot初始化函数，需在类中声明
{
    customPlot = new QCustomPlot(this);  //定义类对象
   // setupRealtimeDataDemo(customPlot);
    //setupDataDemo(customPlot);
    customPlot->setFixedSize(800,600);
    for(int i=0; i<10; i++){
        tempnum[i] = 0;
    }
    n=0;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//查找com口设备
    {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();//打印设备信息

        // Example use QSerialPort
        QSerialPort serial;                        //定义串口对象
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(info.portName());
            serial.close();
        }
    }
    init_plot();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_cmopen_clicked()                      //open按钮槽函数，点击响应
{
    if(ui->pushButton_cmopen->text()==tr("打开串口"))
    {
    my_serialport= new QSerialPort();                             //串口设置
    qDebug()<<ui->comboBox->currentText();                        //打印使用的设备号
    my_serialport->setPortName(ui->comboBox->currentText());
    my_serialport->open(QIODevice::ReadWrite);                    //波特率手动输入
    qDebug()<<ui->lineEdit->text().toInt();                       //打印使用的波特率
    my_serialport->setBaudRate(ui->lineEdit->text().toInt());
    my_serialport->setDataBits(QSerialPort::Data8);
    my_serialport->setParity(QSerialPort::NoParity);
    my_serialport->setStopBits(QSerialPort::OneStop);
    my_serialport->setFlowControl(QSerialPort::NoFlowControl);
    ui->pushButton_cmopen->setText(tr("关闭串口"));                //按钮显示
    ui->pushButton_send->setEnabled(true);                        //发送按钮使能

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAA()));   //定时器调用刷新函数
    timer->start(1000);                                          //定时1000ms


    }
    else
    {
            //关闭串口
            my_serialport->clear();
            my_serialport->close();
            //my_serialport->deleteLater();

            ui->pushButton_cmopen->setText(tr("打开串口"));
    }
}
//
char Widget::ConvertHexChar(char ch)
 {
     if((ch >= '0') && (ch <= '9'))
         return ch-0x30;
     else if((ch >= 'A') && (ch <= 'F'))
         return ch-'A'+10;
     else if((ch >= 'a') && (ch <= 'f'))
         return ch-'a'+10;
     else return (-1);
 }
void Widget::plot_update(QCustomPlot *customPlot) //绘图更新
{
    QVector <double> temp(10);
    QVector <double> temp1(10);
    for(int cnt1 = 0; cnt1<10; cnt1++)
    {
        temp[cnt1] = cnt1/10.0;
    }
    if(readcnt1<10)   //更新数据，从左侧更新
    {
        for(int cnt2=0; cnt2<readcnt1; cnt2++)
        {
           temp1[cnt2]=(double)data1[readcnt1-1-cnt2];
        }
    }
    else
    {
        for(int cnt3=0; cnt3<10; cnt3++)
        {
           temp1[cnt3]=(double)data1[9-cnt3];
        }
    }
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(QColor(70,0,70)));
    customPlot->graph(0)->setData(temp,temp1);
    customPlot->xAxis->setLabel("time");
    customPlot->yAxis->setLabel("yout");
    customPlot->xAxis->setRange(0,1);
    customPlot->xAxis->setSubTickLength(0.1);
    customPlot->yAxis->setRange(0,1000);
    qDebug()<<readcnt1;
    customPlot->replot();
}
void Widget::updateAA()                 //数据更新，串口接收
{
    timercnt++;
    int readdata_tmp;      //暂存
    int i=0,i1=0;
    int byteLeng = my_serialport->bytesAvailable(); //返回串口缓冲区字节数
    qDebug()<<byteLeng;
    requestData = my_serialport->readAll();        //读取buffer内全部数据
    //qDebug()<<requestData[0];
    if(byteLeng>0)                                 //buffer非空时
    {
        ui->textEdit->append(requestData);
        for(i=0;i<byteLeng;i++)                    //遍历数组,i为此次缓存buffer的字节数计数
        {
          readdata_tmp=(int)requestData[i];        //强制转换为asc值

          switch(readcnt)
          {
            case 0:
              if(readdata_tmp==18) readcnt=1; //0x12  ID
            break;
            case 1:
              if(readdata_tmp==85) readcnt=2;//0x55 帧头
              else  readcnt=0;
            break;
            case 2:
              if(readdata_tmp==1) readcnt=3;//0x01
              else  readcnt=0;
            break;
            case 3:
              if(readdata_tmp==18) readcnt=4;//0x12判断长度
              else  readcnt=0;
            break;
            case 4:
              Sid=readdata_tmp;          //sid
              readcnt=5;
            break;
            case 5:
              Cid=readdata_tmp;          //cid
              readcnt=6;
            break;
            case 6:
              Ver=readdata_tmp;          //ver
              readcnt=7;
            break;
            case 7:
              ErrH=readdata_tmp;
              readcnt=8;
            break;
            case 8:
              ErrL=readdata_tmp;
              readcnt=9;
            break;
            case 9:
              StatusH=readdata_tmp;   //status
              readcnt=10;
            break;
            case 10:
              StatusL=readdata_tmp;
              readcnt=11;
            break;
            case 11:
              data1H=readdata_tmp;    //data1
              readcnt=12;
            break;
            case 12:
              data1L=readdata_tmp;
              data1[readcnt1]=data1H*256+data1L;
              if (data1[readcnt1]>=32768) data1[readcnt1]=data1[readcnt1]-65536;
              readcnt=13;
            break;
            case 13:
              data2H=readdata_tmp;    //data2
              readcnt=14;
            break;
            case 14:
              data2L=readdata_tmp;
              data2[readcnt1]=data1H*256+data1L;
              if (data2[readcnt1]>=32768) data2[readcnt1]=data2[readcnt1]-65536;
              readcnt=15;
            break;
            case 15:
              data3H=readdata_tmp;    //data3
              readcnt=16;
            break;
            case 16:
              data3L=readdata_tmp;
              data3[readcnt1]=data3H*256+data3L;
              if (data3[readcnt1]>=32768) data3[readcnt1]=data3[readcnt1]-65536;
              readcnt=17;
            break;
            case 17:
              data4H=readdata_tmp;    //data4
              readcnt=18;
            break;
            case 18:
              data4L=readdata_tmp;
              data4[readcnt1]=data4H*256+data4L;
              if (data4[readcnt1]>=32768) data4[readcnt1]=data4[readcnt1]-65536;
              readcnt=19;
            break;
            case 19:
              data5H=readdata_tmp;    //data5
              readcnt=20;
            break;
            case 20:
              data5L=readdata_tmp;
              data5[readcnt1]=data5H*256+data5L;
              if (data5[readcnt1]>=32768) data5[readcnt1]=data5[readcnt1]-65536;
              readcnt=21;
            break;
            case 21:
              check=readdata_tmp;//check
              readcnt1++;//出现新的数据，==11;
              readcnt=0;
              if(readcnt1>10)
              {
                for(i1=0;i1<10;i1++)
                {
                  data1[i1]=data1[i1+1];
                }
                readcnt1=10;//保持数组个数为10个
              }

            break;
          }
        }

    }
    //qDebug()<<readcnt1;

    requestData.clear();


    n++;
    plot_update(customPlot);
}

void Widget::on_pushButton_send_clicked()
{
    QByteArray TxData = "aaaa";
    my_serialport->write(TxData);
}
