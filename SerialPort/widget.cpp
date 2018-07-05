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
int readok=0;//下位机接收ok反馈状态计数
QString strValue;
int Ver=0,check=0;
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

int checkstatus=0;
int sinestatus=0;
int SigCnt=0;
double SigAmp=0;
double SigTs=0;
float SigOut=0;

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

    ui->comboBox_mode->addItem(QWidget::tr("位置模式"));         //下拉菜单1初始化
    ui->comboBox_mode->addItem(QWidget::tr("速度模式"));
    ui->comboBox_mode->addItem(QWidget::tr("电流模式"));
    ui->comboBox_mode->addItem(QWidget::tr("回零模式"));
    ui->comboBox_mode->addItem(QWidget::tr("找初始角"));


    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//查找com口设备
    {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();   //打印设备信息

        // Example use QSerialPort
        QSerialPort serial;                                    //定义串口对象
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(info.portName());
            serial.close();
        }
    }
    init_plot();                                              //绘图类初始化

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
    timer->start(20);                                          //定时20ms,50Hz
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

void Widget::signalsend()//信号源发送函数，定时调用，50Hz
{
  if(checkstatus==1)//循环阶跃信号使能
  {

     if(SigCnt==1)
     {
         QByteArray TxData;
         int check;
         //LocRef2
         senddata = ui->lineEdit_LocRef1->text().toFloat();//读取输入框内数据，转换为float
         convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
         TxData.resize(8);
         TxData[0]=0xAA;//header
         TxData[1]=0x27;
         check=0x27;
         TxData[2]=convn.byte[3];//高字节
         check+=TxData[2];
         TxData[3]=convn.byte[2];
         check+=TxData[3];
         TxData[4]=convn.byte[1];
         check+=TxData[4];
         TxData[5]=convn.byte[0];
         check+=TxData[5];
         TxData[6]=check&0xFF;  //check
         TxData[7]=0x0A;
         my_serialport->write(TxData);

     }
     if(SigCnt==100)//2s
     {
         QByteArray TxData;
         int check;
         //LocRef2
         senddata = ui->lineEdit_LocRef2->text().toFloat();//读取输入框内数据，转换为float
         convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
         TxData.resize(8);
         TxData[0]=0xAA;//header
         TxData[1]=0x27;
         check=0x27;
         TxData[2]=convn.byte[3];//高字节
         check+=TxData[2];
         TxData[3]=convn.byte[2];
         check+=TxData[3];
         TxData[4]=convn.byte[1];
         check+=TxData[4];
         TxData[5]=convn.byte[0];
         check+=TxData[5];
         TxData[6]=check&0xFF;  //check
         TxData[7]=0x0A;
         my_serialport->write(TxData);
     }
     if(SigCnt==200)SigCnt=0;//5s
     SigCnt++;
  }

  if(sinestatus==1)//正弦信号使能
  {
      SigCnt++;

      QByteArray TxData;
      int check;
      //Sine LocRef
      SigAmp = ui->lineEdit_LocAmp->text().toFloat();//读取输入框内数据，转换为float
      SigTs = ui->lineEdit_LocTs->text().toFloat();//读取输入框内数据，转换为float
      SigOut=  sin(SigCnt*6.28/(SigTs*33))*SigAmp;
      convn.data=(int32_t)SigOut;  //float转换为int类型，4字节，存入共同体内
      TxData.resize(8);
      TxData[0]=0xAA;//header
      TxData[1]=0x27;
      check=0x27;
      TxData[2]=convn.byte[3];//高字节
      check+=TxData[2];
      TxData[3]=convn.byte[2];
      check+=TxData[3];
      TxData[4]=convn.byte[1];
      check+=TxData[4];
      TxData[5]=convn.byte[0];
      check+=TxData[5];
      TxData[6]=check&0xFF;  //check
      TxData[7]=0x0A;
      my_serialport->write(TxData);
  }

}

