#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenuBar>
#include<QToolBar>
#include<QDebug>
#include<QPushButton>
#include<QStatusBar>
#include<QLabel>
#include<QDockWidget>
#include<QTextEdit>
#include<QIcon>
#include<QImage>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,800);
    setWindowTitle("完整窗口");
    //***********************************************************
    //菜单栏
    QMenuBar *bar= menuBar(); //创建菜单栏 菜单栏最多只有一个
    setMenuBar(bar); //将菜单栏放入窗口
    QMenu *fileMenu= bar->addMenu("文件");//创建菜单
    QMenu *editMenu= bar->addMenu("编辑");

    QAction *newAction=  fileMenu->addAction("新建");//创建菜单项
    fileMenu->addSeparator();//添加分隔符
    fileMenu->addAction("打开");//创建菜单项
    fileMenu->addSeparator();//添加分隔符
    fileMenu->addAction("退出");//创建菜单项

    editMenu->addAction("复制");
    editMenu->addAction("粘贴");
    editMenu->addAction("全选");
    //***********************************************************
    //工具栏
    QToolBar * toolBar=new QToolBar(this);//创建工具栏    可以有多个
    addToolBar(Qt::LeftToolBarArea,toolBar);//将工具栏放入窗口
    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);//设置工具栏只能左右停靠
    toolBar->setFloatable(false);//设置浮动操作
    toolBar->setMovable(false); //设置移动 总的开关
    toolBar->addAction(newAction);//在工具栏设置内容
    toolBar->addSeparator();//添加分割线
    QPushButton *btn=new QPushButton("按钮",this);//在工具栏中添加一些控件
    toolBar->addWidget(btn);
    //***********************************************************
    //状态栏
    QStatusBar *stBar=statusBar();//创建状态栏 只能有一个
    setStatusBar(stBar);//状态栏设置在窗口中
    QLabel *label=new QLabel("提示信息",this);//放一些标签控件
    stBar->addWidget(label);
    QLabel *label2=new QLabel("提示信息",this);//把控件放在右侧
    stBar->addPermanentWidget(label2);
    //***********************************************************
    //浮动窗口(铆接部件)
    QDockWidget *dockWidget=new QDockWidget("浮动窗口",this);//创建一个浮动窗口  可以有多个
    addDockWidget(Qt::BottomDockWidgetArea,dockWidget);//浮动窗口放在底部
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea|Qt::BottomDockWidgetArea);      //设置后期停靠区域，只允许上下
    //***********************************************************
    //设置中心部件   只能有一个
    QTextEdit *edit=new QTextEdit(this);
    setCentralWidget(edit);
    //***********************************************************
    //设置ui    为菜单栏设置图标
    QIcon openIcon("C:/Users/18436/Desktop/1.jpg");//图标文件
    newAction->setIcon(openIcon);//设置图标

    //this->setWindowTitle("ICON SET");
    //QWidget *w=new QWidget;
    //setCentralWidget(w);
    //setWindowIcon(QIcon("favicon.ico"));
    setWindowIcon(QIcon(":/favicon.ico"));

    QImage *img=new QImage;





}

MainWindow::~MainWindow()
{
    delete ui;
}

