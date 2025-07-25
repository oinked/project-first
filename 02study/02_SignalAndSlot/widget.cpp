#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);




    //this->tea=new Teacher(this);  //创建一个老师对象
   // this->std=new Stdent(this); //创建一个学生对象

    //connect(tea,&Teacher::hungry,std,&Stdent::treat);
    //classIsOver();   //调用下课函数

    //无参信号和槽连接
    //void (Teacher::*teacherSignal)(QString)=&Teacher::hungry;
    //void (Stdent::*stdentSlot)(QString)=&Stdent::treat;

    //connect(tea,teacherSignal,std,stdentSlot);
    //classIsOver();



//    QPushButton * btn=new QPushButton("下课",this);

//    resize(800,800);
//    btn->resize(80,60);
//    btn->move(100,100);

//    //点击按钮，触发下课
//    //connect(btn,&QPushButton::clicked,this,&Widget::classIsOver);

//    void(Teacher:: *teacherSignal2)(void)=&Teacher::hungry;
//    void(Stdent::*stdentSlot2)(void)=&Stdent::treat;
//    connect(tea,teacherSignal2,std,stdentSlot2);


    QPushButton * btn3=new QPushButton;
    btn3->move(100,0);
    btn3->setParent(this);
    btn3->setText("按钮");
   // connect(btn3,&QPushButton::clicked,this,&Teacher::hungry);



}

//void Widget::classIsOver()
//{
//    //下课函数，调用后，触发老师饿了的信号
//    // emit tea->hungry(); //emit 触发信号
//    emit tea->hungry("juice");

//}




Widget::~Widget()
{
    delete ui;
}

