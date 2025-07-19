#include "sendwindow.h"
#include "ui_sendwindow.h"
#include <QRandomGenerator>
#include<QDebug>


SendWindow::SendWindow(QWidget *parent)
            :  QMainWindow(parent),
            ui(new Ui::SendWindow)
{
    ui->setupUi(this);

    // 创建定时器，每秒触发一次
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SendWindow::onTimerTimeout);
    timer->start(1000); // 1000毫秒 = 1秒
}

SendWindow::~SendWindow()
{
    delete ui;
}

void SendWindow::randomizeStructures(FHQ& fhq, JDK& jdk, InitData& initData, IOS& ios, MIU& miu)
{
    // 为FHQ结构体随机赋值
    fhq.longitude = 180.0 + QRandomGenerator::global()->generateDouble() * 360.0;
    fhq.latitude = 90.0 + QRandomGenerator::global()->generateDouble() * 180.0;
    fhq.altitude = QRandomGenerator::global()->generateDouble() * 10000.0;
    fhq.speed = QRandomGenerator::global()->generateDouble() * 1000.0;
    fhq.vx = 100.0 + QRandomGenerator::global()->generateDouble() * 200.0;
    fhq.vy = 100.0 + QRandomGenerator::global()->generateDouble() * 200.0;
    fhq.vz = 100.0 + QRandomGenerator::global()->generateDouble() * 200.0;
    fhq.pitch = 180.0 + QRandomGenerator::global()->generateDouble() * 360.0;
    fhq.roll = 180.0 + QRandomGenerator::global()->generateDouble() * 360.0;
    fhq.yaw = 180.0 + QRandomGenerator::global()->generateDouble() * 360.0;

    // 为JDK结构体随机赋值
    jdk.attribute1 = QRandomGenerator::global()->bounded(0, 100);
    jdk.attribute2 = static_cast<short>(QRandomGenerator::global()->bounded(0, 32767));
    jdk.attribute3 = QRandomGenerator::global()->generateDouble() * 100.0;

    // 为InitData结构体随机赋值
    initData.attribute1 = QRandomGenerator::global()->bounded(0, 100);
    initData.attribute2 = static_cast<short>(QRandomGenerator::global()->bounded(0, 32767));
    initData.attribute3 = QRandomGenerator::global()->generateDouble() * 100.0;

    // 为IOS结构体随机赋值
    ios.attribute1 = QRandomGenerator::global()->bounded(0, 100);
    ios.attribute2 = static_cast<short>(QRandomGenerator::global()->bounded(0, 32767));
    ios.attribute3 = QRandomGenerator::global()->generateDouble() * 100.0;

    // 为MIU结构体随机赋值
    miu.attribute1 = QRandomGenerator::global()->bounded(0, 100);
    miu.attribute2 = static_cast<short>(QRandomGenerator::global()->bounded(0, 32767));
    miu.attribute3 = QRandomGenerator::global()->generateDouble() * 100.0;
}

void SendWindow::onTimerTimeout()
{
    FHQ fhq;
    JDK jdk;
    InitData initData;
    IOS ios;
    MIU miu;

    // 随机赋值
    randomizeStructures(fhq, jdk, initData, ios, miu);

    // 构建要发送的数据
    QList<QMap<QString, QString>> data;

    // 构建FHQ数据
    QMap<QString, QString> fhqMap;
    fhqMap["structName"] = "FHQ";
    fhqMap["longitude"] = QString::number(fhq.longitude);
    fhqMap["latitude"] = QString::number(fhq.latitude);
    fhqMap["altitude"] = QString::number(fhq.altitude);
    fhqMap["speed"] = QString::number(fhq.speed);
    fhqMap["vx"] = QString::number(fhq.vx);
    fhqMap["vy"] = QString::number(fhq.vy);
    fhqMap["vz"] = QString::number(fhq.vz);
    fhqMap["pitch"] = QString::number(fhq.pitch);
    fhqMap["roll"] = QString::number(fhq.roll);
    fhqMap["yaw"] = QString::number(fhq.yaw);
    data.append(fhqMap);

    // 构建JDK数据
    QMap<QString, QString> jdkMap;
    jdkMap["structName"] = "JDK";
    jdkMap["attribute1"] = QString::number(jdk.attribute1);
    jdkMap["attribute2"] = QString::number(jdk.attribute2);
    jdkMap["attribute3"] = QString::number(jdk.attribute3);
    data.append(jdkMap);

    // 构建InitData数据
    QMap<QString, QString> initDataMap;
    initDataMap["structName"] = "InitData";
    initDataMap["attribute1"] = QString::number(initData.attribute1);
    initDataMap["attribute2"] = QString::number(initData.attribute2);
    initDataMap["attribute3"] = QString::number(initData.attribute3);
    data.append(initDataMap);

    // 构建IOS数据
    QMap<QString, QString> iosMap;
    iosMap["structName"] = "IOS";
    iosMap["attribute1"] = QString::number(ios.attribute1);
    iosMap["attribute2"] = QString::number(ios.attribute2);
    iosMap["attribute3"] = QString::number(ios.attribute3);
    data.append(iosMap);

    // 构建MIU数据
    QMap<QString, QString> miuMap;
    miuMap["structName"] = "MIU";
    miuMap["attribute1"] = QString::number(miu.attribute1);
    miuMap["attribute2"] = QString::number(miu.attribute2);
    miuMap["attribute3"] = QString::number(miu.attribute3);
    data.append(miuMap);

    // 添加调试输出
    qDebug() << "Sending data:" << data;

    // 发送数据
    emit sendData(data);
}
