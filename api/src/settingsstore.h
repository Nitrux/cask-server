#pragma once
#include <QObject>
#include <QString>
#include <QVariant>
#include "caskserver_export.h"

class QSettings;

/**
 * @brief The SettingsStore class
 * Allows to store and read settings from MauiMan.
 */

class CASKSERVER_EXPORT SettingsStore : public QObject
{
    Q_OBJECT
public:
    explicit SettingsStore(QObject *parent = nullptr);
    ~SettingsStore();

    QVariant load(const QString &key, const QVariant &defaultValue);

    void save(const QString &key, const QVariant &value);

    void beginModule(const QString &module);
    void endModule();

private:
    QSettings *m_settings;
};


