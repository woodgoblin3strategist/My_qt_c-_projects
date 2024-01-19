#include "widget.h"
#include "ui_widget.h"

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Косметическая подготовка приложения
//    this->resize(640,640);          // Устанавливаем размеры окна приложения
//    this->setFixedSize(640,640);

    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setSceneRect(-0.1, -0.1, 0.1, 0.1);


    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов


    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);



//    scene->setSceneRect(QRectF(0,0,640,640)); // Устанавливаем размер сцены
}

Widget::~Widget()
{
    delete ui;
}

void Widget::step_counter(){//счётчик шагов
    count_step++;
    ui->lcdNumber->display(count_step);
}

void Widget::stop_game(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Победа");
    msgBox.setText("Шагов:" + QString::number(count_step));
    msgBox.exec();
    scene->clear();
}

int Widget::create_towers(QGraphicsRectItem* pillar_1){//создание колец на первом стержне
    N_ring = ui->lineEdit->text().toInt();//считываем сколько коллец надо
    int width_little_ring = 200 / N_ring; //ширина верхнего кольца(самого мелкого)
    int width_ring;
    int y = len_pillar; //расположение кольца по вертикале
    QList <QVariant> i_ring; // расположение коллец на стержне
    i_ring.append(100);
    for(int i = 0; i < N_ring; i++){
        width_ring = width_little_ring * (N_ring - i); //ширина кольца
        QRectF coordinates (-(width_ring/2), -15, width_ring, 15);
        items.push_back(new MoveItem(coordinates));
        connect(items.back(), &MoveItem::step, this, &Widget::step_counter); //соединяем сигнал шага со слотом подсчёта шагов
        connect(items.back(), &MoveItem::stop_game, this, &Widget::stop_game); //соединяем сигнал конца игры со слотом конца игры

        items.back()->setData(0, 1);//ключ 0 со значением 1, значит, что объект pillar и сквозь него не может проходить кольцо
        items.back()->setData(10, N_ring - i); //индекс кольца
        i_ring.append(N_ring - i);

        scene->addItem(items.back());
        items.back()->setPos(-245, y);

        y-=18;
    }
    items.back()->setIs_moving(true); //последнему элементу разрешаем двигаться
    pillar_1->setData(11, i_ring); //последовательность коллец на первом стержне
    return y;
}


void Widget::on_startGameButton_clicked()
{
//    int len_pillar = 250; //размер стержней подстраевымый под колличество коллец
    count_step = 0; //обнуляем колличество шагов
    ui->lcdNumber->display(count_step);
    scene->clear();
    QList <QVariant> i_ring;
    i_ring.append(100);

    QGraphicsRectItem* pillar_1 =
    scene->addRect(QRectF(-250 ,0 , 10, len_pillar),
    QPen(Qt::green),
    QBrush(Qt::green)
    );
    pillar_1->setData(0, 0); //ключ 0 со значением 0, значит, что объект pillar и сквозь него может проходить кольцо
    pillar_1->setData(1, 1); //ключ 1 с номером стержня

    QGraphicsRectItem* pillar_2 =
    scene->addRect(QRectF(0, 0, 10, len_pillar),
    QPen(Qt::red),
    QBrush(Qt::red)
    );
    pillar_2->setData(0, 0);
    pillar_2->setData(1, 2);
    pillar_2->setData(2, len_pillar);
    pillar_2->setData(11, i_ring); //последовательность коллец на первом стержне

    QGraphicsRectItem* pillar_3 =
    scene->addRect(QRectF(250, 0, 10, len_pillar),
    QPen(Qt::yellow),
    QBrush(Qt::yellow)
    );
    pillar_3->setData(0, 0);
    pillar_3->setData(1, 3);
    pillar_3->setData(2, len_pillar);
    pillar_3->setData(11, i_ring); //последовательность коллец на первом стержне
    pillar_3->setData(3, ui->lineEdit->text().toInt()); //колличество колец на третьем стрежне для победы

    QGraphicsRectItem* footing =
    scene->addRect(QRectF(-500, len_pillar, 1000, len_pillar),
    QPen(Qt::gray),
    QBrush(Qt::gray)
    );
    footing->setData(0, 1);

    int y = create_towers(pillar_1); //создаём кольца и получаем высоту
    pillar_1->setData(2, y); // высота пирамиды
}
