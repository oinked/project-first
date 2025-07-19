// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void receiveData(const QList<QMap<QString, QString>>& data);

private slots:
    void onButtonClicked(const QString& structName);

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    QList<QPushButton*> buttons;
    QMap<QString, QString> structNameToButtonText;
    QMap<QString, QString> buttonTextToStructName; // 新增映射，用于从按钮文本查找structName

    // 当前显示的数据类型
    QString currentStructName;

    // 存储接收到的所有数据
    QMap<QString, QList<QMap<QString, QString>>> storedData;

    // 读取XML文件并返回指定结构体的信息
    QList<QMap<QString, QString>> readXml(const QString &structName);

    // 通用的表格更新函数
    void updateTable(const QList<QMap<QString, QString>>& data);

    // 从接收到的数据更新特定结构体的数据
    void updateStructData(const QString& structName, const QMap<QString, QString>& sourceData);
};
#endif // MAINWINDOW_H
