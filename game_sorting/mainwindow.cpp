#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setSceneRect(-0.1, -0.1, 0.1, 0.1);


    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов


    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

static int randomBetween(int low, int high)
{
//    QTime midnight(0,0,0);
//    qsrand(midnight.secsTo(QTime::currentTime()));
    return (qrand() % ((high + 1) - low) + low);
}

static int randomProperty(int k)
{
    return (qrand() % k);
}

void MainWindow::deleteScene(){
//    for (int i = 0; i < items.length(); i++){
//        delete items[i];
//    }
    items.clear();
    scene->clear();
}

void MainWindow::createMoveItem(int i_color, int i_size, int i_shape){
    QColor color;
    QString size;
    QString shape;
    if(i_color == 0){
        color = Qt::green;
    }
    else if(i_color == 1){
        color = Qt::red;
    }
    else if(i_color == 2){
        color = Qt::yellow;
    }

    if(i_size == 0){
        size = "big";
    }
    else if(i_size == 1){
        size = "medium";
    }
    else if(i_size == 2){
        size = "small";
    }

    if(i_shape == 0){
        shape = "rect";
    }
    else if(i_shape == 1){
        shape = "circle";
    }
    else if(i_shape == 2){
        shape = "triangle";
    }

    items.push_back(new MoveItem(color, size, shape));
    scene->addItem(items.back());
    items.back()->setPos(randomBetween(-300, 300),
                         randomBetween(-220,-10));
    while(!items.back()->collidingItems().isEmpty()){
        items.back()->setPos(randomBetween(-300, 300),
                             randomBetween(-220,-10));
    }
    connect(items.back(), &MoveItem::stop_game, this, &MainWindow::on_proverkaButton_clicked);
}

void MainWindow::create_area(){
    //count_step = 0; //обнуляем колличество шагов
    //ui->lcdNumber->display(count_step);
    deleteScene();
    QList <QVariant> i_ring;
    i_ring.append(100);

    QGraphicsRectItem* pillar_1 =
    scene->addRect(QRectF(-150 ,0 , 10, len_pillar),
    QPen(Qt::gray),
    QBrush(Qt::gray)
    );
    pillar_1->setData(0, 0); //ключ 0 со значением 0, значит, что объект pillar и сквозь него может проходить кольцо
    pillar_1->setData(1, 1); //ключ 1 с номером стержня

    QGraphicsRectItem* pillar_2 =
    scene->addRect(QRectF(150, 0, 10, len_pillar),
    QPen(Qt::gray),
    QBrush(Qt::gray)
    );
    pillar_2->setData(0, 0);
    pillar_2->setData(1, 2);
    pillar_2->setData(2, len_pillar);
    pillar_2->setData(11, i_ring); //последовательность коллец на первом стержне

    QGraphicsRectItem* footing =
    scene->addRect(QRectF(-500, len_pillar, 1000, len_pillar),
    QPen(Qt::gray),
    QBrush(Qt::gray)
    );
    footing->setData(0, 1);

}

void MainWindow::on_colorButton_clicked()
{
    number_level = 0;
    scene->clear();
    create_area();
    //QRectF coordinates (15, -15, 15, 15);

    ui->lineEdit_1->setText("green");
    ui->lineEdit_2->setText("red");
    ui->lineEdit_3->setText("yellow");

    createMoveItem(0, 0, 0);
    createMoveItem(1, 0, 0);
    createMoveItem(2, 0, 0);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_color = randomProperty(3);
        createMoveItem(int_color, 0, 0);
    }
}

bool MainWindow::check_area(){
    QRectF area(-400 ,-270 , 1000, len_pillar+20);
    for (int i = 0; i < items.length(); i++) {
        if(area.contains(items[i]->scenePos())){
            return false;
        }
    }
    return true;
}

bool MainWindow::check_color(QRectF area, QColor color){

    for (int i = 0; i < items.length(); i++) {
        if(area.contains(items[i]->scenePos())){
            color = items[i]->color();
            break;
        }
    }
    //bool is_right_area = true;
    for (int i = 0; i < items.length(); i++) {
        //qDebug() << items.back()->scenePos();
        if(area.contains(items[i]->scenePos())){
            if(items[i]->color() != color){
                return false;
            }
        }

    }
    return true;
}

bool MainWindow::check_size(QRectF area, QString size){

    for (int i = 0; i < items.length(); i++) {
        if(area.contains(items[i]->scenePos())){
            size = items[i]->size();
            break;
        }
    }

    for (int i = 0; i < items.length(); i++) {
        //qDebug() << items.back()->scenePos();
        if(area.contains(items[i]->scenePos())){
            if(items[i]->size() != size){
                return false;
            }
        }

    }
    return true;
}