void Widget::plot_update(QCustomPlot *customPlot) //绘图更新函数
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


void Widget::updateAA()                 //数据更新，串口接收，处理,50Hz定时
{
    //timercnt++;
    quint8 readdata_tmp;      //暂存
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
              if(readdata_tmp==0x55) readcnt=1;//0x55 帧头
              else  readcnt=0;
            break;
            case 1:
              if(readdata_tmp==0x01) readcnt=2;//0x01
              else  readcnt=0;
            break;
            case 2:
              Ver=readdata_tmp;              //ver
              readcnt=3;
            break;
            case 3:
              Err.all=readdata_tmp;          //Err
              readcnt=4;
            break;
            case 4:
              status_tmp.all=readdata_tmp;   //status
              readcnt=5;
            break;
            case 5:
              data1H=readdata_tmp;    //data1
              readcnt=6;
            break;
            case 6:
              data1L=readdata_tmp;
              data1[readcnt1]=data1H*256+data1L;
              if (data1[readcnt1]>=32768) data1[readcnt1]=data1[readcnt1]-65536;
              readcnt=7;
            break;
            case 7:
              data2H=readdata_tmp;    //data2
              readcnt=8;
            break;
            case 8:
              data2L=readdata_tmp;
              data2[readcnt1]=data2H*256+data2L;
              if (data2[readcnt1]>=32768) data2[readcnt1]=data2[readcnt1]-65536;
              readcnt=9;
            break;
            case 9:
              data3H=readdata_tmp;    //data3
              readcnt=10;
            break;
            case 10:
              data3L=readdata_tmp;
              data3[readcnt1]=data3H*256+data3L;
              if (data3[readcnt1]>=32768) data3[readcnt1]=data3[readcnt1]-65536;
              readcnt=11;
            break;
            case 11:
              data4H=readdata_tmp;    //data4
              readcnt=12;
            break;
            case 12:
              data4L=readdata_tmp;
              data4[readcnt1]=data4H*256+data4L;
              if (data4[readcnt1]>=32768) data4[readcnt1]=data4[readcnt1]-65536;
              readcnt=13;
            break;
            case 13:
              data5H=readdata_tmp;    //data5
              readcnt=14;
            break;
            case 14:
              data5L=readdata_tmp;
              data5[readcnt1]=data5H*256+data5L;
              if (data5[readcnt1]>=32768) data5[readcnt1]=data5[readcnt1]-65536;
              readcnt=15;
            break;
            case 15:
              check=readdata_tmp;//check
              //更新到textedit,会导致界面卡
              /*
              strValue = tr("%1").arg(data1[readcnt1]);
              ui->textEdit_Loc->setPlainText(strValue);
              strValue = tr("%1").arg(data3[readcnt1]);
              ui->textEdit_Spd->setPlainText(strValue);
              strValue = tr("%1").arg(data5[readcnt1]);
              ui->textEdit_I->setPlainText(strValue);*/
              //更新画布
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
              if((Err.all&0x007F)==0)                //判断状态正常时显示绿色
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
              if((Err.all&0x0080)==0x0080)                //接收一帧标志
              {
                readok++;
                strValue = tr("%1").arg(readok);
                ui->textEdit->setPlainText(strValue);
              }
            break;
          }
        }

    }
    //qDebug()<<readcnt1;

    requestData.clear();

    plot_update(customPlot);

    signalsend( );
}

int Widget::getmode(QString text)
{
  if(text=="位置模式")
      return 0x0;
  else if(text=="速度模式")
      return 0x01;
  else if(text=="电流模式")
      return 0x02;
  else if(text=="回零模式")
      return 0x03;
  else if(text=="找初始角")
      return 0x04;
  else return 0;
}

