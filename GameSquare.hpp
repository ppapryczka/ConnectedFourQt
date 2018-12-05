#ifndef GAMESQUARE_HPP
#define GAMESQUARE_HPP

// qt
#include<QPainter>
#include<QGraphicsItem>
#include<QPainterPath>

// connected four
#include "common.hpp"

class GameSquare : public QGraphicsItem
{
protected:
    float sideLength_;
    QBrush brush;

public:
    GameSquare(float sideLength);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // GAMESQUARE_H
