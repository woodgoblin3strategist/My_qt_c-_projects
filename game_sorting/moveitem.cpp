#include "moveitem.h"

MoveItem::MoveItem(QColor color, QString size, QString shape_figure, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , m_color(color)
  , m_size(size)
  , m_shape_figure(shape_figure)
{

}

MoveItem::~MoveItem()
{

}

QRectF MoveItem::boundingRect() const
{
    QRectF s;
    if(m_size == "small"){
        s = QRectF (0, 0, 16, 16);
    }
    else if(m_size == "medium"){
        s = QRectF (0, 0, 30, 30);
    }
    else if(m_size == "big"){
        s = QRectF (0, 0, 50, 50);
    }
    return s;
}

QPainterPath MoveItem::shape() const
{
    QPainterPath path;
    if(m_shape_figure == "rect"){
        path.addRect(boundingRect());
    }
    else if(m_shape_figure == "circle"){
        path.addEllipse(boundingRect());
    }
    else if(m_shape_figure == "triangle"){
        QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
        // Помещаем координаты точек в полигональную модель
        if(m_size == "small"){
            polygon << QPoint(0,16) << QPoint(8,0) << QPoint(16,16);
        }
        else if(m_size == "medium"){
            polygon << QPoint(0,30) << QPoint(15,0) << QPoint(30,30);
        }
        else if(m_size == "big"){
            polygon << QPoint(0,50) << QPoint(25,0) << QPoint(50,50);
        }
        path.addPolygon(polygon);
    }
    return path;
}

QString MoveItem::shape_figure() const
{
    return m_shape_figure;
}

void MoveItem::setShape_figure(const QString &shape_figure)
{
    m_shape_figure = shape_figure;
}

QString MoveItem::size() const
{
    return m_size;
}

void MoveItem::setSize(const QString &size)
{
    m_size = size;
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(m_color);

    if(m_shape_figure == "rect"){
        QRectF s;
        if(m_size == "small"){
            s = QRectF (0, 0, 16, 16);
        }
        else if(m_size == "medium"){
            s = QRectF (0, 0, 30, 30);
        }
        else if(m_size == "big"){
            s = QRectF (0, 0, 50, 50);
        }
        painter->drawRect(s);
    }
    else if(m_shape_figure == "circle"){
        QRectF s;
        if(m_size == "small"){
            s = QRectF (0, 0, 16, 16);
        }
        else if(m_size == "medium"){
            s = QRectF (0, 0, 30, 30);
        }
        else if(m_size == "big"){
            s = QRectF (0, 0, 50, 50);
        }
        painter->drawEllipse(s);
    }
    else if(m_shape_figure == "triangle"){
        QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
        // Помещаем координаты точек в полигональную модель
        if(m_size == "small"){
            polygon << QPoint(0,16) << QPoint(8,0) << QPoint(16,16);
        }
        else if(m_size == "medium"){
            polygon << QPoint(0,30) << QPoint(15,0) << QPoint(30,30);
        }
        else if(m_size == "big"){
            polygon << QPoint(0,50) << QPoint(25,0) << QPoint(50,50);
        }
        painter->drawPolygon(polygon);
    }
//    painter->drawRect(this->m_coordinates);
    (void)option;
    (void)widget;
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

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)//переопределение движения мышкой
{

    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    QPointF f = event->lastScenePos();
//    qDebug() << f.x() << " - "
//                << f.y() << "\n";
    this->setPos(event->scenePos() - m_hotPoint);

    if(!collidingItems().isEmpty()){
        this->setPos(event->lastScenePos() - event->lastPos());
        QCursor::setPos(event->lastScreenPos());
    }
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) //переопределение нажатия кнопки
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    m_hotPoint = event->pos(); // позиция курсора на элементе при нажатии на кнопку
    //initial_position = event->scenePos(); //изначальная позиция кольца до захвата
    (void)event;
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));

    emit stop_game();

    (void)event;
}
