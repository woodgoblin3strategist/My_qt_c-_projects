#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class MoveItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit MoveItem(QGraphicsItem *parent = 0);
    ~MoveItem();

signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual QPainterPath shape() const override ;

    QPointF m_hotPoint; // позиция курсора на элементе при нажатии на кнопку

public slots:
};

#endif // MOVEITEM_H
