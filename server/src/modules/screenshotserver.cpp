#include "screenshotserver.h"
#include "screenshotadaptor.h"

#include <QDBusInterface>

ScreenshotServer::ScreenshotServer(QObject *parent) : QObject(parent)
{
    new ScreenshotAdaptor(this);
    if(!QDBusConnection::sessionBus().registerObject(QStringLiteral("/Screenshot"), this))
    {
        qDebug() << "FAILED TO REGISTER SCREENSHOT DBUS OBJECT";
        return;
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
