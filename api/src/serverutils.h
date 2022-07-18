#pragma once

#include <QObject>

class ServerUtils : public QObject
{
    Q_OBJECT
public:
    explicit ServerUtils(QObject *parent = nullptr);

    bool serverRunning() const;

    static void startServer();

signals:
    void serverRunningChanged(bool state);

private:
    bool m_serverRunning = false;
};

