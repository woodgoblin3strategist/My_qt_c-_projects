#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include <moveitem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_startGameButton_clicked();

    void step_counter();

    void stop_game();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;

    int N_ring;
    int create_towers(QGraphicsRectItem* pillar_1);
    QVector <MoveItem*> items;
    int len_pillar = 250; //размер стержней подстраевымый под колличество коллец
    int count_step;

};
#endif // WIDGET_H
