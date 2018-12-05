#include "SizeFitGraphicsView.hpp"

SizeFitGraphicsView::SizeFitGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{}

void SizeFitGraphicsView::resizeEvent(QResizeEvent *event){
    this->fitInView(this->sceneRect(), Qt::KeepAspectRatio);
}

void SizeFitGraphicsView::mousePressEvent(QMouseEvent *event)
{
    auto p = mapToScene(event->pos());
    int x = p.x();
    if(x>=0)
        emit graphicsViewClicked(x);
}
