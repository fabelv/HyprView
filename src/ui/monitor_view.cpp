#include "monitor_view.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <qgraphicsitem.h>

MonitorView::MonitorView(Monitor monitor, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), monitor(monitor) {
    
    setRect(0, 0, monitor.getWidth() / 10, monitor.getHeight() / 10);
    setBrush(QBrush(Qt::gray));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    textItem = new QGraphicsTextItem(QString::fromStdString(monitor.getName()), this);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setFont(QFont("Arial", 10));
    textItem->setPos(rect().width() / 2 - textItem->boundingRect().width() / 2,
                     rect().height() / 2 - textItem->boundingRect().height() / 2);
}

void MonitorView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    dragStartPos = event->scenePos();
    setBrush(QBrush(Qt::blue));  
    emit monitorSelected(monitor);
    QGraphicsRectItem::mousePressEvent(event);
}

void MonitorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    setPos(pos() + event->scenePos() - dragStartPos);
    dragStartPos = event->scenePos();
    QGraphicsRectItem::mouseMoveEvent(event);
}

void MonitorView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    setBrush(QBrush(Qt::gray));
    QGraphicsRectItem::mouseReleaseEvent(event);
}
