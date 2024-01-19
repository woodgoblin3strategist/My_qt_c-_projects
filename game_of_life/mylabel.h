#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QtWidgets>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent = nullptr);

signals:
    void signal1(int x, int y);

private:
    virtual void mousePressEvent(QMouseEvent *ev);

};

#endif // MYLABEL_H
