#include "studyfirst.h"

#include <QApplication>   //包含一个应用程序类的头文件




int main(int argc, char *argv[])  //main程序入口，argc命令行变量的数量，argv命令行变量的数组
{


    QApplication a(argc, argv);  //a应用程序对象，在qt中，应用程序对象，有且只有一个
    studyfirst w;  //窗口的对象
    w.show();  //窗口对象，默认不会显示，必须要调用show方法显示窗口
    return a.exec();  //让应用程序对象进入消息循环机制
}
