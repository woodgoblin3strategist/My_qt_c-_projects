#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void draw_cirles();

    //void on_pushButton_2_clicked();

    void on_start_clicked();

    void draw_step();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    qreal R_main = 200;
    qreal R_second = 20;
    qreal relation = 10;
    qreal ant_rel = 0.1;
    qreal a;
    qreal b;

    QGraphicsEllipseItem* main_circle;
    QGraphicsEllipseItem* second_circle;
    QGraphicsItem* ball;
    QTimeLine *timer;
    QGraphicsItemAnimation* animation_main;
    QGraphicsItemAnimation* animation_second;
    QGraphicsPathItem* cicl;
    QPainterPath path;

};
#endif // MAINWINDOW_H
