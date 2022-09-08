#include "caskscreenshot.h"
#include "serverutils.h"

#include <QDBusInterface>
#include <QCoreApplication>

#include <QDebug>

static QString appId()
{
    return QString::number(qApp->applicationPid());
}

CaskScreenshot::CaskScreenshot(QObject *parent) : QObject(parent)
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

void CaskScreenshot::grabAllScreens()
{
    sync("grabAllScreens", appId());
}

void CaskScreenshot::grabCurrentScreen()
{
    sync("grabCurrentScreen", appId());
}

void CaskScreenshot::grabCurrentWindow()
{
    sync("grabCurrentWindow", appId());
}

void CaskScreenshot::setScreenshotReady(const QString &url, const QString &id)
{
    if(m_interface && m_interface->isValid())
    {

    }
}

void CaskScreenshot::onGrabAllScreensRequested(const QString &id)
{
    Q_EMIT this->takeScreenshot(Type::AllScreens, id);
}

void CaskScreenshot::onGrabCurrentScreenRequested(const QString &id)
{
    qDebug() << "REQUESTING TO GRAB CURRENT SCREEN" << id;
    Q_EMIT this->takeScreenshot(Type::CurrentScreen, id);
}

void CaskScreenshot::onGrabCurrentWindowRequested(const QString &id)
{
    Q_EMIT this->takeScreenshot(Type::CurrentWindow, id);
}

void CaskScreenshot::sync(const QString &key, const QVariant &value)
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

void CaskScreenshot::setConnections()
{
    if(m_interface)
    {
        m_interface->disconnect();
        m_interface->deleteLater();
        m_interface = nullptr;
    }

    m_interface = new QDBusInterface ("org.cask.Server",
                                      "/Screenshot",
                                      "org.cask.Screenshot",
                                      QDBusConnection::sessionBus(), this);
    if (m_interface->isValid())
    {
        connect(m_interface, SIGNAL(grabAllScreensRequested(QString)), this, SLOT(onGrabAllScreensRequested(QString)));
        connect(m_interface, SIGNAL(grabCurrentScreenRequested(QString)), this, SLOT(onGrabCurrentScreenRequested(QString)));
        connect(m_interface, SIGNAL(grabCurrentWindowRequested(QString)), this, SLOT(onGrabCurrentWindowRequested(QString)));
    }
}
