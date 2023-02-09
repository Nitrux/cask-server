#pragma once
#include <QObject>
#include <QMap>

class ScreenshotServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList blacklisted READ blacklisted NOTIFY blacklistedChanged)
    Q_PROPERTY(QString saveDir READ saveDir WRITE setSaveDir NOTIFY saveDirChanged)

public:
    explicit ScreenshotServer(QObject *parent = nullptr);

    void grabAllScreens(const QString &id);
    void grabCurrentScreen(const QString &id);
    void grabCurrentWindow(const QString &id);
    void blacklist(const QString &id);
    void unblacklist(const QString &id);

    QStringList blacklisted();

    QString saveDir() const;
    void setSaveDir(QString saveDir);

private:
    QStringList m_blacklisted;

    QString m_saveDir;

Q_SIGNALS:
    void screenshotReady(const QString &path, const QString &id);

    void grabAllScreensRequested(const QString &id);
    void grabCurrentScreenRequested(const QString &id);
    void grabCurrentWindowRequested(const QString &id);
    void blacklistedChanged(QStringList blacklisted);
    void saveDirChanged(QString saveDir);
};

