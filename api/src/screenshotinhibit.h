#pragma once

#include <QObject>
#include "caskserver_export.h"


class CaskScreenshot;
class CASKSERVER_EXPORT ScreenshotInhibit : public QObject
{
    Q_OBJECT
public:
    explicit ScreenshotInhibit(const QString &appId, QObject *parent = nullptr);

    ~ ScreenshotInhibit();

    void blacklist();
    void unblacklist();

private:
    CaskScreenshot *m_server;
    QString m_appId;

signals:

};
