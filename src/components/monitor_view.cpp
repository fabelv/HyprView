#include "monitor_view.h"

MonitorView::MonitorView(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
}

void MonitorView::setMonitors(const std::vector<Monitor>& monitors) {
    scene->clear();

    for (const auto& monitor : monitors) {
        MonitorItem *item = new MonitorItem(monitor);
        scene->addItem(item);

        connect(item, &MonitorItem::selected, this, &MonitorView::monitorSelected);
    }
}
