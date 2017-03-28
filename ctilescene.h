#ifndef CTILESCENE_H
#define CTILESCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CTileScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CTileScene(QObject *parent = 0,const QRectF &rect=QRectF(-300,-300,600,600));
    void drawGrid(int cellsize);
    void addItem(QGraphicsItem* item,const QString &name);

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

signals:

public slots:
};

#endif // CTILESCENE_H
