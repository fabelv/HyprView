#include <QObject>

#include "qml_monitor.h"

namespace qtbridge {

class QmlMonitorHelpers : public QObject {
    Q_OBJECT

   public:
    Q_INVOKABLE static QList<QString> getAvailableMirrorMonitors(
        QmlMonitor* selectedQmlMonitor, const QList<QObject*>& qmlMonitors);
};

}  // namespace qtbridge
