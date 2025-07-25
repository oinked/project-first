#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"teacher.h"
#include"stdent.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;


//    Teacher * tea;
//    Stdent *std;
//void classIsOver();


};
#endif // WIDGET_H
