#include "serverutils.h"

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusServiceWatcher>

#include <QDebug>

#include <QProcess>

static const QString serverInterface(QStringLiteral("org.cask.Server"));

ServerUtils::ServerUtils(QObject *parent)
    : QObject{parent}
{
    const QDBusConnection bus = QDBusConnection::sessionBus();
    const auto registeredServices = bus.interface()->registeredServiceNames();

    if (registeredServices.isValid())
    {
        m_serverRunning = registeredServices.value().contains(serverInterface);
    }

    auto watcher = new QDBusServiceWatcher(serverInterface, QDBusConnection::sessionBus(), QDBusServiceWatcher::WatchForRegistration | QDBusServiceWatcher::WatchForUnregistration, this);

    connect(watcher, &QDBusServiceWatcher::serviceRegistered, [=](const QString &name) {
        qDebug() << "Connected to MauiMan server" << name;
        m_serverRunning = true;
        Q_EMIT serverRunningChanged(m_serverRunning);
    });

    connect(watcher, &QDBusServiceWatcher::serviceUnregistered, [=](const QString &name) {
        qDebug() << "Disconnected to MauiMan server" << name;
        m_serverRunning = false;
        Q_EMIT serverRunningChanged(m_serverRunning);
    });
}

bool ServerUtils::serverRunning() const
{
    return m_serverRunning;
}

void ServerUtils::startServer()
{
    QProcess::startDetached(QStringLiteral("CaskServer"), QStringList());
}

