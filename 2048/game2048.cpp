#include "game2048.h"
#include <QMessageBox>
#include <QFont>
#include <QPalette>
#include <QBrush>
#include <QColor>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>

Game2048::Game2048(QWidget *parent)
    : QMainWindow(parent), score(0), gameOver(false)
{
    // 设置窗口
    setWindowTitle("2048 Game");
    setFixedSize(400, 500);

    // 初始化随机数生成器
    srand(time(nullptr));

    // 创建主布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 顶部信息区
    QHBoxLayout *topLayout = new QHBoxLayout();

    QLabel *titleLabel = new QLabel("2048", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    topLayout->addWidget(titleLabel);

    scoreLabel = new QLabel("Score: 0", this);
    QFont scoreFont = scoreLabel->font();
    scoreFont.setPointSize(16);
    scoreLabel->setFont(scoreFont);
    topLayout->addWidget(scoreLabel);

    QPushButton *newGameButton = new QPushButton("New Game", this);
    connect(newGameButton, &QPushButton::clicked, this, &Game2048::newGame);
    topLayout->addWidget(newGameButton);

    mainLayout->addLayout(topLayout);

    // 游戏网格
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(10); // 单元格间距

    // 初始化单元格按钮
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cells[i][j] = new QPushButton(this);
            cells[i][j]->setFixedSize(80, 80);
            QFont cellFont = cells[i][j]->font();
            cellFont.setPointSize(18);
            cellFont.setBold(true);
            cells[i][j]->setFont(cellFont);
            cells[i][j]->setStyleSheet("background-color: #cdc1b4; color: #776e65; border-radius: 5px;");
            gridLayout->addWidget(cells[i][j], i, j);
        }
    }

    mainLayout->addLayout(gridLayout);
    setCentralWidget(centralWidget);

    // 开始新游戏
    newGame();
}

Game2048::~Game2048()
{
    // 自动释放Qt控件
}

void Game2048::initializeGame()
{
    // 初始化游戏板
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }

    score = 0;
    scoreLabel->setText("Score: 0");
    gameOver = false;

    // 初始添加两个数字
    addNewNumber();
    addNewNumber();

    drawBoard();
}

void Game2048::drawBoard()
{
    // 根据board数据更新界面
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int value = board[i][j];
            if (value == 0) {
                cells[i][j]->setText("");
                cells[i][j]->setStyleSheet("background-color: #cdc1b4; color: #776e65; border-radius: 5px;");
            } else {
                cells[i][j]->setText(QString::number(value));

                // 根据不同的值设置不同的背景颜色
                QString style;
                switch (value) {
                    case 2: style = "background-color: #eee4da;"; break;
                    case 4: style = "background-color: #ede0c8;"; break;
                    case 8: style = "background-color: #f2b179; color: #f9f6f2;"; break;
                    case 16: style = "background-color: #f59563; color: #f9f6f2;"; break;
                    case 32: style = "background-color: #f67c5f; color: #f9f6f2;"; break;
                    case 64: style = "background-color: #f65e3b; color: #f9f6f2;"; break;
                    case 128: style = "background-color: #edcf72; color: #f9f6f2;"; break;
                    case 256: style = "background-color: #edcc61; color: #f9f6f2;"; break;
                    case 512: style = "background-color: #edc850; color: #f9f6f2;"; break;
                    case 1024: style = "background-color: #edc53f; color: #f9f6f2;"; break;
                    case 2048: style = "background-color: #edc22e; color: #f9f6f2;"; break;
                    default: style = "background-color: #3c3a32; color: #f9f6f2;";
                }
                style += "border-radius: 5px; font-weight: bold; font-size: 18px;";
                cells[i][j]->setStyleSheet(style);
            }
        }
    }
}

bool Game2048::addNewNumber()
{
    // 查找所有空单元格
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyCells.emplace_back(i, j);
            }
        }
    }

    // 如果没有空单元格，返回false
    if (emptyCells.empty()) {
        return false;
    }

    // 随机选择一个空单元格
    int index = rand() % emptyCells.size();
    int row = emptyCells[index].first;
    int col = emptyCells[index].second;

    // 90%概率生成2，10%概率生成4
    board[row][col] = (rand() % 10 == 0) ? 4 : 2;

    return true;
}

