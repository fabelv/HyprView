#pragma once

#include <QObject>
#include <QList>

namespace core {
    class MonitorManager;
}

class QmlMonitorManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> monitors READ getMonitors NOTIFY monitorsChanged)
    Q_PROPERTY(QObject* selectedMonitor READ getSelectedMonitor NOTIFY selectedMonitorChanged)

public:
    explicit QmlMonitorManager(core::MonitorManager* coreManager, QObject* parent = nullptr);

    Q_INVOKABLE void apply();
    Q_INVOKABLE void revertAplly();
    Q_INVOKABLE void rescan();

    QList<QObject*> getMonitors() const;
    QObject* getSelectedMonitor() const;

signals:
    void monitorsChanged();
    void selectedMonitorChanged();

private:
    core::MonitorManager* m_coreManager;
    QList<QObject*> m_monitors;
    QObject* m_selectedMonitor;
};

