#include "ctilescene.h"
#include <QDebug>

CTileScene::CTileScene(QObject *parent,const QRectF &rect) : QGraphicsScene(parent) {
    this->setSceneRect(rect);
    drawGrid(32);
}

void CTileScene::drawGrid(int cellsize) {
    auto o1 = this->addLine(QLineF(QPointF(-25,0),QPointF(25,0)),QPen(Qt::blue));
    o1->setData(0,"XAxis");
    auto o2 = this->addLine(QLineF(QPointF(0,-25),QPointF(0,25)),QPen(Qt::blue));
    o2->setData(0,"YAxis");
    auto r = this->addRect(this->sceneRect(),QPen(Qt::black));
    r->setData(0,"Boundary");
}

void CTileScene::addItem(QGraphicsItem *item,const QString &name) {
    item->setData(0,name);
    QGraphicsScene::addItem(item);
}
/**

 * @param mouseEvent
 *
 * Need to setMouseTracking = true in the view
 */
void CTileScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    //qDebug() << mouseEvent->scenePos();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
