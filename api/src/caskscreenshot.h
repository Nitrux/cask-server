#pragma once
#include <QObject>
#include "caskserver_export.h"
#include <QVariant>

class QDBusInterface;
class CASKSERVER_EXPORT CaskScreenshot : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        AllScreens,
        CurrentScreen,
        CurrentWindow,
        CustomArea

    }; Q_ENUM(Type)

    explicit CaskScreenshot(QObject *parent = nullptr);

public slots:
    void grabAllScreens();
    void grabCurrentScreen();
    void grabCurrentWindow();

    void setScreenshotReady(const QString &url, const QString &id);

private slots:
    void onGrabAllScreensRequested(const QString &id);
    void onGrabCurrentScreenRequested(const QString &id);
    void onGrabCurrentWindowRequested(const QString &id);

private:
    QDBusInterface *m_interface = nullptr;
    void sync(const QString &key, const QVariant &value =  QVariant());
    void setConnections();

signals:
    void takeScreenshot(Type type, QString id);
};

