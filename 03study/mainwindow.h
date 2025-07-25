#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"second.h"    //添加second头文件
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void openbuttonclick();
    void closebuttonclick();


private:
    Ui::MainWindow *ui;
    QPushButton *btn;//在这里把btn声明为成员变量，btn是手动创建的按钮，不是通过QT Designer设计的界面元素，所以UI：：MainWindow类中并没有btn这个成员
    QPushButton *btn2;
    second *a_second;
};
#endif // MAINWINDOW_H
