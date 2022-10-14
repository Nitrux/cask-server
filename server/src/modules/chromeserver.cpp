#include "chromeserver.h"

#include "chromeadaptor.h"

#include <QDBusInterface>

ChromeServer::ChromeServer(QObject *parent) : QObject(parent)
{
    new ChromeAdaptor(this);
    if(!QDBusConnection::sessionBus().registerObject(QStringLiteral("/Chrome"), this))
    {
        qDebug() << "FAILED TO REGISTER POWER DBUS OBJECT";
        return;
    }
}

void ChromeServer::blurBackground(int radius, const QString &id)
{
    if(!m_blurredList.contains(id))
    {
        m_blurredList.insert(id, radius);
    }else
    {
        m_blurredList[id] = radius;
    }
    Q_EMIT blurBackgroundFor(radius, id);

}

void ChromeServer::dropShadow(int radius, const QString &id)
{
    qDebug() << "REQUEST TO ADD DROP SHADOW FOR" << radius << id;

    if(!m_shadowsList.contains(id))
    {
        m_shadowsList.insert(id, radius);
    }else
    {
        m_shadowsList[id] = radius;
    }
    qDebug() << "REQUEST TO ADD DROP SHADOW FOR" << m_shadowsList;

    Q_EMIT dropShadowFor(radius, id);
}

QStringList ChromeServer::shadowsList()
{
  QStringList res;

  for(const auto &key : m_shadowsList.keys())
  {
      res << QString("%1:%2").arg(key, QString::number(m_shadowsList.value(key)));
  }

  return res;
}

QStringList ChromeServer::blurredList()
{
    QStringList res;

    for(const auto &key : m_blurredList.keys())
    {
        res << QString("%1:%2").arg(key, QString::number(m_blurredList.value(key)));
    }

    return res;
}

int ChromeServer::blurFor(const QString &id)
{
    if(m_blurredList.contains(id))
    {
        return m_blurredList.value(id);
    }

    return -1;
}

int ChromeServer::shadowFor(const QString &id)
{
    if(m_shadowsList.contains(id))
    {
        return m_shadowsList.value(id);
    }

    return -1;
}
