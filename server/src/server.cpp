#include "server.h"
#include <QDBusConnectionInterface>
#include <QDebug>

#include "modules/powerserver.h"

#define CASK_SERVER_ORG "org.cask.Server"

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

    if(iface->isServiceRegistered(CASK_SERVER_ORG))
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
                 qPrintable(CASK_SERVER_ORG),
                 qPrintable(registration.error().message()));

        return false;
    }

    m_modules << new PowerServer(this);
    return true;
}
