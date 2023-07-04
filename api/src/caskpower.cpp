#include "caskpower.h"
#include "serverutils.h"

#include <QDBusInterface>

CaskPower::CaskPower(QObject *parent) : QObject(parent)
{
    auto server = new ServerUtils(this);
    if(server->serverRunning())
    {
        this->setConnections();
    }

    connect(server, &ServerUtils::serverRunningChanged, [this](bool state)
    {
        if(state)
        {
            this->setConnections();
        }
    });
}

void CaskPower::restart()
{
    sync(QStringLiteral("restart"));
}

void CaskPower::logout()
{
    sync(QStringLiteral("logout"));
}

void CaskPower::shutdown()
{
    sync(QStringLiteral("shutdown"));
}

void CaskPower::sleep()
{
    sync(QStringLiteral("sleep"));
}

void CaskPower::onShutdown()
{
    Q_EMIT this->shutdownRequested();
}

void CaskPower::onLogout()
{
    Q_EMIT this->logoutRequested();
}

void CaskPower::onRestart()
{
    Q_EMIT this->restartRequested();
}

void CaskPower::onSleep()
{
    Q_EMIT this->sleepRequested();
}

void CaskPower::sync(const QString &key, const QVariant &value)
{
    if (m_interface && m_interface->isValid())
    {
        if(value.isValid())
        {
            m_interface->call(key, value);
        }else
        {
            m_interface->call(key);
        }
    }
}

void CaskPower::setConnections()
{
    if(m_interface)
    {
        m_interface->disconnect();
        m_interface->deleteLater();
        m_interface = nullptr;
    }

    m_interface = new QDBusInterface (QStringLiteral("org.cask.Server"),
                                      QStringLiteral("/Power"),
                                      QStringLiteral("org.cask.Power"),
                                      QDBusConnection::sessionBus(), this);
    if (m_interface->isValid())
    {
        connect(m_interface, SIGNAL(shutdownRequested()), this, SLOT(onShutdown()));
        connect(m_interface, SIGNAL(logoutRequested()), this, SLOT(onLogout()));
        connect(m_interface, SIGNAL(sleepRequested()), this, SLOT(onSleep()));
        connect(m_interface, SIGNAL(restartRequested()), this, SLOT(onRestart()));
    }
}