bool MainWindow::check_shape(QRectF area, QString shape){ //проверка формы

    for (int i = 0; i < items.length(); i++) {
        if(area.contains(items[i]->scenePos())){
            shape = items[i]->shape_figure();
            break;
        }
    }
    for (int i = 0; i < items.length(); i++) {
        //qDebug() << items.back()->scenePos();
        if(area.contains(items[i]->scenePos())){
            if(items[i]->shape_figure() != shape){
                return false;
            }
        }
    }
    return true;
}

void MainWindow::on_proverkaButton_clicked()
{
    if (number_level == 0){
        if(check_area()){
            if( check_color(QRectF(-400 ,0 , 250, len_pillar), Qt::green) &&
                check_color(QRectF(-140 ,0 , 290, len_pillar), Qt::red)&&
                check_color(QRectF(160 ,0 , 250, len_pillar), Qt::yellow)){
                qDebug() << "да";
                if(is_game){
                    number_level++;
                    level();
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Победа");
                    msgBox.exec();
                    deleteScene();
                }

            }
        }
    }
    else if(number_level == 1){
        if(check_area()){
            if( check_size(QRectF(-400 ,0 , 250, len_pillar), "big") &&
                check_size(QRectF(-140 ,0 , 290, len_pillar), "medium")&&
                check_size(QRectF(160 ,0 , 250, len_pillar), "small")){
                qDebug() << "да";
                if(is_game){
                    number_level++;
                    level();
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Победа");
                    msgBox.exec();
                    deleteScene();
                }
            }
        }
    }
    else if(number_level == 2){
        if(check_area()){
            if( check_shape(QRectF(-400 ,0 , 250, len_pillar), "rect") &&
                check_shape(QRectF(-140 ,0 , 290, len_pillar), "circle")&&
                check_shape(QRectF(160 ,0 , 250, len_pillar), "triangle")){
                qDebug() << "да";
                if(is_game){
                    number_level++;
                    level();
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Победа");
                    msgBox.exec();
                    deleteScene();
                }
            }
        }
    }
    else if(number_level == 3){
        if(check_area()){
            if( check_color(QRectF(-400 ,0 , 250, len_pillar), Qt::green) &&
                check_color(QRectF(-140 ,0 , 290, len_pillar), Qt::red)&&
                check_color(QRectF(160 ,0 , 250, len_pillar), Qt::yellow)){
                qDebug() << "да";
                number_level++;
                level();
            }
            else if( check_shape(QRectF(-400 ,0 , 250, len_pillar), "rect") &&
                check_shape(QRectF(-140 ,0 , 290, len_pillar), "circle")&&
                check_shape(QRectF(160 ,0 , 250, len_pillar), "triangle")){
                qDebug() << "да";
                number_level++;
                level();
            }
        }
    }
    else if(number_level == 4){
        if(check_area()){
            if( check_shape(QRectF(-400 ,0 , 250, len_pillar), "rect") &&
                check_shape(QRectF(-140 ,0 , 290, len_pillar), "circle")&&
                check_shape(QRectF(160 ,0 , 250, len_pillar), "triangle")){
                qDebug() << "да";
                number_level++;
                level();
            }
            else if( check_size(QRectF(-400 ,0 , 250, len_pillar), "big") &&
                check_size(QRectF(-140 ,0 , 290, len_pillar), "medium")&&
                check_size(QRectF(160 ,0 , 250, len_pillar), "small")){
                qDebug() << "да";
                number_level++;
                level();
            }
        }
    }
    else if(number_level == 5){
        if(check_area()){
            if( check_color(QRectF(-400 ,0 , 250, len_pillar), Qt::green) &&
                check_color(QRectF(-140 ,0 , 290, len_pillar), Qt::red)&&
                check_color(QRectF(160 ,0 , 250, len_pillar), Qt::yellow)){
                qDebug() << "да";
                number_level++;
                level();
            }
            else if( check_size(QRectF(-400 ,0 , 250, len_pillar), "big") &&
                check_size(QRectF(-140 ,0 , 290, len_pillar), "medium")&&
                check_size(QRectF(160 ,0 , 250, len_pillar), "small")){
                qDebug() << "да";
                number_level++;
                level();
            }
        }
    }
    else if(number_level == 6){
        if(check_area()){
            //все комбинации по форме
            if( check_shape(QRectF(-400 ,0 , 250, len_pillar), "rect") &&
                check_shape(QRectF(-140 ,0 , 290, len_pillar), "circle")&&
                check_shape(QRectF(160 ,0 , 250, len_pillar), "triangle")){
                qDebug() << "да";
                number_level++;
                level();
                deleteScene();
                QMessageBox msgBox;
                msgBox.setWindowTitle("Победа");
                msgBox.exec();
                number_level = 0;
            }
            else if( check_color(QRectF(-400 ,0 , 250, len_pillar), Qt::green) &&
                check_color(QRectF(-140 ,0 , 290, len_pillar), Qt::red)&&
                check_color(QRectF(160 ,0 , 250, len_pillar), Qt::yellow)){
                qDebug() << "да";
                number_level++;
                level();
                deleteScene();
                QMessageBox msgBox;
                msgBox.setWindowTitle("Победа");
                msgBox.exec();
                number_level = 0;
            }
            else if( check_size(QRectF(-400 ,0 , 250, len_pillar), "big") &&
                check_size(QRectF(-140 ,0 , 290, len_pillar), "medium")&&
                check_size(QRectF(160 ,0 , 250, len_pillar), "small")){
                qDebug() << "да";
                number_level++;
                level();
                deleteScene();
                QMessageBox msgBox;
                msgBox.setWindowTitle("Победа");
                msgBox.exec();
                number_level = 0;
            }
        }
    }
}

