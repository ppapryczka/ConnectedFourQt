#include "SizeFitGraphicsView.hpp"



SizeFitGraphicsView::SizeFitGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{}

void SizeFitGraphicsView::resizeEvent(QResizeEvent *event){
    this->fitInView(QRect(0, 0, this->sceneRect().width(), this->sceneRect().height()));
}

void SizeFitGraphicsView::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    emit graphicsViewClicked(x);
}
