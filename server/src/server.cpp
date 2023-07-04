#include "server.h"
#include <QDBusConnectionInterface>
#include <QDebug>

#include "modules/powerserver.h"
#include "modules/screenshotserver.h"
#include "modules/chromeserver.h"

#define CASK_SERVER_ORG "org.cask.Server"


#include <signal.h>

void sigtermHandler(int signalNumber)
{
    qDebug() << "terminating CaskServer session" << signalNumber;
    if (QCoreApplication::instance())
    {
        QCoreApplication::instance()->exit(-1);
        qDebug() << "terminating CaskServer session FINISHED" << signalNumber;
    }
}

void sigHandler(int signalNumber)
{
    qDebug() << "terminating CaskServer session" << signalNumber;
}

Server::Server(int &argc, char **argv) : QCoreApplication(argc, argv)
{

}

Server::~Server()
{
    qDeleteAll(m_modules);
}

bool Server::init()
{
    QDBusConnectionInterface *iface = QDBusConnection::sessionBus().interface();

    if(iface->isServiceRegistered(QStringLiteral(CASK_SERVER_ORG)))
    {
        qWarning() << "Cask Server is already registered";
        return false;
    }

    auto registration = iface->registerService(QStringLiteral(CASK_SERVER_ORG),
                                               QDBusConnectionInterface::ReplaceExistingService,
                                               QDBusConnectionInterface::DontAllowReplacement);

    if (!registration.isValid())
    {
        qWarning("2 Failed to register D-Bus service \"%s\" on session bus: \"%s\"",
                 qPrintable(QStringLiteral(CASK_SERVER_ORG)),
                 qPrintable(registration.error().message()));

        return false;
    }

    signal(SIGTERM, sigtermHandler);
    signal(SIGINT, sigHandler);

    m_modules << new PowerServer(this);
    m_modules << new ScreenshotServer(this);
    m_modules << new ChromeServer(this);

    return true;
}
