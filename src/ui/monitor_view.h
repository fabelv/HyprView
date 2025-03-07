#ifndef MONITOR_VIEW_H
#define MONITOR_VIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <qgraphicsitem.h>
#include "../models/monitor.h"

class MonitorView : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    MonitorView(Monitor monitor, QGraphicsItem* parent = nullptr);

signals:
    void monitorSelected(Monitor monitor);

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
