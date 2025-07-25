#ifndef STDENT_H
#define STDENT_H

#include <QObject>

class Stdent : public QObject
{
    Q_OBJECT
public:
    explicit Stdent(QObject *parent = nullptr);

signals:


public slots:

    //返回值void，需要声明，也需要实现
//    //可以有参，可以发生重载
//    void treat();

//    void treat(QString foodname);

};

#endif // STDENT_H
