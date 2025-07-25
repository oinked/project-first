#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , a_second(nullptr)//初始化新窗口指针为空
{
    ui->setupUi(this);
//***********************************************************
    QPushButton * btn = new QPushButton("open", this);
    QPushButton * btn2=new QPushButton("close",this);
    resize(800, 800);

//***********************************************************

    QWidget *centralWidget = new QWidget(this);// 创建一个中央部件
    QVBoxLayout * layout = new QVBoxLayout(centralWidget); // 将布局设置给中央部件，而不是主窗口
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(btn);
    layout->addWidget(btn2);
    setCentralWidget(centralWidget);// 设置中央部件
//***********************************************************
    connect(btn,&QPushButton::clicked,this,&MainWindow::openbuttonclick);//将open按钮的点击信号与槽函数连接
    connect(btn2,&QPushButton::clicked,this,&MainWindow::closebuttonclick); // 将close按钮的点击信号与槽函数连接
}



MainWindow::~MainWindow()//主窗口析构函数
{
    delete ui;
}


void MainWindow::openbuttonclick()// 当open按钮被点击时调用
{
    if(a_second==nullptr)// 判断检查新窗口是否已经存在，如果不存在才创建
    {
        a_second=new second;//
        a_second->setAttribute(Qt::WA_DeleteOnClose); // 设置窗口关闭时自动删除，避免内存泄漏
        connect(a_second,&second::destroyed,this, [this]() { a_second = nullptr; }); // 当新窗口关闭时，将second指针重置为nullptr
    }

    a_second->show();//显示第二个窗口
}



void MainWindow::closebuttonclick()//点击close时被调用
{
    if(a_second!=nullptr)// 检查新窗口是否存在，如果存在则关闭
    {
        a_second->close();
    }
}















