#include "studyfirst.h"
#include <QPushButton>

#include"mypushbutton.h"
#include<QDebug>
studyfirst::studyfirst(QWidget *parent)
    : QWidget(parent)
{
    QPushButton * btn=new QPushButton("first",this);
    //  btn->show();
    btn->resize(80,60);
    resize(600,600);






    MyPushButton * mybtn=new MyPushButton();
mybtn->move(100,100);
mybtn->resize(80,60);
mybtn->setText("my");
mybtn->setParent(this);

//connect(mybtn,&QPushButton::clicked,this,&QWidget::close);  //参数1：信号的发送者   参数2：发送的信号（函数地址）参数3 信号的接收者  参数4 处理的槽函数
connect(mybtn,&MyPushButton::clicked,this,&QWidget::close);


}

studyfirst::~studyfirst()
{

qDebug()<<"studyfirst的析构调用";
}

