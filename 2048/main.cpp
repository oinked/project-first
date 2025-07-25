#include "game2048.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game2048 w;
    //w.setWindowTitle("2048 游戏");
    w.show();

    return a.exec();
}
