#include "moveitem.h"

MoveItem::MoveItem(QRectF coordinates, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , m_coordinates(coordinates)
{

}

MoveItem::~MoveItem()
{

}

QRectF MoveItem::boundingRect() const
{
    return this->m_coordinates;
}

QPainterPath MoveItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

int MoveItem::i_taken_ring() const
{
    return m_i_taken_ring;
}

void MoveItem::setI_taken_ring(int i_taken_ring)
{
    m_i_taken_ring = i_taken_ring;
}

bool MoveItem::is_moving() const
{
    return m_is_moving;
}

void MoveItem::setIs_moving(bool is_moving)
{
    m_is_moving = is_moving;
}

QColor MoveItem::color() const
{
    return m_color;
}

void MoveItem::setColor(const QColor &color)
{
    m_color = color;
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(m_color);
    painter->drawRect(this->m_coordinates);
    (void)option;
    (void)widget;
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)//переопределение движения мышкой
{
    if(!this->is_moving()){ //если кольцо не верхнее
        return;
    }

    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
//    QPointF f = event->lastScenePos();
//    qDebug() << f.x() << " - "
//                << f.y() << "\n";
    this->setPos(event->scenePos() - m_hotPoint);

    bool is_pillar = false;
    QList<QGraphicsItem *> obstacles = collidingItems();
    for(int i = 0; i < obstacles.count(); i++){//проверяем все объекты, есть ли среди них кольца
        if(obstacles[i]->data(0).toInt() == 1){
            is_pillar = true;
        }
        else if(obstacles[i]->data(0).toInt() == 0){
            int color_ring = obstacles[i]->data(1).toInt();
            if(color_ring == 1){
                this->setColor(Qt::green);
            }
            else if(color_ring == 2){
                this->setColor(Qt::red);
            }
            else if(color_ring == 3){
                this->setColor(Qt::yellow);
            }
        }
    }
    if(is_pillar){ //если кольцо
        this->setPos(event->lastScenePos() - event->lastPos());
        QCursor::setPos(event->lastScreenPos());
    }
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) //переопределение нажатия кнопки
{
    QList<QGraphicsItem *> obstacles = collidingItems(); //собираем все коллизии
    for(int i = 0; i < obstacles.count(); i++){//ищем на каком столбе находится кольцо, которое взяли
        if(obstacles[i]->data(0).toInt() == 0){
            int y = obstacles[i]->data(2).toInt(); //высота положенного кольца
            int color_ring = obstacles[i]->data(1).toInt(); //номер стержня
            QList <QVariant> i_ring = obstacles[i]->data(11).toList(); // расположение коллец на стержне
            //qDebug() << i_ring.back().toInt() << ":" << this->data(10).toInt();
            if(i_ring.back().toInt() == this->data(10).toInt()){ //если индекс взятого кольца совпадает
                this->setIs_moving(true);//с индексом верхнего кольца на стобе, то разрешаем движение кольца
            }
            else{
                return;
            }

            if(color_ring == 1){
                y +=18;
                obstacles[i]->setData(2,y);//новая высота(расположение для нового верхнего кольца)
                this->setI_taken_ring(i_ring.back().toInt()); //получаем индекс взятого элемента
                i_ring.pop_back();
                obstacles[i]->setData(11, i_ring);

                initial_position = event->scenePos(); //позиция где взяли кольцо
                break;
            }
            else if(color_ring == 2){
                y +=18;
                obstacles[i]->setData(2,y); //новая высота(расположение для нового верхнего кольца)
                this->setI_taken_ring(i_ring.back().toInt()); //получаем индекс взятого элемента
                i_ring.pop_back();
                obstacles[i]->setData(11, i_ring);

                initial_position = event->scenePos();
                break;
            }
            else if(color_ring == 3){
                y +=18;
                obstacles[i]->setData(2,y); //новая высота(расположение для нового верхнего кольца)
                this->setI_taken_ring(i_ring.back().toInt()); //получаем индекс взятого элемента
                i_ring.pop_back();
                obstacles[i]->setData(11, i_ring);

                initial_position = event->scenePos();
                break;
            }
        }
    }

    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    m_hotPoint = event->pos(); // позиция курсора на элементе при нажатии на кнопку
    //initial_position = event->scenePos(); //изначальная позиция кольца до захвата
    (void)event;
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->is_moving()){ //если кольцо не верхнее
        return;
    }
    bool isEmpty_area = false; //флаг для проверки, находимся ли мы в пустоте и вернёмся ли обратно
    //QGraphicsItem::mouseReleaseEvent(event);
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));

    QList<QGraphicsItem *> obstacles = collidingItems();
    if(obstacles.isEmpty()){//если кольцо ни к чему не прислонилось
        this->setPos(initial_position);
        obstacles = collidingItems();
        isEmpty_area = true;
    }

    for(int i = 0; i < obstacles.count(); i++){//проверяем все объекты, есть ли среди них кольца
        if(obstacles[i]->data(0).toInt() == 0){
            int y = obstacles[i]->data(2).toInt(); //высота положенного кольца
            int color_ring = obstacles[i]->data(1).toInt(); //номер стержня
            QList <QVariant> i_ring = obstacles[i]->data(11).toList(); // расположение коллец на стержне
            //qDebug() << i_ring;
            int i_top_ring = i_ring.back().toInt();
            //qDebug() << this->i_taken_ring() << " - " << i_top_ring;

            if((this->i_taken_ring() < i_top_ring)){
                if(color_ring == 1){
                    this->setColor(Qt::green);
                    QPointF new_position (-245, y); //новая позиция
                    this->setPos(new_position);
                    y -=18;
                    obstacles[i]->setData(2,y);
                    i_ring.append(this->i_taken_ring());
                    obstacles[i]->setData(11, i_ring); //помещаем индекс поставленного элемента в стержень

                    this->setIs_moving(false); //запрещаем движение кольца
                    if (!isEmpty_area) emit step(); //сделан шаг
                    break;
                }
                else if(color_ring == 2){
                    this->setColor(Qt::red);
                    QPointF new_position (5, y); //новая позиция
                    this->setPos(new_position);
                    y -=18;
                    obstacles[i]->setData(2,y);
                    i_ring.append(this->i_taken_ring());
                    obstacles[i]->setData(11, i_ring); //помещаем индекс поставленного элемента в стержень

                    this->setIs_moving(false); //запрещаем движение кольца
                    if (!isEmpty_area)emit step(); //сделан шаг
                    break;
                }
                else if(color_ring == 3){
                    this->setColor(Qt::yellow);
                    QPointF new_position (255, y); //новая позиция
                    this->setPos(new_position);
                    y -=18;
                    obstacles[i]->setData(2,y);
                    i_ring.append(this->i_taken_ring());
                    obstacles[i]->setData(11, i_ring); //помещаем индекс поставленного элемента в стержень

                    this->setIs_moving(false); //запрещаем движение кольца
                    if (!isEmpty_area)emit step(); //сделан шаг
                    qDebug() << i_ring.count()-1 << " : " <<obstacles[i]->data(3).toInt();
                    if(i_ring.count() - 1 == obstacles[i]->data(3).toInt()){//проверяем все ли кольца на третьем стержне
                        emit stop_game();
                    }
                    break;
                }
            }
            else{//если кольцо больше уже надетого, то его тоже нужно верстать обратно
                this->setPos(0, -100);
                mouseReleaseEvent(event);

                this->setIs_moving(false); //запрещаем движение кольца
                return;
            }

        }
    }


    (void)event;
}