void MainWindow::on_sizeButton_clicked()
{
    number_level = 1;
    deleteScene();
    create_area();

    ui->lineEdit_1->setText("big");
    ui->lineEdit_2->setText("medium");
    ui->lineEdit_3->setText("small");

    createMoveItem(0, 0, 0);
    createMoveItem(0, 1, 0);
    createMoveItem(0, 2, 0);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_size = randomProperty(3);
        createMoveItem(0, int_size, 0);
    }

}

void MainWindow::on_shapeButton_clicked()
{
    number_level = 2;
    deleteScene();
    create_area();

    ui->lineEdit_1->setText("rect");
    ui->lineEdit_2->setText("circle");
    ui->lineEdit_3->setText("triangle");

    createMoveItem(0, 0, 0);
    createMoveItem(0, 0, 1);
    createMoveItem(0, 0, 2);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_shape = randomProperty(3);
        createMoveItem(0, 0, int_shape);
    }
}

void MainWindow::shape_color(){
    scene->clear();
    create_area();

    ui->lineEdit_1->setText("green rect");
    ui->lineEdit_2->setText("red circle");
    ui->lineEdit_3->setText("yellow triangle");

    createMoveItem(0, 0, 0);
    createMoveItem(1, 0, 1);
    createMoveItem(2, 0, 2);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_color = randomProperty(3);
        int int_shape = randomProperty(3);

        createMoveItem(int_color, 0, int_shape);
    }
}

void MainWindow::shape_size(){
    scene->clear();
    create_area();

    ui->lineEdit_1->setText("big rect");
    ui->lineEdit_2->setText("medium circle");
    ui->lineEdit_3->setText("small triangle");

    createMoveItem(0, 0, 0);
    createMoveItem(0, 1, 1);
    createMoveItem(0, 2, 2);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_size = randomProperty(3);
        int int_shape = randomProperty(3);
        createMoveItem(0, int_size, int_shape);
    }
}

void MainWindow::color_size(){
    scene->clear();
    create_area();

    ui->lineEdit_1->setText("green big");
    ui->lineEdit_2->setText("red medium");
    ui->lineEdit_3->setText("yellow small");

    createMoveItem(0, 0, 0);
    createMoveItem(1, 1, 0);
    createMoveItem(2, 2, 0);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_color = randomProperty(3);
        int int_size = randomProperty(3);
        createMoveItem(int_color, int_size, 0);
    }
}

void MainWindow::shape_color_size(){
    scene->clear();
    create_area();

    ui->lineEdit_1->setText("green big rect");
    ui->lineEdit_2->setText("red medium circle");
    ui->lineEdit_3->setText("yellow small triangle");

    createMoveItem(0, 0, 0);
    createMoveItem(1, 1, 1);
    createMoveItem(2, 2, 2);

    int N = randomBetween(2, 7);

    for(int i = 0; i < N; i++){
        int int_color = randomProperty(3);
        int int_size = randomProperty(3);
        int int_shape = randomProperty(3);
        createMoveItem(int_color, int_size, int_shape);
    }
}

void MainWindow::level(){
    if (number_level == 0){
        on_colorButton_clicked();
    }
    else if(number_level == 1){
        on_sizeButton_clicked();
    }
    else if(number_level == 2){
        on_shapeButton_clicked();
    }
    else if(number_level == 3){
        shape_color();
    }
    else if(number_level == 4){
        shape_size();
    }
    else if(number_level == 5){
        color_size();
    }
    else if(number_level == 6){
        shape_color_size();
    }
}

void MainWindow::on_startButton_clicked()
{
    is_game = true;
    number_level = 0;
    level();
}
