#ifndef GAME2048_H
#define GAME2048_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <vector>
#include <ctime>
#include <cstdlib>

class Game2048 : public QMainWindow
{
    Q_OBJECT

public:
    Game2048(QWidget *parent = nullptr);
    ~Game2048();

private:
    static const int SIZE = 4; // 4x4网格
    int board[SIZE][SIZE];     // 游戏数据
    QPushButton *cells[SIZE][SIZE]; // 界面单元格
    QLabel *scoreLabel;        // 分数显示
    int score;                 // 当前分数
    bool gameOver;             // 游戏是否结束

    void initializeGame();     // 初始化游戏
    void drawBoard();          // 绘制游戏界面
    bool addNewNumber();       // 添加新数字(2或4)
    void keyPressEvent(QKeyEvent *event) override; // 处理键盘事件

    // 移动函数，返回是否成功移动
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();

    // 检查游戏是否结束
    bool checkGameOver();

    // 辅助函数：处理一行的左移和合并
    bool processRow(int row);

    // 辅助函数：转置矩阵(用于上下移动)
    void transposeBoard();

    // 辅助函数：反转每一行(用于右移)
    void reverseRows();

private slots:
    void newGame();            // 开始新游戏
};

#endif // GAME2048_H
