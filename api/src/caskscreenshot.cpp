#include "caskscreenshot.h"
#include "serverutils.h"

#include <QDBusInterface>
#include <QCoreApplication>
#include <QDBusReply>
#include <QDebug>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>

#include "settingsstore.h"

CaskScreenshot::CaskScreenshot(QObject *parent) : QObject(parent)
  ,m_appId(qApp->organizationDomain()) //should be desktopFileName instead but needs to link to qguiapplication
  ,m_settings(new SettingsStore(this))
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

    loadSettings();
}

void CaskScreenshot::setAppId(const QString &id)
{
    m_appId = id;
}

QString CaskScreenshot::saveDir() const
{
    return m_saveDir;
}

void CaskScreenshot::grabAllScreens()
{
    sync("grabAllScreens", m_appId);
}

void CaskScreenshot::grabCurrentScreen()
{
    sync("grabCurrentScreen", m_appId);
}

void CaskScreenshot::grabCurrentWindow()
{
    sync("grabCurrentWindow", m_appId);
}

void CaskScreenshot::setScreenshotReady(const QString &url, const QString &id)
{
    if(m_interface && m_interface->isValid())
    {

    }
}

QStringList CaskScreenshot::blacklisted()
{
    return m_blacklisted;
}

void CaskScreenshot::blacklist(const QString &id)
{
    if (m_interface && m_interface->isValid())
    {
        m_interface->call("blacklist", id);
    }
}

void CaskScreenshot::unblacklist(const QString &id)
{
    if (m_interface && m_interface->isValid())
    {
        m_interface->call("unblacklist", id);
    }
}

void CaskScreenshot::setSaveDir(const QString &saveDir)
{
    if (m_saveDir == saveDir)
        return;

    m_settings->save("SaveDir", m_saveDir);
    sync("saveDir", m_saveDir);

    m_saveDir = saveDir;

    Q_EMIT saveDirChanged(m_saveDir);
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

void CaskScreenshot::onBlacklistedChanged(const QStringList &ids)
{
    qDebug() << "BLACKLISTED LIST CHANGED" << m_blacklisted << ids;
    if(m_blacklisted == ids)
        return;

    m_blacklisted = ids;
    m_settings->save("Blacklisted", m_blacklisted);

    Q_EMIT blacklistedChanged(m_blacklisted);
}

void CaskScreenshot::onSaveDirChanged(const QString &url)
{
    if (m_saveDir == url)
        return;

    m_saveDir = url;
    emit saveDirChanged(m_saveDir);
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
        connect(m_interface, SIGNAL(blacklistedChanged(QStringList)), this, SLOT(onBlacklistedChanged(QStringList)));
    }
}

void CaskScreenshot::loadSettings()
{
    m_settings->beginModule("Screenshot");

    if(m_interface && m_interface->isValid())
    {
        m_blacklisted = m_interface->property("blacklisted").toStringList();
        m_saveDir = m_interface->property("saveDir").toString();
        return;
    }

    m_saveDir = m_settings->load("SaveDir", m_saveDir).toString();
    m_blacklisted = m_settings->load("Blacklisted", m_blacklisted).toStringList();
}
