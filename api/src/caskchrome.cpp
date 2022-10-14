#include "caskchrome.h"
#include "serverutils.h"
#include <QDBusInterface>
#include <QDBusReply>
#include <QCoreApplication>

CaskChrome::CaskChrome(QObject *parent) : QObject(parent)
  ,m_appId(qApp->organizationName())
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

void CaskChrome::dropShadow(int radius, const QString &id)
{
     sync("dropShadow", radius, id.isEmpty() ? m_appId : id);
}

void CaskChrome::blurBackground(int radius, const QString &id)
{
    sync("blurBackground", radius, id.isEmpty() ? m_appId : id);
}

int CaskChrome::blurFor(const QString &id)
{
    if(m_interface)
    {
        auto call= m_interface->asyncCallWithArgumentList("blurFor", {id});
        call.waitForFinished();

        QDBusReply<int> reply = call.reply();
        return reply;
    }

    return -1;
}

int CaskChrome::shadowFor(const QString &id)
{
    if(m_interface)
    {
        auto call= m_interface->asyncCallWithArgumentList("shadowFor", {id});
        call.waitForFinished();

        QDBusReply<int> reply = call.reply();
        return reply;
    }

    return -1;
}

void CaskChrome::sync(const QString &key, const QVariant &value, const QVariant &value2)
{
    if (m_interface && m_interface->isValid())
    {
        m_interface->call(key, value, value2);
    }
}

void CaskChrome::setConnections()
{
    if(m_interface)
    {
        m_interface->disconnect();
        m_interface->deleteLater();
        m_interface = nullptr;
    }

    m_interface = new QDBusInterface ("org.cask.Server",
                                      "/Chrome",
                                      "org.cask.Chrome",
                                      QDBusConnection::sessionBus(), this);
    if (m_interface->isValid())
    {
        connect(m_interface, SIGNAL(shutdownRequested()), this, SLOT(onShutdown()));
        connect(m_interface, SIGNAL(logoutRequested()), this, SLOT(onLogout()));
        connect(m_interface, SIGNAL(sleepRequested()), this, SLOT(onSleep()));
        connect(m_interface, SIGNAL(restartRequested()), this, SLOT(onRestart()));
    }
}

void CaskChrome::onDropShadow(int radius, const QString &id)
{

}

void CaskChrome::onBlurBackground(int radius, const QString &id)
{

}
