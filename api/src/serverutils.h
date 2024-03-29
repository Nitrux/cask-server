#pragma once

#include <QObject>
#include "caskserver_export.h"

class CASKSERVER_EXPORT ServerUtils : public QObject
{
    Q_OBJECT
public:
    explicit ServerUtils(QObject *parent = nullptr);

    bool serverRunning() const;

    static void startServer();

private:
    bool m_serverRunning = false;

Q_SIGNALS:
    void serverRunningChanged(bool state);
};

