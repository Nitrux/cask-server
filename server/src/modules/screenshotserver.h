#pragma once
#include <QObject>

class ScreenshotServer : public QObject
{
    Q_OBJECT
public:
    explicit ScreenshotServer(QObject *parent = nullptr);

    void grabAllScreens(const QString &id);
    void grabCurrentScreen(const QString &id);
    void grabCurrentWindow(const QString &id);

Q_SIGNALS:
    void screenshotReady(const QString &path, const QString &id);

    void grabAllScreensRequested(const QString &id);
    void grabCurrentScreenRequested(const QString &id);
    void grabCurrentWindowRequested(const QString &id);
};

