#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setSceneRect(-0.1, -0.1, 0.1, 0.1);

//    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

//    scene->addItem(&cicl);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::draw_cirles() //рисуем круги
{
//    if(ui->spinBox->text().toInt() < 1){//если не задали отношение
//        return;
//    }
//    relation = ui->spinBox->text().toInt();//считываем отношение
    //relation = ui->lineEdit->text().toInt();//считываем отношение
//    relation = ui->lineEdit->text().toFloat();
    a = ui->spinBox->text().toInt();
    b = ui->spinBox_2->text().toInt();
    relation = a/b;

    scene->clear();

    R_second = 200 / (relation + 1);
    R_main = R_second * relation;

    main_circle = //неподвижный круг
            scene->addEllipse(QRectF(-R_main/2 ,-R_main/2 , R_main, R_main),
                              QPen(Qt::gray)
                              );
    //main_circle->setFlags(QGraphicsItem::ItemIsMovable);

    second_circle = //подвижный круг
            scene->addEllipse(QRectF(-R_second/2 ,-R_second/2 , R_second, R_second), QPen(Qt::gray));
    second_circle->setParentItem(main_circle); //задаём ему родителя неподвижный круг

    ball = scene->addEllipse(QRectF(-2 ,-2 , 4, 4), //точка
                                         QPen(Qt::red),
                                         QBrush(Qt::red));
    ball->setParentItem(second_circle);

    if(ui->radioButton->isChecked()){ //эпициклоида
        second_circle->setPos(R_main/2 + R_second/2, 0);
        ball->setPos(-R_second/2, 0);
    }
    else if(ui->radioButton_2->isChecked()){//гипоциклоида
        second_circle->setPos(R_main/2 - R_second/2, 0);
        ball->setPos(R_second/2, 0);
    }
}

void MainWindow::draw_step(){ //на каждом интервале таймера добавляем новую точку для линии
    path.lineTo(ball->scenePos());//добавляем новую точку
    cicl->setPath(path);
    scene->addItem(cicl);
}

void MainWindow::on_start_clicked()
{

    int x = ui->spinBox->text().toInt();
    int z = ui->spinBox_2->text().toInt();
    while(x%z != 0){
        x = x*2;
    }
    qreal kek = x/z;
    draw_cirles();
    cicl = new QGraphicsPathItem();
    path.clear(); //очищаем путь
    path.moveTo(ball->scenePos()); //позиция начала

    timer = new QTimeLine(5000);

    connect(timer, &QTimeLine::valueChanged, this, &MainWindow::draw_step);

    animation_main = new QGraphicsItemAnimation;
    animation_second = new QGraphicsItemAnimation;

    animation_main->setItem(main_circle);
    animation_second->setItem(second_circle);

    animation_main->setTimeLine(timer);
    animation_second->setTimeLine(timer);


    animation_main->setRotationAt(0, 0);
    animation_main->setRotationAt(1, 360*z);
    if(ui->radioButton->isChecked()){ //эпициклоида
        animation_second->setRotationAt(0, 0);
        animation_second->setRotationAt(1, 360*relation*z);
    }
    else if(ui->radioButton_2->isChecked()){//гипоциклоида
        animation_second->setRotationAt(0, 0);
        animation_second->setRotationAt(1, -360*relation*z);
    }


    timer->start();
}

void MainWindow::on_pushButton_clicked()
{
    draw_cirles();
}
