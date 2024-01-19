#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_step_btn_clicked()));
    connect(ui->Draw_label,SIGNAL(signal1(int,int)), this, SLOT(slot1(int, int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot1(int x, int y){//ручное протыкиваение ячеек
    qp.begin(img);
    int i = x / pix;
    int z = y / pix;
    if(arr[n0][i][z] == 1){
        arr[n0][i][z] = 0;
        qp.fillRect(i * pix, z * pix, pix, pix, fon_color);
    }
    else if(arr[n0][i][z] == 0){
        arr[n0][i][z] = 1;
        qp.fillRect(i * pix, z * pix, pix, pix, pix_color);
    }
    qp.end();
    ui->Draw_label->setPixmap(QPixmap::fromImage(*img));
}


void Widget::on_New_btn_clicked()
{
    n0 = 0;
    n1 = 1;
    max_x = ui->X_Edit->text().toInt();
    max_y = ui->Y_Edit->text().toInt();
    clear_arr(0);
    clear_arr(1);
    pix = ui->Pixel_Edit->text().toInt();

    int width = max_x * pix;
    int height = max_y * pix;

    if(width > ui->frame->width()){// не выходим ли за пределы ширины окна
        max_x = ui->frame->width() / pix;
        ui->X_Edit->setText(QString::number(max_x));
        width = (ui->X_Edit->text().toInt()) * pix;
    }
    if(height > ui->frame->height()){// не выходим ли за пределы высоты окна
        max_y = ui->frame->height() / pix;
        ui->Y_Edit->setText(QString::number(max_y));
        height = (ui->Y_Edit->text().toInt()) * pix;
    }

    if(img != nullptr){// очищаем рисунок ,если он уже был
        delete img;
        img = nullptr;
    }
    img = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);// задаём рисунок  с шириной высотой и цветом
    img->fill(fon_color);// заливаем цветом
    int X0 = (ui->frame->width() - width) / 2;
    int Y0 = (ui->frame->height() - height) / 2;
    ui->Draw_label->setGeometry(X0, Y0, width, height);//задаём размер и размещение лейбла в котром отобразиться img

    ui->Draw_label->setPixmap(QPixmap::fromImage(*img));// помещаем рисунок в лейбл чтоб он стал нам виден

    draw_arr(0);
}

void Widget::draw_arr(int k){//рисуем заполненное поле
    img->fill(fon_color);
    qp.begin(img);
    for(int i = 0; i < max_x; i++){
        for (int z = 0; z < max_y; z++) {
            if(arr[k][i][z] == 1){
                qp.fillRect(i * pix, z * pix, pix, pix, pix_color);
            }
        }
    }
    qp.end();
    ui->Draw_label->setPixmap(QPixmap::fromImage(*img));
}

void Widget::clear_arr(int k){//очищение массива
    for(int i = 0; i < max_x; i++){
        for(int z = 0; z < max_y; z++){
            arr[k][i][z] = 0;
        }
    }
}

int Widget::alive_cell(int x, int y){//считаем колличество живых ячеек вокруг нашей
    int result = 0;
    int temp_i, temp_j;
    if(ui->borders->isChecked()){
        for (int i = x - 1; i <= x + 1; i++){
            temp_i = i;
            if(i == -1){ temp_i = max_x - 1;}//проверяем не находится ли клетка рядом с границей
            else if(i == max_x){ temp_i = 0;}

            for (int j = y - 1; j <= y + 1; j++){
                temp_j = j;
                if(j == -1){ temp_j = max_y - 1;}//проверяем не находится ли клетка рядом с границей
                else if(j == max_y){ temp_j = 0;}

                if((arr[n0][temp_i][temp_j] == 1) && !(temp_i == x && temp_j == y)){
                    result++;
                }
            }
        }
    }
    else{
        for (int i = x - 1; i <= x + 1; i++){
            temp_i = i;
            if(i == -1){ continue; }//проверяем не находится ли клетка рядом с границей
            else if(i == max_x){ continue; }

            for (int j = y - 1; j <= y + 1; j++){
                temp_j = j;
                if(j == -1){ continue;}//проверяем не находится ли клетка рядом с границей
                else if(j == max_y){ continue;}

                if((arr[n0][temp_i][temp_j] == 1) && !(temp_i == x && temp_j == y)){
                    result++;
                }
            }
        }
    }
    return result;
}

void Widget::on_step_btn_clicked()
{
    clear_arr(n1);
    int alive;
    int z;
    for(int i = 0; i < max_x; i++){
        for(int j = 0; j < max_y; j++){
            alive = alive_cell(i, j);
            if((arr[n0][i][j] == 0) && (alive == 3)){
                arr[n1][i][j] = 1;
            }
            else if((arr[n0][i][j] == 1) && (alive > 3 || alive < 2)){
                arr[n1][i][j] = 0;
            }
            else if((arr[n0][i][j] == 1) && (alive == 3 || alive == 2)){
                arr[n1][i][j] = 1;
            }
            else{
                arr[n1][i][j] = 0;
            }
        }
    }
    z = n0;
    n0 = n1;
    n1 = z;
    draw_arr(n0);
}


void Widget::on_Time_Edit_editingFinished()//связываем поле с движком
{
    timeout = ui->Time_Edit->text().toInt();
    ui->Time_Slider->setValue(timeout);
    timer->setInterval(timeout);
}

void Widget::on_Time_Slider_valueChanged(int value)//связываем движок с полем
{
    ui->Time_Edit->setText(QString::number(value, 10));
    timeout = value;
    timer->setInterval(timeout);
}

void Widget::on_Random_btn_clicked()//задание массива рандомом
{
    int x, y;
    on_New_btn_clicked();
    int r = ui->Random_Edit->text().toInt();
    QRandomGenerator generator;
    generator.seed(QTime(0,0,0).secsTo(QTime::currentTime()));// задание рандома временем
    for(int i = 0; i < r; i++){
        x = generator.generate() % max_x;
        y = generator.generate() % max_y;
        arr[n0][x][y] = 1;//деление на максимум диапозона рандома
    }
    draw_arr(n0);
}

void Widget::on_Start_btn_clicked()//перемена значений и имени кнопки старт/стоп
{
    if(run){
        run = false;
        ui->Start_btn->setText("START");
        timer->stop();
    }
    else {
        ui->Start_btn->setText("STOP");
        run = true;
        timer->start();
    }
}
