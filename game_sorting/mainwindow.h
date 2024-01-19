#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

#include <moveitem.h>
#include <qrandom.h>

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
    void create_area();

    void on_proverkaButton_clicked();

    void deleteScene();

    void createMoveItem(int color, int size, int shape);

    bool check_area(); //проверяет пуста ли верхняя область
    bool check_color(QRectF area, QColor color); //проверяет область на правильность цвета
    bool check_size(QRectF area, QString size); //проверяет область на правильность размера
    bool check_shape(QRectF area, QString shape); //проверяет область на правильность формы

    void on_colorButton_clicked();
    void on_sizeButton_clicked();
    void on_shapeButton_clicked();
    void shape_color();
    void shape_size();
    void color_size();
    void shape_color_size();

    void on_startButton_clicked();

    void level();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    int N_ring;
    int number_level = 6;
    int len_pillar = 250; //размер стержней подстраевымый под колличество коллец
    bool is_game = false;
    int create_towers(QGraphicsRectItem* pillar_1);
    QVector <MoveItem*> items;
};
#endif // MAINWINDOW_H
