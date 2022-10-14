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

public slots:
    int blurFor(const QString &id);
    int shadowFor(const QString &id);

private:
    QDBusInterface *m_interface = nullptr;
    void sync(const QString &key, const QVariant &value, const QVariant &value2);
    void setConnections();

    QString m_appId;

private slots:
    void onDropShadow(int radius, const QString &id);
    void onBlurBackground(int radius, const QString &id);


};

