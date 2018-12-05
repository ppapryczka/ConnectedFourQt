#include "GameSquare.hpp"


GameSquare::GameSquare(float sideLength)
    :sideLength_(sideLength)
{
    brush = QBrush(QColor("blue"));
}


QRectF GameSquare::boundingRect() const{
    return QRectF(0, 0, sideLength_, sideLength_);
}

void GameSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPainterPath gameSquarePath;
    QRectF rec = boundingRect();
    QRectF recEllipse(  0 + gameSquareEllipseProcent/2*sideLength_,
                        0 + gameSquareEllipseProcent/2*sideLength_,
                        sideLength_ - gameSquareEllipseProcent*sideLength_,
                        sideLength_ - gameSquareEllipseProcent*sideLength_);

    gameSquarePath.moveTo(0, 0);
    gameSquarePath.addRect(rec);
    gameSquarePath.addEllipse(recEllipse);

    gameSquarePath.setFillRule(Qt::OddEvenFill);
    painter->setBrush(brush);

    painter->drawPath(gameSquarePath);
}
