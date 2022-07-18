#pragma once
#include <QObject>
#include <QVariant>
#include "caskserver_export.h"

class QDBusInterface;

class CASKSERVER_EXPORT CaskPower : public QObject
{
    Q_OBJECT
public:
    explicit CaskPower(QObject *parent = nullptr);
    Q_INVOKABLE void restart();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void shutdown();
    Q_INVOKABLE void sleep();

signals:
    void restartRequested();
    void logoutRequested();
    void shutdownRequested();
    void sleepRequested();

private slots:
    void onShutdown();
    void onLogout();
    void onRestart();
    void onSleep();
private:
    QDBusInterface *m_interface = nullptr;
    void sync(const QString &key, const QVariant &value =  QVariant());
    void setConnections();

signals:

};

