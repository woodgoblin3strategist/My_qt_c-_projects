#include "moveitem.h"

MoveItem::MoveItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{

}

MoveItem::~MoveItem()
{

}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

QPainterPath MoveItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-30,-30,60,60);
    (void)option;
    (void)widget;
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /*вызываем родительскю функцию для перемещения элемента
    (для синхронизации позиций курсора)--------*/
     //QGraphicsItem::mouseMoveEvent(event);

    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    QPointF f = event->lastScenePos();
    qDebug() << f.x() << " - "
                << f.y() << "\n";
    this->setPos(event->scenePos() - m_hotPoint);

    if(!collidingItems().isEmpty()){
        this->setPos(event->lastScenePos() - event->lastPos());
        QCursor::setPos(event->lastScreenPos());
    }
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mousePressEvent(event);
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    (void)event;
    m_hotPoint = event->pos(); // позиция курсора на элементе при нажатии на кнопку
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mouseReleaseEvent(event);
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    (void)event;
}