void Game2048::keyPressEvent(QKeyEvent *event)
{
    if (gameOver) {
        return; // 游戏结束时不响应按键
    }

    bool moved = false;

    // 根据按键方向移动
    switch (event->key()) {
        case Qt::Key_Left:
            moved = moveLeft();
            break;
        case Qt::Key_Right:
            moved = moveRight();
            break;
        case Qt::Key_Up:
            moved = moveUp();
            break;
        case Qt::Key_Down:
            moved = moveDown();
            break;
        default:
            QMainWindow::keyPressEvent(event); // 其他按键交给父类处理
            return;
    }

    // 如果成功移动，添加新数字并重绘
    if (moved) {
        addNewNumber();
        drawBoard();

        // 检查游戏是否结束
        if (checkGameOver()) {
            gameOver = true;
            QMessageBox::information(this, "Game Over", "Game Over! Your score: " + QString::number(score));
        }
    }
}

bool Game2048::processRow(int row)
{
    bool moved = false;
    int temp[SIZE] = {0}; // 临时存储处理后的行
    int tempIndex = 0;    // 临时数组的索引

    // 先将所有非零数字移到左边
    for (int j = 0; j < SIZE; ++j) {
        if (board[row][j] != 0) {
            if (tempIndex > 0 && temp[tempIndex - 1] == board[row][j]) {
                // 合并相同的数字
                temp[tempIndex - 1] *= 2;
                score += temp[tempIndex - 1]; // 增加分数
                moved = true;
            } else {
                // 不能合并则直接移动
                temp[tempIndex++] = board[row][j];
                if (tempIndex - 1 != j) {
                    moved = true; // 位置发生了变化
                }
            }
        }
    }

    // 将处理后的结果写回原数组
    for (int j = 0; j < SIZE; ++j) {
        board[row][j] = temp[j];
    }

    return moved;
}

bool Game2048::moveLeft()
{
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        if (processRow(i)) {
            moved = true;
        }
    }
    if (moved) {
        scoreLabel->setText("Score: " + QString::number(score));
    }
    return moved;
}

bool Game2048::moveRight()
{
    // 反转每一行，然后用左移处理，最后再反转回来
    reverseRows();
    bool moved = moveLeft();
    reverseRows();
    return moved;
}

bool Game2048::moveUp()
{
    // 转置矩阵，然后用左移处理，最后再转置回来
    transposeBoard();
    bool moved = moveLeft();
    transposeBoard();
    return moved;
}

bool Game2048::moveDown()
{
    // 转置矩阵，反转每一行，用左移处理，然后反转回来，最后再转置回来
    transposeBoard();
    reverseRows();
    bool moved = moveLeft();
    reverseRows();
    transposeBoard();
    return moved;
}

void Game2048::transposeBoard()
{
    // 转置矩阵（行变列，列变行）
    for (int i = 0; i < SIZE; ++i) {
        for (int j = i + 1; j < SIZE; ++j) {
            std::swap(board[i][j], board[j][i]);
        }
    }
}

void Game2048::reverseRows()
{
    // 反转每一行
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            std::swap(board[i][j], board[i][SIZE - 1 - j]);
        }
    }
}

bool Game2048::checkGameOver()
{
    // 检查是否还有空单元格
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                return false; // 还有空单元格，游戏未结束
            }
        }
    }

    // 检查是否有相邻的相同数字可以合并
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] == board[i][j + 1]) {
                return false; // 水平方向可以合并
            }
        }
    }

    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE - 1; ++i) {
            if (board[i][j] == board[i + 1][j]) {
                return false; // 垂直方向可以合并
            }
        }
    }

    // 没有空单元格且不能合并，游戏结束
    return true;
}

void Game2048::newGame()
{
    initializeGame();
}