void Widget::on_pushButton_send_clicked()//发送PI参数按键事件
{
    QByteArray TxData;
    int check;
    //LocKp
    senddata = ui->lineEdit_LocP->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*10000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x21;
    check=0x21;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //LocKi
    senddata = ui->lineEdit_LocI->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*10000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x22;
    check=0x22;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //SpdKp
    senddata = ui->lineEdit_SpdP->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*10000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x23;
    check=0x23;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //SpdKi
    senddata = ui->lineEdit_SpdI->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*10000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x24;
    check=0x24;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //IKp
    senddata = ui->lineEdit_IP->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*10000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x25;
    check=0x25;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //IKi
    senddata = ui->lineEdit_II->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*10000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x26;
    check=0x26;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_zero_clicked() //较零
{
    QByteArray TxData;
    TxData.resize(8);
    TxData[0]=0xAA;
    TxData[1]=0x11;
    TxData[2]=0x00;
    TxData[3]=0x00;
    TxData[4]=0x00;
    TxData[5]=0x01;
    TxData[6]=0x12;
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_on_clicked()
{
    if(ui->pushButton_on->text()==tr("电机启动"))
    {
        QByteArray TxData;
        TxData.resize(8);
        TxData[0]=0xAA;
        TxData[1]=0x10;
        TxData[2]=0x00;
        TxData[3]=0x00;
        TxData[4]=0x00;
        TxData[5]=0x01;
        TxData[6]=0x11;
        TxData[7]=0x0A;
        my_serialport->write(TxData);
        ui->pushButton_on->setText(tr("电机停机"));                //按钮显示
    }
    else
    {
        QByteArray TxData;
        TxData.resize(8);
        TxData[0]=0xAA;
        TxData[1]=0x10;
        TxData[2]=0x00;
        TxData[3]=0x00;
        TxData[4]=0x00;
        TxData[5]=0x00;
        TxData[6]=0x10;
        TxData[7]=0x0A;
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


void Widget::on_pushButton_mode_clicked()
{
    QByteArray TxData;
    int check;
    int mode;

    mode=getmode(ui->comboBox_mode->currentText());//获取下拉菜单中操作模式
    convn.data=(int32_t)mode;
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x13;
    check=0x13;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_com_clicked()
{
    if(ui->pushButton_com->text()==tr("连接通讯"))
    {
        QByteArray TxData;
        TxData.resize(8);
        TxData[0]=0xAA;
        TxData[1]=0x15;
        TxData[2]=0x12;
        TxData[3]=0x34;
        TxData[4]=0x56;
        TxData[5]=0x78;
        TxData[6]=0x29;
        TxData[7]=0x0A;
        my_serialport->write(TxData);
        ui->pushButton_com->setText(tr("断开通讯"));                //按钮显示
    }
    else
    {
        QByteArray TxData;
        TxData.resize(8);
        TxData[0]=0xAA;
        TxData[1]=0x15;
        TxData[2]=0x00;
        TxData[3]=0x00;
        TxData[4]=0x00;
        TxData[5]=0x00;
        TxData[6]=0x15;
        TxData[7]=0x0A;
        my_serialport->write(TxData);
        ui->pushButton_com->setText(tr("连接通讯"));
    }
}

void Widget::on_pushButton_dir_clicked()
{
    if(ui->pushButton_dir->text()==tr("传动同向"))
    {
        QByteArray TxData;
        TxData.resize(8);
        TxData[0]=0xAA;
        TxData[1]=0x12;
        TxData[2]=0x00;
        TxData[3]=0x00;
        TxData[4]=0x00;
        TxData[5]=0x01;
        TxData[6]=0x13;
        TxData[7]=0x0A;
        my_serialport->write(TxData);
        ui->pushButton_dir->setText(tr("传动反向"));                //按钮显示
    }
    else
    {
        QByteArray TxData;
        TxData.resize(8);
        TxData[0]=0xAA;
        TxData[1]=0x12;
        TxData[2]=0x00;
        TxData[3]=0x00;
        TxData[4]=0x00;
        TxData[5]=0x00;
        TxData[6]=0x12;
        TxData[7]=0x0A;
        my_serialport->write(TxData);
        ui->pushButton_dir->setText(tr("传动同向"));
    }
}

void Widget::on_pushButton_write_clicked()  //写入flash
{
    QByteArray TxData;
    TxData.resize(8);
    TxData[0]=0xAA;
    TxData[1]=0x14;
    TxData[2]=0x00;
    TxData[3]=0x00;
    TxData[4]=0x00;
    TxData[5]=0x01;
    TxData[6]=0x15;
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_para_clicked()
{
    QByteArray TxData;
    int check;
    //Ratio
    senddata = ui->lineEdit_Ratio->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x2A;
    check=0x2A;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //Poles
    senddata = ui->lineEdit_Poles->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x2B;
    check=0x2B;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //coder
    senddata = ui->lineEdit_Coder->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x32;
    check=0x32;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //PeakI
    senddata = ui->lineEdit_PeakI->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*1000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x2C;
    check=0x2C;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //LimitSpd
    senddata = ui->lineEdit_LimitSpd->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x2D;
    check=0x2D;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //LimitI
    senddata = ui->lineEdit_LimitI->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*1000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x2E;
    check=0x2E;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //LockedSpd
    senddata = ui->lineEdit_LockedSpd->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x2F;
    check=0x2F;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
    //LockedI
    senddata = ui->lineEdit_LockedI->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*1000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x31;
    check=0x31;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_Loc1_clicked()
{
    QByteArray TxData;
    int check;
    //LocRef1
    senddata = ui->lineEdit_LocRef1->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x27;
    check=0x27;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_Loc2_clicked()
{
    QByteArray TxData;
    int check;
    //LocRef2
    senddata = ui->lineEdit_LocRef2->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x27;
    check=0x27;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_Spd1_clicked()
{
    QByteArray TxData;
    int check;
    //SpdRef1
    senddata = ui->lineEdit_SpdRef1->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x28;
    check=0x28;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_Spd2_clicked()
{
    QByteArray TxData;
    int check;
    //SpdRef2
    senddata = ui->lineEdit_SpdRef2->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)senddata;  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x28;
    check=0x28;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}


void Widget::on_pushButton_I1_clicked()
{
    QByteArray TxData;
    int check;
    //IRef1
    senddata = ui->lineEdit_IRef1->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*1000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x29;
    check=0x29;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_pushButton_I2_clicked()
{
    QByteArray TxData;
    int check;
    //IRef2
    senddata = ui->lineEdit_IRef2->text().toFloat();//读取输入框内数据，转换为float
    convn.data=(int32_t)(senddata*1000);  //float转换为int类型，4字节，存入共同体内
    TxData.resize(8);
    TxData[0]=0xAA;//header
    TxData[1]=0x29;
    check=0x29;
    TxData[2]=convn.byte[3];//高字节
    check+=TxData[2];
    TxData[3]=convn.byte[2];
    check+=TxData[3];
    TxData[4]=convn.byte[1];
    check+=TxData[4];
    TxData[5]=convn.byte[0];
    check+=TxData[5];
    TxData[6]=check&0xFF;  //check
    TxData[7]=0x0A;
    my_serialport->write(TxData);
}

void Widget::on_checkBox_clicked()
{
    SigCnt=0;  //复位0
    if(ui->checkBox->checkState() == Qt::Checked)
    {
      checkstatus=1;
    }
    else
    {
      checkstatus=0;
    }

}

void Widget::on_pushButton_Sine_clicked()
{
    if(ui->pushButton_Sine->text()==tr("开启"))
    {
       sinestatus=1;
       ui->pushButton_Sine->setText(tr("停止"));                //按钮显示
    }
    else
    {
       sinestatus=0;
       ui->pushButton_Sine->setText(tr("开启"));
    }
}
