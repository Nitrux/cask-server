#include "screenshotserver.h"
#include "screenshotadaptor.h"

#include <QDBusInterface>

#include <QDir>
#include <QStandardPaths>

#include "settingsstore.h"

ScreenshotServer::ScreenshotServer(QObject *parent) : QObject(parent)
{
    new ScreenshotAdaptor(this);
    if(!QDBusConnection::sessionBus().registerObject(QStringLiteral("/Screenshot"), this))
    {
        qDebug() << "FAILED TO REGISTER SCREENSHOT DBUS OBJECT";
        return;
    }

    m_saveDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/Screenshots";

    SettingsStore settings;
    settings.beginModule("Screenshot");
    m_saveDir = settings.load("SaveDir", m_saveDir).toString();
    m_blacklisted = settings.load("Blacklisted", m_blacklisted).toStringList();
    settings.endModule();

    //Make sure to create the saveDir
    QDir dir(m_saveDir);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
}

void ScreenshotServer::grabAllScreens(const QString &id)
{
    Q_EMIT grabAllScreensRequested(id);
}

void ScreenshotServer::grabCurrentScreen(const QString &id)
{
    Q_EMIT grabCurrentScreenRequested(id);
}

void ScreenshotServer::grabCurrentWindow(const QString &id)
{
    Q_EMIT grabCurrentWindowRequested(id);
}

void ScreenshotServer::blacklist(const QString &id)
{
    if(!m_blacklisted.contains(id))
    {
        m_blacklisted << id;

        Q_EMIT blacklistedChanged(m_blacklisted);
    }
}

void ScreenshotServer::unblacklist(const QString &id)
{
    if(m_blacklisted.contains(id))
    {
        m_blacklisted.removeAll(id);
        Q_EMIT blacklistedChanged(m_blacklisted);
    }
}

QStringList ScreenshotServer::blacklisted()
{
    qDebug() << "ASK TO PRINT VALUES" << m_blacklisted;
    return m_blacklisted;
}

QString ScreenshotServer::saveDir() const
{
    return m_saveDir;
}

void ScreenshotServer::setSaveDir(QString saveDir)
{
    if (m_saveDir == saveDir)
        return;

    m_saveDir = saveDir;
    emit saveDirChanged(m_saveDir);
}
