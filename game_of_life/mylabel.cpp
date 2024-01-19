#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{

}


void MyLabel::mousePressEvent(QMouseEvent *ev){
    int x = ev->x();
    int y = ev->y();
    emit signal1(x, y);
}
