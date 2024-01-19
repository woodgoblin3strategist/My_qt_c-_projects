#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

#define X_MAX 300
#define Y_MAX 300

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
    void on_New_btn_clicked();

    void on_Time_Edit_editingFinished();

    void on_Time_Slider_valueChanged(int value);

    void on_Random_btn_clicked();

    void on_Start_btn_clicked();

    void slot1(int x, int y);

    void on_step_btn_clicked();

    int alive_cell(int x, int y);

private:
    Ui::Widget *ui;

    int timeout, max_x, max_y, n0, n1, pix;
    uint8_t arr[2][X_MAX][Y_MAX];
    QImage *img = nullptr;
    QColor fon_color = Qt::white;
    QColor pix_color = Qt::green;
    QPainter qp;
    bool run = false;
    QTimer * timer;
    void clear_arr(int k);
    void draw_arr(int k);
};
#endif // WIDGET_H
