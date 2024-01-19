#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>

class MoveItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit MoveItem(QRectF coordinates, QGraphicsItem *parent = 0);
    ~MoveItem();

    QColor color() const;
    void setColor(const QColor &color);

    bool is_moving() const;
    void setIs_moving(bool is_moving);

    int i_taken_ring() const;
    void setI_taken_ring(int i_taken_ring);

signals:
    void step();
    void stop_game();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual QPainterPath shape() const override ;

    QPointF m_hotPoint; // позиция курсора на элементе при нажатии на кнопку

    QRectF m_coordinates;
    bool m_is_moving = false; //флаг, движемо кольцо или нет
    bool is_ring = true;
    QColor m_color = Qt::green; //цвет кольца
    QPointF initial_position; //изначальная позиция кольца до захвата
    int m_i_taken_ring; //индекс взятого элемента

public slots:
};

#endif // MOVEITEM_H
