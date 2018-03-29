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
int Sid=0,Cid=0,Ver=0,ErrH=0,ErrL=0,check=0;
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
QVector <double> temp(1000);
QVector <double> temp1(1000);
QVector <double> temp2(1000);
QVector <double> temp3(1000);
QVector <double> temp4(1000);
QVector <double> temp5(1000);

double ts=0.01;//采样时间为100Hz
int timercnt=0;//时间事件计数器
QByteArray txtemp;
float senddata;

void Widget:: init_plot()  //plot初始化函数，需在类中声明
{
    customPlot = new QCustomPlot(this);  //定义类对象
   // setupRealtimeDataDemo(customPlot);
    //setupDataDemo(customPlot);
    customPlot->setFixedSize(1000,800);

    customPlot->addGraph();                         //此段初始化放在此处，若在plot_update内存会逐步上升
    customPlot->graph(0)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setName("data1");
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::blue));
    customPlot->graph(1)->setName("data2");
    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::gray));
    customPlot->graph(2)->setName("data3");
    customPlot->addGraph();
    customPlot->graph(3)->setPen(QPen(Qt::yellow));
    customPlot->graph(3)->setName("data4");
    customPlot->addGraph();
    customPlot->graph(4)->setPen(QPen(Qt::green));
    customPlot->graph(4)->setName("data5");

    for(int cnt1 = 0; cnt1<1000; cnt1++)
    {
        temp[cnt1] = cnt1/100.0;   //事件轴，0--10.0
    }
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->comboBox_type->addItem(QWidget::tr("位置指令"));
    ui->comboBox_type->addItem(QWidget::tr("传动比"));
    ui->comboBox_type->addItem(QWidget::tr("位置Kp"));

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
    timer->start(20);                                          //定时100ms
     //startTimer(50);//单位为毫秒

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

void Widget::plot_update(QCustomPlot *customPlot) //绘图更新
{


    if(readcnt1<1000)   //更新数据，从左侧更新，10s以内
    {
        for(int cnt2=0; cnt2<readcnt1; cnt2++)
        {
           temp1[cnt2]=(double)data1[readcnt1-1-cnt2];
           temp2[cnt2]=(double)data2[readcnt1-1-cnt2];
           temp3[cnt2]=(double)data3[readcnt1-1-cnt2];
           temp4[cnt2]=(double)data4[readcnt1-1-cnt2];
           temp5[cnt2]=(double)data5[readcnt1-1-cnt2];
        }
    }
    else
    {
        for(int cnt3=0; cnt3<1000; cnt3++)//10s以后，动态刷新
        {
           temp1[cnt3]=(double)data1[999-cnt3];
           temp2[cnt3]=(double)data2[999-cnt3];
           temp3[cnt3]=(double)data3[999-cnt3];
           temp4[cnt3]=(double)data4[999-cnt3];
           temp5[cnt3]=(double)data5[999-cnt3];
        }
    }


    customPlot->graph(0)->setData(temp,temp1);
    customPlot->graph(1)->setData(temp,temp2);
    customPlot->graph(2)->setData(temp,temp3);
    customPlot->graph(3)->setData(temp,temp4);
    customPlot->graph(4)->setData(temp,temp5);
    customPlot->xAxis->setLabel("time");
    customPlot->yAxis->setLabel("yout");
    //customPlot->xAxis->setRange((ui->lineEdit_x1->text().toFloat()),(ui->lineEdit_x2->text().toFloat()));
    //customPlot->xAxis->setSubTickLength(0.1);
    //customPlot->yAxis->setRange((ui->lineEdit_y1->text().toFloat()),(ui->lineEdit_y2->text().toFloat()));
    //customPlot->yAxis->setAutoTickStep(true);//自动识别范围
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//可放大缩小
    //qDebug()<<readcnt1;
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
        //ui->textEdit->append(requestData);
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
              status_tmp.read[1]=readdata_tmp;   //status小端处理
              readcnt=10;
            break;
            case 10:
              status_tmp.read[0]=readdata_tmp;
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
              data2[readcnt1]=data2H*256+data2L;
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
              if(readcnt1>1000)
              {
                for(i1=0;i1<1000;i1++)
                {
                  data1[i1]=data1[i1+1];
                  data2[i1]=data2[i1+1];
                  data3[i1]=data3[i1+1];
                  data4[i1]=data4[i1+1];
                  data5[i1]=data5[i1+1];
                }
                readcnt1=1000;//保持数组个数为1000个
              }
              QPalette pal(ui->widget_status->palette());   //声明控件颜色板
              if((status_tmp.all&0x00FC)==0)                //判断状态正常时显示绿色
              {
                  pal.setColor(QPalette::Background, Qt::green);
                  ui->widget_status->setAutoFillBackground(true);
                  ui->widget_status->setPalette(pal);
                  ui->widget_status->show();
              }
              else
              {
                  pal.setColor(QPalette::Background, Qt::red);  //故障时显示红色
                  ui->widget_status->setAutoFillBackground(true);
                  ui->widget_status->setPalette(pal);
                  ui->widget_status->show();
              }
            break;
          }
        }

    }
    //qDebug()<<readcnt1;

    requestData.clear();

    plot_update(customPlot);
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
int Widget::gettype(QString text)
{
  if(text=="位置指令")
      return 0;
  else if(text=="传动比")
      return 1;
  else if(text=="位置Kp")
      return 2;
  else return 0;
}

