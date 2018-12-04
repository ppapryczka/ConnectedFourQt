#ifndef GAMESQUARE_HPP
#define GAMESQUARE_HPP

// qt
#include<QPainter>
#include<QGraphicsItem>
#include<QPainterPath>

class GameSquare : public QGraphicsItem
{
protected:
    float x_;
    float y_;
    float sideLength_;
    float ellipseProcent;
    QGraphicsRectItem* square_;
    QGraphicsEllipseItem* ellipse_;
    QBrush brush;

public:
    GameSquare(float x, float y, float sideLength, float ellipseProcent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // GAMESQUARE_H
