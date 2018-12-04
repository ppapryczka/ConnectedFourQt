#include "GameSquare.hpp"


GameSquare::GameSquare(float x, float y, float sideLength, float ellipseProcent)
    :x_(x), y_(y), sideLength_(sideLength), ellipseProcent(ellipseProcent)
{
    brush = QBrush(QColor("blue"));
}


QRectF GameSquare::boundingRect() const{
    return QRectF(x_, y_, sideLength_, sideLength_);
}

void GameSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPainterPath gameSquarePath;
    QRectF rec = boundingRect();
    QRectF recEllipse(x_+ ellipseProcent*0.5*sideLength_,
                      y_+ ellipseProcent*0.5*sideLength_,
                      sideLength_ -ellipseProcent*sideLength_,
                      sideLength_-ellipseProcent*sideLength_);

    gameSquarePath.moveTo(x_-sideLength_/2, y_+sideLength_/2);
    gameSquarePath.addRect(rec);
    gameSquarePath.addEllipse(recEllipse);

    gameSquarePath.setFillRule(Qt::OddEvenFill);
    painter->setBrush(brush);

    painter->drawPath(gameSquarePath);
}
