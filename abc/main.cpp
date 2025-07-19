#include "mainwindow.h"
#include "sendwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    SendWindow send;

       // 连接信号和槽
       QObject::connect(&send, &SendWindow::sendData, &w, &MainWindow::receiveData);
    w.show();
    send.show();
    return a.exec();
}
