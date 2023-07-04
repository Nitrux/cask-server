#pragma once

#include <QObject>
#include "caskserver_export.h"

class QDBusInterface;

class CASKSERVER_EXPORT CaskChrome : public QObject
{
    Q_OBJECT
public:
    explicit CaskChrome(QObject *parent = nullptr);

    Q_INVOKABLE void dropShadow(int radius, const QString &id = QString());
    Q_INVOKABLE void blurBackground(int radius, const QString &id = QString());
    void setAppId(const QString &id);

public Q_SLOTS:
    int blurFor(const QString &id);
    int shadowFor(const QString &id);

private:
    QDBusInterface *m_interface = nullptr;
    void sync(const QString &key, const QVariant &value, const QVariant &value2);
    void setConnections();

    QString m_appId;

private Q_SLOTS:
    void onDropShadow(int radius, const QString &id);
    void onBlurBackground(int radius, const QString &id);


Q_SIGNALS:
    void dropShadowChanged(int radius, const QString &id);
};

