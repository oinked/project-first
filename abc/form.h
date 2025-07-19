#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

// 定义FHQ结构体
struct FHQ {
    double longitude;
    double latitude;
    double altitude;
    double speed;
    double vx;
    double vy;
    double vz;
    double pitch;
    double roll;
    double yaw;
};

// 定义JDK结构体
struct JDK {
    int attribute1;
    short attribute2;
    double attribute3;
};

// 定义InitData结构体
struct InitData {
    int attribute1;
    short attribute2;
    double attribute3;
};
// 定义IOS结构体
struct IOS {
    int attribute1;
    short attribute2;
    double attribute3;
};

// 定义MIU结构体
struct MIU {
    int attribute1;
    short attribute2;
    double attribute3;
};


class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
};

#endif // FORM_H