void Widget::on_pushButton_send_clicked()//发送指令按键事件
{
    senddata = ui->lineEdit_data->text().toFloat();//读取输入框内数据，转换为float
    convn.data=_IQ24(senddata);  //float转换为IQ24的int类型，4字节，存入共同体内
    QByteArray TxData;
    int check;
    int type;
    TxData.resize(15);
    TxData[0]=0x7E;
    TxData[1]=0x5A;
    TxData[2]=0x12;//ID
    TxData[3]=0x0A;
    TxData[4]=0xAA;//header
    type=gettype(ui->comboBox_type->currentText());
    TxData[5]=type;
    check=type;
    TxData[6]=0x07;
    check+=0x07;
    TxData[7]=convn.byte[3];//高字节
    check+=TxData[7];
    TxData[8]=convn.byte[2];
    check+=TxData[8];
    TxData[9]=convn.byte[1];
    check+=TxData[9];
    TxData[10]=convn.byte[0];
    check+=TxData[10];
    TxData[11]=0x01;
    check+=0x01;
    TxData[12]=check&0xFF;  //check
    TxData[13]=0x0A;
    TxData[14]=0xEC;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_zero_clicked()
{
    QByteArray TxData;
    TxData.resize(15);
    TxData[0]=0x7E;
    TxData[1]=0x5A;
    TxData[2]=0x12;
    TxData[3]=0x0A;
    TxData[4]=0xAA;
    TxData[5]=0x11;
    TxData[6]=0x07;
    TxData[7]=0x00;
    TxData[8]=0x00;
    TxData[9]=0x00;
    TxData[10]=0x01;
    TxData[11]=0x01;
    TxData[12]=0x1A;
    TxData[13]=0x0A;
    TxData[14]=0xEC;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_on_clicked()
{
    if(ui->pushButton_on->text()==tr("电机启动"))
    {
        QByteArray TxData;
        TxData.resize(15);
        TxData[0]=0x7E;
        TxData[1]=0x5A;
        TxData[2]=0x12;
        TxData[3]=0x0A;
        TxData[4]=0xAA;
        TxData[5]=0x10;
        TxData[6]=0x07;
        TxData[7]=0x00;
        TxData[8]=0x00;
        TxData[9]=0x00;
        TxData[10]=0x01;
        TxData[11]=0x01;
        TxData[12]=0x19;
        TxData[13]=0x0A;
        TxData[14]=0xEC;
        my_serialport->write(TxData);
        ui->pushButton_on->setText(tr("电机停机"));                //按钮显示
    }
    else
    {
        QByteArray TxData;
        TxData.resize(15);
        TxData[0]=0x7E;
        TxData[1]=0x5A;
        TxData[2]=0x12;
        TxData[3]=0x0A;
        TxData[4]=0xAA;
        TxData[5]=0x10;
        TxData[6]=0x07;
        TxData[7]=0x00;
        TxData[8]=0x00;
        TxData[9]=0x00;
        TxData[10]=0x00;
        TxData[11]=0x01;
        TxData[12]=0x18;
        TxData[13]=0x0A;
        TxData[14]=0xEC;
        my_serialport->write(TxData);

        ui->pushButton_on->setText(tr("电机启动"));
    }
}

void Widget::on_pushButton_xy_clicked()
{
    customPlot->xAxis->setRange((ui->lineEdit_x1->text().toFloat()),(ui->lineEdit_x2->text().toFloat()));
    //customPlot->xAxis->setSubTickLength(0.1);
    customPlot->yAxis->setRange((ui->lineEdit_y1->text().toFloat()),(ui->lineEdit_y2->text().toFloat()));
}

void Widget::on_pushButton_id_clicked()
{
    QByteArray TxData;
    TxData.resize(3);
    TxData[0]=0xFF;
    TxData[1]=0x55;
    TxData[2]=0x10;
    my_serialport->write(TxData);
}
