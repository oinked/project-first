#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QList>
#include <QMap>

#include "form.h"

//QT_BEGIN_NAMESPACE
namespace Ui
{
class SendWindow;
}
//QT_END_NAMESPACE

class SendWindow : public QMainWindow
{
    Q_OBJECT

public:
    SendWindow(QWidget *parent = nullptr);
    ~SendWindow();

signals:
    // 定义发送数据的信号
    void sendData(const QList<QMap<QString, QString>>& data);

private slots:
    // 定时器触发的槽函数
    void onTimerTimeout();

private:
    Ui::SendWindow *ui;
    QTimer *timer;
    // 为结构体随机赋值的函数
    void randomizeStructures(FHQ& fhq, JDK& jdk, InitData& initData, IOS& ios, MIU& miu);
};
#endif // SENDWINDOW_H
