// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentStructName("")
{
    // 创建主窗口的中心部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 创建水平布局用于放置按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // 读取XML文件获取按钮信息
    QFile file("display.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
    } else {
        QDomDocument doc;
        if (doc.setContent(&file)) {
            QDomElement root = doc.documentElement();
            QDomNodeList tables = root.elementsByTagName("tabel");
            for (int i = 0; i < tables.size(); ++i) {
                QDomElement table = tables.at(i).toElement();
                if (table.attribute("display") == "1") {
                    QString structName = table.attribute("name");
                    QString buttonText = table.attribute("displayName"); // 直接使用表格的displayName属性

                    // 如果表格没有displayName属性，则使用第一个item的displayName
                    if (buttonText.isEmpty()) {
                        QDomNodeList items = table.elementsByTagName("item");
                        if (!items.isEmpty()) {
                            buttonText = items.at(0).toElement().attribute("displayName");
                        }
                    }

                    // 如果还是没有找到displayName，则使用structName
                    if (buttonText.isEmpty()) {
                        buttonText = structName;
                    }

                    structNameToButtonText[structName] = buttonText;
                    buttonTextToStructName[buttonText] = structName;

                    QPushButton *button = new QPushButton(buttonText, this);
                    buttons.append(button);
                    buttonLayout->addWidget(button);
                    connect(button, &QPushButton::clicked, [this, structName]() {
                        onButtonClicked(structName);
                    });

                    // 初始加载数据
                    storedData[structName] = readXml(structName);
                }
            }
        }
        file.close();
    }

    // 创建表格
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4);

    // 设置表头
    QStringList headers;
    headers << "序号" << "名称" << "数据类型" << "值";
    tableWidget->setHorizontalHeaderLabels(headers);

    // 将水平布局和表格添加到垂直布局
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableWidget);

    // 初始加载第一个表格数据
    if (!buttons.isEmpty()) {
        QString firstStructName = structNameToButtonText.key(buttons.first()->text());
        onButtonClicked(firstStructName);
    }
}

MainWindow::~MainWindow()
{
    // 析构函数，不需要额外操作
}

// 读取XML文件并返回指定结构体的信息
QList<QMap<QString, QString>> MainWindow::readXml(const QString &structName)
{
    QList<QMap<QString, QString>> result;
    QFile file("display.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return result;
    }

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        qDebug() << "无法解析XML文件";
        file.close();
        return result;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList tables = root.elementsByTagName("tabel");
    for (int i = 0; i < tables.size(); ++i) {
        QDomElement table = tables.at(i).toElement();
        if (table.attribute("name") == structName && table.attribute("display") == "1") {
            QDomNodeList items = table.elementsByTagName("item");
            for (int j = 0; j < items.size(); ++j) {
                QDomElement item = items.at(j).toElement();
                QMap<QString, QString> itemInfo;
                itemInfo["displayName"] = item.attribute("displayName");
                itemInfo["type"] = item.attribute("type");
                itemInfo["value"] = ""; // 这里暂时设置为空，实际应用中可以根据需要填充
                result.append(itemInfo);
            }
        }
    }
    return result;
}

// 通用的表格更新函数
void MainWindow::updateTable(const QList<QMap<QString, QString>>& data)
{
    // 使用setUpdatesEnabled避免闪烁
    tableWidget->setUpdatesEnabled(false);

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    for (int i = 0; i < data.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(data[i]["displayName"]));
        tableWidget->setItem(i, 2, new QTableWidgetItem(data[i]["type"]));
        tableWidget->setItem(i, 3, new QTableWidgetItem(data[i]["value"]));
    }

    tableWidget->setUpdatesEnabled(true);
    tableWidget->update();
}

// 从接收到的数据更新特定结构体的数据
void MainWindow::updateStructData(const QString& structName, const QMap<QString, QString>& sourceData)
{
    if (!storedData.contains(structName)) {
        return;
    }

    QList<QMap<QString, QString>>& structData = storedData[structName];
    for (int i = 0; i < structData.size(); ++i) {
        QString displayName = structData[i]["displayName"];
        // 尝试将displayName映射到sourceData中的键
        QString realKey = displayName; // 默认使用displayName作为键

        // 特殊映射关系（根据实际情况调整）
        if (structName == "FHQ") {
            if (displayName == "综合经度") realKey = "longitude";
            else if (displayName == "综合纬度") realKey = "latitude";
            else if (displayName == "高度") realKey = "altitude";
            else if (displayName == "真空速") realKey = "speed";
            else if (displayName == "x轴速度") realKey = "vx";
            else if (displayName == "y轴速度") realKey = "vy";
            else if (displayName == "z轴速度") realKey = "vz";
            else if (displayName == "俯仰角") realKey = "pitch";
            else if (displayName == "滚转角") realKey = "roll";
            else if (displayName == "偏航角") realKey = "yaw";
        } else if (structName == "JDK" || structName == "InitData" || structName == "IOS" || structName == "MIU") {
            if (displayName == "变量1") realKey = "attribute1";
            else if (displayName == "变量2") realKey = "attribute2";
            else if (displayName == "变量3") realKey = "attribute3";
            else if (displayName == "变量5") realKey = "attribute1";
            else if (displayName == "变量6") realKey = "attribute2";
            else if (displayName == "变量7") realKey = "attribute3";

        }

        if (sourceData.contains(realKey)) {
            structData[i]["value"] = sourceData[realKey];
        }
    }
}

// 按钮点击槽函数
void MainWindow::onButtonClicked(const QString& structName)
{
    currentStructName = structName;
    updateTable(storedData[structName]);
}

// 接收第二个界面发送的数据
void MainWindow::receiveData(const QList<QMap<QString, QString>>& data)
{
    qDebug() << "Received data:" << data;
    if (data.isEmpty())
    {
        qDebug() << "error";
        return;
    }

    // 更新所有结构体的数据
    for (const QString& structName : storedData.keys()) {
        // 查找对应的数据源索引
        int sourceIndex = -1;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i].contains("structName") && data[i]["structName"] == structName) {
                sourceIndex = i;
                break;
            }
        }

        // 更新数据
        if (sourceIndex >= 0 && sourceIndex < data.size()) {
            updateStructData(structName, data[sourceIndex]);
        }
    }

    // 更新当前显示的表格
    if (!currentStructName.isEmpty() && storedData.contains(currentStructName)) {
        updateTable(storedData[currentStructName]);
    }
}
