#include <stdlib.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QtWidgets>
#include <QTime>
#include <QRandomGenerator>
#include <QThread>
#include <QTimer>
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(strtoul(ui->lineEdit_2->text().toLatin1(), 0, 10));
    timeout = strtoul(ui->lineEdit_2->text().toLatin1(), 0, 10);
    line_color.setAlpha(128);
    on_pushButton_2_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] arr;
    delete img_arr;
}


inline void MainWindow::delay()
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(timeout);
    loop.exec();
}


void MainWindow::on_pushButton_clicked()
{
    int i,j;
    for (i = 1; i < arr_size ; i++ ) {
        for( j = 0; j < arr_size - i; j++){
            draw_item(j, Qt::red, true);
            draw_item(j+1, Qt::green);

            vi.clear();
            vi.append(img_arr);
            vi.append(img_line);
            show_img(vi, 0, arr_size - i);

            delay();
            if(arr[j] > arr[j+1]){
                swap( j, j + 1, 0, arr_size - i);
            }
            draw_item(j, item_color);
            draw_item(j+1, item_color);
            vi.clear();
            vi.append(img_arr);
            show_img(vi, 0, arr_size - i - 1);
        }
    }
}


void MainWindow::swap( int l, int r, int b, int e){

    int tmp;

    draw_item(l, Qt::green);
    draw_item(r, Qt::red);
    draw_bezier(img_bezier, l, r);
    vi.clear();
    vi.append(img_arr);
    vi.append(img_line);
    vi.append(img_bezier);
    show_img(vi, b, e);
    delay();

    tmp = arr[r];
    arr[r] = arr[l];
    arr[l] = tmp;

    draw_item(l, item_color);
    draw_item(r, item_color);
    draw_bezier(img_bezier, l, r);
    vi.clear();
    vi.append(img_arr);
    vi.append(img_line);
    vi.append(img_bezier);
    show_img(vi, b, e);
    delay();

}


void MainWindow::on_pushButton_2_clicked()
{

    QRandomGenerator generator;// подключение генератора рандома
    arr_size = ui->lineEdit->text().toInt();
    max_height = ui->scrollArea->size().height() - 25;
    max_width = ui->scrollArea->size().width() - 2;

    if( arr != NULL){
        delete []  arr;
        arr = NULL;
    }
    arr = new int[arr_size];
    generator.seed(QTime(0,0,0).secsTo(QTime::currentTime()));
    for( int i = 0; i < arr_size; i++){
        arr[i] = (generator.generate() % ((1000 + 1) - 0) + 0);//деление на максимум диапозона рандома
    }

    if(img_arr != NULL){
        delete img_arr;
        img_arr = NULL;
    }
    if(img_line != NULL){
        delete img_line;
        img_line = NULL;
    }
    if(img_res != NULL){
        delete img_res;
        img_res = NULL;
    }
    if(img_bezier != NULL){
        delete img_bezier;
        img_bezier = NULL;
    }
    int x = arr_size * (pen_width + space);
    max_width = x > max_width ? x: max_width;
    img_arr = new QImage(max_width, max_height, QImage::Format_ARGB32_Premultiplied);
    img_line = new QImage(max_width, max_height, QImage::Format_ARGB32_Premultiplied);
    img_res = new QImage(max_width, max_height, QImage::Format_ARGB32_Premultiplied);
    img_bezier = new QImage(max_width, max_height, QImage::Format_ARGB32_Premultiplied);
    img_arr->fill(fon_color);
    img_line->fill(fon_color);
    ui->scrollArea->setWidget(&lbl);
    ui->scrollArea->setVisible(true);

    draw_array();

}


void MainWindow::draw_array(){

    max_arr = arr[0];
    min_arr = arr[0];
    for (int i = 1; i < arr_size ; i++ ) {
        if( max_arr < arr[i]){
            max_arr = arr[i];
        }
        if (min_arr > arr[i]){
            min_arr = arr[i];
        }
    }

    img_arr->fill(fon_color);
    qp.begin(img_arr);
    qp.setRenderHint(QPainter::Antialiasing, false);
    qp.setCompositionMode(QPainter::CompositionMode_Source);
    qp.setPen(QPen(item_color, pen_width));

    for (int i = 0; i < arr_size ; i++ ) {
        int x =  i * (space + pen_width) + space;
        int y = max_height - (((arr[i]- min_arr)*((max_height - space_up) - 10))/(max_arr - min_arr))  - 5 + pen_width/2;
        qp.drawLine( x, max_height - 5 + space_up, x, y);
    }

    qp.end();

    vi.clear();
    vi.append(img_arr);
    show_img(vi);
}


void MainWindow::draw_item(int i, QColor color, bool line){

    qp.begin(img_arr);
    qp.setRenderHint(QPainter::Antialiasing, false);
    qp.setCompositionMode(QPainter::CompositionMode_Source);

    int x =  i * (space + pen_width) + space;

    qp.setPen(QPen(fon_color, pen_width));  // Clear item
    qp.drawLine( x, max_height, x, 0);

    qp.setPen(QPen(color, pen_width));
    int y = max_height - (((arr[i]- min_arr)*((max_height - space_up) - 10))/(max_arr - min_arr))  - 5 + pen_width/2;
    qp.drawLine( x, max_height - 5  + space_up, x, y);

    qp.end();

    if( line ){
        img_line->fill(fon_color);
        qp.begin(img_line);
        qp.setRenderHint(QPainter::Antialiasing, false);
        qp.setCompositionMode(QPainter::CompositionMode_Source);
        qp.setPen(QPen(line_color, 1,Qt::DashLine));
        qp.drawLine( 0, y - pen_width/2, max_width, y - pen_width/2);
        qp.end();
    }

}


