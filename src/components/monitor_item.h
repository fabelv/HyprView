
#ifndef MONITOR_ITEM_H
#define MONITOR_ITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "../models/monitor.h"

class MonitorItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    explicit MonitorItem(const Monitor& monitor, QGraphicsItem* parent = nullptr);

signals:
    void moved(int id, int newX, int newY);
    void selected(Monitor monitor);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Monitor monitor;
    QPointF dragStartPos;
    QGraphicsTextItem* textItem;
};

#endif

