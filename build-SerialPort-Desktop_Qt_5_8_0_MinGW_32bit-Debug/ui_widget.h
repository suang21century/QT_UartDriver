/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFrame *frame;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton_cmopen;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *frame_2;
    QPushButton *pushButton_zero;
    QPushButton *pushButton_on;
    QLineEdit *lineEdit_LocP;
    QPushButton *pushButton_send;
    QWidget *widget_status;
    QLabel *label;
    QComboBox *comboBox_mode;
    QPushButton *pushButton_mode;
    QPushButton *pushButton_com;
    QPushButton *pushButton_dir;
    QPushButton *pushButton_write;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit_LocI;
    QLineEdit *lineEdit_SpdP;
    QLineEdit *lineEdit_SpdI;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_II;
    QLineEdit *lineEdit_Ratio;
    QLineEdit *lineEdit_Poles;
    QLineEdit *lineEdit_Coder;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *lineEdit_PeakI;
    QLineEdit *lineEdit_LimitSpd;
    QLineEdit *lineEdit_LimitI;
    QLineEdit *lineEdit_LockedI;
    QLineEdit *lineEdit_LockedSpd;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QPushButton *pushButton_para;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_Loc2;
    QPushButton *pushButton_Loc1;
    QLineEdit *lineEdit_LocRef1;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *lineEdit_LocRef2;
    QLabel *label_26;
    QCheckBox *checkBox;
    QLineEdit *lineEdit_LocAmp;
    QLabel *label_29;
    QLineEdit *lineEdit_LocTs;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QPushButton *pushButton_Sine;
    QWidget *tab_2;
    QPushButton *pushButton_Spd2;
    QPushButton *pushButton_Spd1;
    QLineEdit *lineEdit_SpdRef2;
    QLineEdit *lineEdit_SpdRef1;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_28;
    QWidget *tab_3;
    QPushButton *pushButton_I2;
    QLineEdit *lineEdit_IRef1;
    QLineEdit *lineEdit_IRef2;
    QPushButton *pushButton_I1;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_27;
    QFrame *frame_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_x1;
    QLineEdit *lineEdit_x2;
    QLineEdit *lineEdit_y1;
    QLineEdit *lineEdit_y2;
    QPushButton *pushButton_xy;
    QTextEdit *textEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1581, 807);
        frame = new QFrame(Widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(1060, 20, 251, 111));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        comboBox = new QComboBox(frame);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 10, 91, 22));
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 50, 91, 20));
        pushButton_cmopen = new QPushButton(frame);
        pushButton_cmopen->setObjectName(QStringLiteral("pushButton_cmopen"));
        pushButton_cmopen->setGeometry(QRect(60, 80, 75, 23));
        pushButton_cmopen->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 10, 54, 12));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 50, 54, 12));
        frame_2 = new QFrame(Widget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(1020, 190, 541, 611));
        frame_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton_zero = new QPushButton(frame_2);
        pushButton_zero->setObjectName(QStringLiteral("pushButton_zero"));
        pushButton_zero->setGeometry(QRect(30, 220, 75, 23));
        pushButton_zero->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        pushButton_on = new QPushButton(frame_2);
        pushButton_on->setObjectName(QStringLiteral("pushButton_on"));
        pushButton_on->setGeometry(QRect(130, 110, 91, 51));
        pushButton_on->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        lineEdit_LocP = new QLineEdit(frame_2);
        lineEdit_LocP->setObjectName(QStringLiteral("lineEdit_LocP"));
        lineEdit_LocP->setGeometry(QRect(350, 370, 113, 20));
        pushButton_send = new QPushButton(frame_2);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(480, 430, 41, 61));
        pushButton_send->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        widget_status = new QWidget(frame_2);
        widget_status->setObjectName(QStringLiteral("widget_status"));
        widget_status->setGeometry(QRect(180, 40, 31, 31));
        widget_status->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 50, 54, 12));
        comboBox_mode = new QComboBox(frame_2);
        comboBox_mode->setObjectName(QStringLiteral("comboBox_mode"));
        comboBox_mode->setGeometry(QRect(300, 40, 91, 22));
        pushButton_mode = new QPushButton(frame_2);
        pushButton_mode->setObjectName(QStringLiteral("pushButton_mode"));
        pushButton_mode->setGeometry(QRect(420, 40, 75, 23));
        pushButton_mode->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        pushButton_com = new QPushButton(frame_2);
        pushButton_com->setObjectName(QStringLiteral("pushButton_com"));
        pushButton_com->setGeometry(QRect(30, 50, 75, 23));
        pushButton_com->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        pushButton_dir = new QPushButton(frame_2);
        pushButton_dir->setObjectName(QStringLiteral("pushButton_dir"));
        pushButton_dir->setGeometry(QRect(140, 220, 75, 23));
        pushButton_dir->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        pushButton_write = new QPushButton(frame_2);
        pushButton_write->setObjectName(QStringLiteral("pushButton_write"));
        pushButton_write->setGeometry(QRect(210, 560, 91, 31));
        pushButton_write->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 370, 54, 12));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(300, 400, 54, 12));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(300, 430, 54, 12));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(300, 460, 54, 12));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(300, 490, 54, 12));
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(300, 520, 54, 12));
        lineEdit_LocI = new QLineEdit(frame_2);
        lineEdit_LocI->setObjectName(QStringLiteral("lineEdit_LocI"));
        lineEdit_LocI->setGeometry(QRect(350, 400, 113, 20));
        lineEdit_SpdP = new QLineEdit(frame_2);
        lineEdit_SpdP->setObjectName(QStringLiteral("lineEdit_SpdP"));
        lineEdit_SpdP->setGeometry(QRect(350, 430, 113, 20));
        lineEdit_SpdI = new QLineEdit(frame_2);
        lineEdit_SpdI->setObjectName(QStringLiteral("lineEdit_SpdI"));
        lineEdit_SpdI->setGeometry(QRect(350, 460, 113, 20));
        lineEdit_IP = new QLineEdit(frame_2);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(350, 490, 113, 20));
        lineEdit_II = new QLineEdit(frame_2);
        lineEdit_II->setObjectName(QStringLiteral("lineEdit_II"));
        lineEdit_II->setGeometry(QRect(350, 520, 113, 20));
        lineEdit_Ratio = new QLineEdit(frame_2);
        lineEdit_Ratio->setObjectName(QStringLiteral("lineEdit_Ratio"));
        lineEdit_Ratio->setGeometry(QRect(110, 310, 113, 20));
        lineEdit_Poles = new QLineEdit(frame_2);
        lineEdit_Poles->setObjectName(QStringLiteral("lineEdit_Poles"));
        lineEdit_Poles->setGeometry(QRect(110, 340, 113, 20));
        lineEdit_Coder = new QLineEdit(frame_2);
        lineEdit_Coder->setObjectName(QStringLiteral("lineEdit_Coder"));
        lineEdit_Coder->setGeometry(QRect(110, 280, 113, 20));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(50, 310, 54, 12));
        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(50, 340, 54, 12));
        label_14 = new QLabel(frame_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(40, 280, 61, 20));
        lineEdit_PeakI = new QLineEdit(frame_2);
        lineEdit_PeakI->setObjectName(QStringLiteral("lineEdit_PeakI"));
        lineEdit_PeakI->setGeometry(QRect(110, 380, 113, 20));
        lineEdit_LimitSpd = new QLineEdit(frame_2);
        lineEdit_LimitSpd->setObjectName(QStringLiteral("lineEdit_LimitSpd"));
        lineEdit_LimitSpd->setGeometry(QRect(110, 410, 113, 20));
        lineEdit_LimitI = new QLineEdit(frame_2);
        lineEdit_LimitI->setObjectName(QStringLiteral("lineEdit_LimitI"));
        lineEdit_LimitI->setGeometry(QRect(110, 440, 113, 20));
        lineEdit_LockedI = new QLineEdit(frame_2);
        lineEdit_LockedI->setObjectName(QStringLiteral("lineEdit_LockedI"));
        lineEdit_LockedI->setGeometry(QRect(110, 500, 113, 20));
        lineEdit_LockedSpd = new QLineEdit(frame_2);
        lineEdit_LockedSpd->setObjectName(QStringLiteral("lineEdit_LockedSpd"));
        lineEdit_LockedSpd->setGeometry(QRect(110, 470, 113, 20));
        label_15 = new QLabel(frame_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(30, 380, 71, 20));
        label_16 = new QLabel(frame_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 410, 81, 20));
        label_17 = new QLabel(frame_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(30, 440, 71, 20));
        label_18 = new QLabel(frame_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(20, 470, 81, 20));
        label_19 = new QLabel(frame_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(30, 500, 71, 20));
        pushButton_para = new QPushButton(frame_2);
        pushButton_para->setObjectName(QStringLiteral("pushButton_para"));
        pushButton_para->setGeometry(QRect(80, 530, 75, 23));
        pushButton_para->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        tabWidget = new QTabWidget(frame_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(260, 90, 261, 251));
        tabWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_Loc2 = new QPushButton(tab);
        pushButton_Loc2->setObjectName(QStringLiteral("pushButton_Loc2"));
        pushButton_Loc2->setGeometry(QRect(190, 70, 61, 23));
        pushButton_Loc2->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        pushButton_Loc1 = new QPushButton(tab);
        pushButton_Loc1->setObjectName(QStringLiteral("pushButton_Loc1"));
        pushButton_Loc1->setGeometry(QRect(190, 40, 61, 23));
        pushButton_Loc1->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        lineEdit_LocRef1 = new QLineEdit(tab);
        lineEdit_LocRef1->setObjectName(QStringLiteral("lineEdit_LocRef1"));
        lineEdit_LocRef1->setGeometry(QRect(60, 40, 113, 20));
        label_20 = new QLabel(tab);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(0, 40, 54, 12));
        label_21 = new QLabel(tab);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(0, 70, 54, 12));
        lineEdit_LocRef2 = new QLineEdit(tab);
        lineEdit_LocRef2->setObjectName(QStringLiteral("lineEdit_LocRef2"));
        lineEdit_LocRef2->setGeometry(QRect(60, 70, 113, 20));
        label_26 = new QLabel(tab);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(90, 20, 31, 16));
        checkBox = new QCheckBox(tab);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(80, 100, 71, 16));
        lineEdit_LocAmp = new QLineEdit(tab);
        lineEdit_LocAmp->setObjectName(QStringLiteral("lineEdit_LocAmp"));
        lineEdit_LocAmp->setGeometry(QRect(60, 150, 113, 20));
        label_29 = new QLabel(tab);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 150, 31, 16));
        lineEdit_LocTs = new QLineEdit(tab);
        lineEdit_LocTs->setObjectName(QStringLiteral("lineEdit_LocTs"));
        lineEdit_LocTs->setGeometry(QRect(60, 180, 113, 20));
        label_31 = new QLabel(tab);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 180, 31, 16));
        label_32 = new QLabel(tab);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(110, 130, 31, 16));
        label_33 = new QLabel(tab);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(150, 130, 21, 16));
        label_34 = new QLabel(tab);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(50, 130, 51, 16));
        pushButton_Sine = new QPushButton(tab);
        pushButton_Sine->setObjectName(QStringLiteral("pushButton_Sine"));
        pushButton_Sine->setGeometry(QRect(190, 160, 61, 31));
        pushButton_Sine->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        pushButton_Spd2 = new QPushButton(tab_2);
        pushButton_Spd2->setObjectName(QStringLiteral("pushButton_Spd2"));
        pushButton_Spd2->setGeometry(QRect(190, 70, 61, 23));
        pushButton_Spd2->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        pushButton_Spd1 = new QPushButton(tab_2);
        pushButton_Spd1->setObjectName(QStringLiteral("pushButton_Spd1"));
        pushButton_Spd1->setGeometry(QRect(190, 40, 61, 23));
        pushButton_Spd1->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        lineEdit_SpdRef2 = new QLineEdit(tab_2);
        lineEdit_SpdRef2->setObjectName(QStringLiteral("lineEdit_SpdRef2"));
        lineEdit_SpdRef2->setGeometry(QRect(60, 70, 113, 20));
        lineEdit_SpdRef1 = new QLineEdit(tab_2);
        lineEdit_SpdRef1->setObjectName(QStringLiteral("lineEdit_SpdRef1"));
        lineEdit_SpdRef1->setGeometry(QRect(60, 40, 113, 20));
        label_22 = new QLabel(tab_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(0, 40, 54, 12));
        label_23 = new QLabel(tab_2);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(0, 70, 54, 12));
        label_28 = new QLabel(tab_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(90, 20, 31, 16));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton_I2 = new QPushButton(tab_3);
        pushButton_I2->setObjectName(QStringLiteral("pushButton_I2"));
        pushButton_I2->setGeometry(QRect(190, 70, 61, 23));
        pushButton_I2->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        lineEdit_IRef1 = new QLineEdit(tab_3);
        lineEdit_IRef1->setObjectName(QStringLiteral("lineEdit_IRef1"));
        lineEdit_IRef1->setGeometry(QRect(60, 40, 113, 20));
        lineEdit_IRef2 = new QLineEdit(tab_3);
        lineEdit_IRef2->setObjectName(QStringLiteral("lineEdit_IRef2"));
        lineEdit_IRef2->setGeometry(QRect(60, 70, 113, 20));
        pushButton_I1 = new QPushButton(tab_3);
        pushButton_I1->setObjectName(QStringLiteral("pushButton_I1"));
        pushButton_I1->setGeometry(QRect(190, 40, 61, 23));
        pushButton_I1->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        label_24 = new QLabel(tab_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(0, 40, 54, 12));
        label_25 = new QLabel(tab_3);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(0, 70, 54, 12));
        label_27 = new QLabel(tab_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(100, 20, 21, 16));
        tabWidget->addTab(tab_3, QString());
        frame_3 = new QFrame(Widget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(1340, 20, 221, 161));
        frame_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 20, 54, 12));
        label_5 = new QLabel(frame_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 90, 54, 12));
        lineEdit_x1 = new QLineEdit(frame_3);
        lineEdit_x1->setObjectName(QStringLiteral("lineEdit_x1"));
        lineEdit_x1->setGeometry(QRect(80, 10, 113, 20));
        lineEdit_x2 = new QLineEdit(frame_3);
        lineEdit_x2->setObjectName(QStringLiteral("lineEdit_x2"));
        lineEdit_x2->setGeometry(QRect(80, 40, 113, 20));
        lineEdit_y1 = new QLineEdit(frame_3);
        lineEdit_y1->setObjectName(QStringLiteral("lineEdit_y1"));
        lineEdit_y1->setGeometry(QRect(80, 70, 113, 20));
        lineEdit_y2 = new QLineEdit(frame_3);
        lineEdit_y2->setObjectName(QStringLiteral("lineEdit_y2"));
        lineEdit_y2->setGeometry(QRect(80, 100, 113, 20));
        pushButton_xy = new QPushButton(frame_3);
        pushButton_xy->setObjectName(QStringLiteral("pushButton_xy"));
        pushButton_xy->setGeometry(QRect(60, 130, 75, 23));
        pushButton_xy->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(1060, 140, 251, 41));
        frame_3->raise();
        frame->raise();
        frame_2->raise();
        textEdit->raise();

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("Widget", "115200", Q_NULLPTR));
        pushButton_cmopen->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        pushButton_zero->setText(QApplication::translate("Widget", "\346\240\241\351\233\266", Q_NULLPTR));
        pushButton_on->setText(QApplication::translate("Widget", "\347\224\265\346\234\272\345\220\257\345\212\250", Q_NULLPTR));
        lineEdit_LocP->setText(QApplication::translate("Widget", "10.0", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\347\212\266\346\200\201\347\201\257\357\274\232", Q_NULLPTR));
        pushButton_mode->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_com->setText(QApplication::translate("Widget", "\350\277\236\346\216\245\351\200\232\350\256\257", Q_NULLPTR));
        pushButton_dir->setText(QApplication::translate("Widget", "\344\274\240\345\212\250\345\220\214\345\220\221", Q_NULLPTR));
        pushButton_write->setText(QApplication::translate("Widget", "\345\206\231\345\205\245flash", Q_NULLPTR));
        label_6->setText(QApplication::translate("Widget", "\344\275\215\347\275\256P", Q_NULLPTR));
        label_7->setText(QApplication::translate("Widget", "\344\275\215\347\275\256I", Q_NULLPTR));
        label_8->setText(QApplication::translate("Widget", "\351\200\237\345\272\246P", Q_NULLPTR));
        label_9->setText(QApplication::translate("Widget", "\351\200\237\345\272\246I", Q_NULLPTR));
        label_10->setText(QApplication::translate("Widget", "\347\224\265\346\265\201P", Q_NULLPTR));
        label_11->setText(QApplication::translate("Widget", "\347\224\265\346\265\201I", Q_NULLPTR));
        lineEdit_LocI->setText(QApplication::translate("Widget", "0.002", Q_NULLPTR));
        lineEdit_SpdP->setText(QApplication::translate("Widget", "0.3", Q_NULLPTR));
        lineEdit_SpdI->setText(QApplication::translate("Widget", "0.01", Q_NULLPTR));
        lineEdit_IP->setText(QApplication::translate("Widget", "0.3", Q_NULLPTR));
        lineEdit_II->setText(QApplication::translate("Widget", "0.02", Q_NULLPTR));
        lineEdit_Ratio->setText(QApplication::translate("Widget", "100", Q_NULLPTR));
        lineEdit_Poles->setText(QApplication::translate("Widget", "4", Q_NULLPTR));
        lineEdit_Coder->setText(QApplication::translate("Widget", "512", Q_NULLPTR));
        label_12->setText(QApplication::translate("Widget", "\344\274\240\345\212\250\346\257\224", Q_NULLPTR));
        label_13->setText(QApplication::translate("Widget", "\346\236\201\345\257\271\346\225\260", Q_NULLPTR));
        label_14->setText(QApplication::translate("Widget", "\347\274\226\347\240\201\345\231\250\347\272\277\346\225\260", Q_NULLPTR));
        lineEdit_PeakI->setText(QApplication::translate("Widget", "30", Q_NULLPTR));
        lineEdit_LimitSpd->setText(QApplication::translate("Widget", "7300", Q_NULLPTR));
        lineEdit_LimitI->setText(QApplication::translate("Widget", "20", Q_NULLPTR));
        lineEdit_LockedI->setText(QApplication::translate("Widget", "10", Q_NULLPTR));
        lineEdit_LockedSpd->setText(QApplication::translate("Widget", "500", Q_NULLPTR));
        label_15->setText(QApplication::translate("Widget", "\345\263\260\345\200\274\347\224\265\346\265\201(A)", Q_NULLPTR));
        label_16->setText(QApplication::translate("Widget", "\351\200\237\345\272\246\351\231\220\345\271\205(rpm)", Q_NULLPTR));
        label_17->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\351\231\220\345\271\205(A)", Q_NULLPTR));
        label_18->setText(QApplication::translate("Widget", "\345\240\265\350\275\254\351\200\237\345\272\246(rpm)", Q_NULLPTR));
        label_19->setText(QApplication::translate("Widget", "\345\240\265\350\275\254\347\224\265\346\265\201(A)", Q_NULLPTR));
        pushButton_para->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_Loc2->setText(QApplication::translate("Widget", ">", Q_NULLPTR));
        pushButton_Loc1->setText(QApplication::translate("Widget", ">", Q_NULLPTR));
        lineEdit_LocRef1->setText(QApplication::translate("Widget", "0", Q_NULLPTR));
        label_20->setText(QApplication::translate("Widget", "\344\275\215\347\275\256\346\214\207\344\273\2441", Q_NULLPTR));
        label_21->setText(QApplication::translate("Widget", "\344\275\215\347\275\256\346\214\207\344\273\2442", Q_NULLPTR));
        lineEdit_LocRef2->setText(QApplication::translate("Widget", "10000", Q_NULLPTR));
        label_26->setText(QApplication::translate("Widget", "cnt", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Widget", "\345\276\252\347\216\257", Q_NULLPTR));
        lineEdit_LocAmp->setText(QApplication::translate("Widget", "10000", Q_NULLPTR));
        label_29->setText(QApplication::translate("Widget", "\345\271\205\345\200\274", Q_NULLPTR));
        lineEdit_LocTs->setText(QApplication::translate("Widget", "5", Q_NULLPTR));
        label_31->setText(QApplication::translate("Widget", "\345\221\250\346\234\237", Q_NULLPTR));
        label_32->setText(QApplication::translate("Widget", "cnt", Q_NULLPTR));
        label_33->setText(QApplication::translate("Widget", "s", Q_NULLPTR));
        label_34->setText(QApplication::translate("Widget", "\346\255\243\345\274\246\346\214\207\344\273\244", Q_NULLPTR));
        pushButton_Sine->setText(QApplication::translate("Widget", "\345\274\200\345\220\257", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\344\275\215\347\275\256", Q_NULLPTR));
        pushButton_Spd2->setText(QApplication::translate("Widget", ">", Q_NULLPTR));
        pushButton_Spd1->setText(QApplication::translate("Widget", ">", Q_NULLPTR));
        lineEdit_SpdRef2->setText(QApplication::translate("Widget", "0", Q_NULLPTR));
        lineEdit_SpdRef1->setText(QApplication::translate("Widget", "3000", Q_NULLPTR));
        label_22->setText(QApplication::translate("Widget", "\351\200\237\345\272\246\346\214\207\344\273\2441", Q_NULLPTR));
        label_23->setText(QApplication::translate("Widget", "\351\200\237\345\272\246\346\214\207\344\273\2442", Q_NULLPTR));
        label_28->setText(QApplication::translate("Widget", "rpm", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_I2->setText(QApplication::translate("Widget", ">", Q_NULLPTR));
        lineEdit_IRef1->setText(QApplication::translate("Widget", "0", Q_NULLPTR));
        lineEdit_IRef2->setText(QApplication::translate("Widget", "0", Q_NULLPTR));
        pushButton_I1->setText(QApplication::translate("Widget", ">", Q_NULLPTR));
        label_24->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\346\214\207\344\273\2441", Q_NULLPTR));
        label_25->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\346\214\207\344\273\2442", Q_NULLPTR));
        label_27->setText(QApplication::translate("Widget", "A", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "\347\224\265\346\265\201", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "X\350\275\264\350\256\276\347\275\256\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "Y\350\275\264\350\256\276\347\275\256\357\274\232", Q_NULLPTR));
        lineEdit_x1->setText(QApplication::translate("Widget", "-1.0", Q_NULLPTR));
        lineEdit_x2->setText(QApplication::translate("Widget", "11.0", Q_NULLPTR));
        lineEdit_y1->setText(QApplication::translate("Widget", "-10000", Q_NULLPTR));
        lineEdit_y2->setText(QApplication::translate("Widget", "10000", Q_NULLPTR));
        pushButton_xy->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