void MainWindow::show_img(QVector<QImage *> vi, int x1, int x2){

    img_res->fill(Qt::white);
    qp.begin(img_res);
    qp.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if ( x2 > x1 ){
        x1 = x1 * (space + pen_width) + space;
        x2 = x2 * (space + pen_width) + space;
        qp.setPen(QPen(select_color));
        qp.setBrush(QBrush(select_color));
        qp.drawRect(x1,0, x2-x1 , max_height);
    }

    for (const auto &img:vi) {
        qp.drawImage(QPoint(0,0),*img);
    }
    qp.end();

    lbl.setPixmap(QPixmap::fromImage(*img_res));
}

int MainWindow::val_y(int i){
    return (max_height - ((arr[i]- min_arr) * (max_height - 10 - space_up))/(max_arr - min_arr) - 5);
}

void MainWindow::draw_bezier(QImage *img, int i1, int i2){

    QPainterPath path;
    QLineF l;

    img->fill(fon_color);
    if(i1 > i2){
        int i = i1;
        i1 = i2;
        i2 = i;
    }
    int y1 = val_y(i1);
    int y2 = val_y(i2);
    qp.begin(img);
    qp.setPen(QPen(beze_color, 1));
    qp.setBrush(QBrush(fon_color));
    qp.setRenderHint(QPainter::Antialiasing, true);
    QPoint p1 = QPoint(i1*(space + pen_width) + space, y1);
    QPoint p4 = QPoint(i2*(space + pen_width) + space, y2);
    QPoint p2 = QPoint(p1.x() + (p4.x() - p1.x())/5, 0);
    QPoint p3 =  QPoint(p1.x() + 4*(p4.x() - p1.x())/5, 0);

    path.moveTo(p1);
    path.cubicTo(p2,p3,p4);
    qp.drawPath(path);

    l.setLine(p1.x(), p1.y(), p2.x(), p2.y());
    l.setAngle(l.angle() + angle);
    l.setLength(8);
    qp.drawLine(l);
    l.setAngle(l.angle() + angle - 90);
    qp.drawLine(l);
    l.setLine(p4.x(), p4.y(), p3.x(), p3.y());
    l.setAngle(l.angle() + angle);
    l.setLength(8);
    qp.drawLine(l);
    l.setAngle(l.angle() + angle - 90);
    qp.drawLine(l);

    qp.end();

}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit_2->setText(QString::number(value, 10));
    timeout = value;
}


void MainWindow::on_lineEdit_2_editingFinished()
{
//    timeout = strtoul(ui->lineEdit_2->text().toLatin1(), 0, 10);
    timeout = ui->lineEdit_2->text().toInt();
    ui->horizontalSlider->setValue(timeout);
}


void MainWindow::on_pushButton_3_clicked()
{
    qsort(0, arr_size - 1);
    //    quicksort(0, arr_size-1);
    //    draw_array();
}


void MainWindow::quickSortT(int low, int high) {

    if (low >= high)
        return;// завершить выполнение если уже нечего делить

    // выбрать опорный элемент
    int middle = low + (high - low) / 2;
    int opora = arr[middle];

    // разделить на подмассивы, который больше и меньше опорного элемента
    int i = low, j = high;
    while (i <= j) {
        while (arr[i] < opora) {
            i++;
        }

        while (arr[j] > opora) {
            j--;
        }

        if (i <= j) {// меняем местами
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    // вызов рекурсии для сортировки левой и правой части
    if (low < j)
        quickSortT(low, j);

    if (high > i)
        quickSortT(i, high);
}


void MainWindow::qsort (int b, int e){

    int l = b, r = e;
    int piv = arr[(l + r) / 2]; // Опорным элементом для примера возьмём средний

    draw_item((l + r) / 2, item_color, true);
    vi.clear();
    vi.append(img_arr);
    vi.append(img_line);
    show_img(vi, b, e);
    delay();

    while (l <= r)
    {
        while (arr[l] < piv)
            l++;
        while (arr[r] > piv)
            r--;
        if (l <= r){
            if(l != r){
                swap(l, r, b, e);
            }
            l++; r--;
        }
    }

    if (b < r)
        qsort (b, r);
    if (e > l)
        qsort (l, e);

    vi.clear();
    vi.append(img_arr);
    show_img(vi);

}


void MainWindow::quicksort(int start, int stop){

    int it = start + 1, rit = stop, t;

    if(it > rit)
        return;

    while(it < rit)
        if( (arr[it]) <= (arr[start]) ) {
            ++it;
        }
        else if((arr[rit]) > (arr[start])) {
            --rit;
        }
        else {
            t = arr[it];
            arr[it] = arr[rit];
            arr[rit] = t;
        }

    if(arr[rit] >= arr[start]) {
        --rit;
    }
    if(rit != start) {
        t = arr[rit];
        arr[rit] = arr[start];
        arr[start] = t;
    }

    quicksort(start, rit - 1);
    quicksort(rit + 1, stop);
}


