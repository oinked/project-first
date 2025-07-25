#include "mypushbutton.h"
#include<QDebug>
MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

qDebug()<<"按钮类构造调用";

}



MyPushButton::~MyPushButton()
{
    qDebug()<<"按钮类析构";
}
