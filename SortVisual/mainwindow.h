#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QWidget>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    inline void pb2c(){on_pushButton_2_clicked();}

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_2_editingFinished();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    int max_height, max_width;
    int pen_width = 8;
    int space = 4;
    int angle = 30;

    int arr_size, max_arr, min_arr, timeout;
    int space_up = 20;

    int *arr = NULL;
    QImage *img_arr = NULL;
    QImage *img_line = NULL;
    QImage *img_res = NULL;
    QImage *img_bezier = NULL;
    QVector<QImage *> vi;


    QLabel lbl;
    QPainter qp;

    QColor fon_color = QColor(255,255,255,0);
    QColor select_color = QColor(242,242,242);
    QColor item_color = Qt::gray;
    QColor line_color = QColor(Qt::black);
    QColor beze_color = QColor(Qt::blue);

    void draw_item(int i, QColor color, bool line = false);
    void draw_array();
    void show_img(QVector<QImage *> vi, int x1 = 0, int x2 = 0);
    void draw_bezier(QImage *img, int i1, int i2);
    inline void delay();
    void qsort (int b, int e);
    void quicksort(int start, int stop);
    void quickSortT(int low, int high);
    void swap( int i, int j, int b, int e);
    int val_y(int i);

};



#endif // MAINWINDOW_H
