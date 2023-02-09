#include "screenshotinhibit.h"
#include "caskscreenshot.h"

ScreenshotInhibit::ScreenshotInhibit(const QString &appId, QObject *parent) : QObject(parent)
  ,m_appId(appId)
  ,m_server(new CaskScreenshot)
{
}

ScreenshotInhibit::~ScreenshotInhibit()
{
//    unblacklist();
}

void ScreenshotInhibit::blacklist()
{
    m_server->blacklist(m_appId);
}

void ScreenshotInhibit::unblacklist()
{
    m_server->unblacklist(m_appId);
}
