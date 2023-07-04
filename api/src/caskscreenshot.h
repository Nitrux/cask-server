#pragma once

#include <QObject>
#include <QVariant>

#include "caskserver_export.h"

class QDBusInterface;
class SettingsStore;
class CASKSERVER_EXPORT CaskScreenshot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList blacklisted READ blacklisted NOTIFY blacklistedChanged)
    Q_PROPERTY(QString saveDir READ saveDir WRITE setSaveDir NOTIFY saveDirChanged)

public:
    enum Type
    {
        AllScreens,
        CurrentScreen,
        CurrentWindow,
        CustomArea

    }; Q_ENUM(Type)

    explicit CaskScreenshot(QObject *parent = nullptr);
    void setAppId(const QString &id);

    QString saveDir() const;

public Q_SLOTS:
    void grabAllScreens();
    void grabCurrentScreen();
    void grabCurrentWindow();

    void setScreenshotReady(const QString &url, const QString &id);

    QStringList blacklisted();
    void blacklist(const QString &id);
    void unblacklist(const QString &id);

    void setSaveDir(const QString &saveDir);

private Q_SLOTS:
    void onGrabAllScreensRequested(const QString &id);
    void onGrabCurrentScreenRequested(const QString &id);
    void onGrabCurrentWindowRequested(const QString &id);
    void onBlacklistedChanged(const QStringList &ids);
    void onSaveDirChanged(const QString &url);

private:
    QDBusInterface *m_interface = nullptr;
    SettingsStore *m_settings;

    void sync(const QString &key, const QVariant &value =  QVariant());
    void setConnections();
    void loadSettings();

    QStringList m_blacklisted;
    QString m_appId;

    QString m_saveDir;

Q_SIGNALS:
    void takeScreenshot(Type type, QString id);
    void blacklistedChanged(QStringList blacklisted);
    void saveDirChanged(QString saveDir);
};

