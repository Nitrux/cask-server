#pragma once
#include <QObject>
#include <QHash>

class ChromeServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList blurredList READ blurredList NOTIFY blurredListChanged)
    Q_PROPERTY(QStringList shadowsList READ shadowsList NOTIFY shadowListChanged)
public:
    ChromeServer(QObject *parent = nullptr);

    void blurBackground(int radius , const QString &id);
    void dropShadow(int radius , const QString &id);

    QStringList shadowsList();
    QStringList blurredList();

    /**
     * @brief blurFor
     * Get the blur value for a given ID, if not matches are found -1 is returned
     * @param id
     * ID of the app
     * @return
     * A value found or -1 if not found
     */
    int blurFor(const QString &id);
    int shadowFor(const QString &id);

private:
    QHash<QString, int> m_blurredList;
    QHash<QString, int> m_shadowsList;

Q_SIGNALS:
    void blurBackgroundFor(int, QString);
    void dropShadowFor(int, QString);

    void shadowListChanged();
    void blurredListChanged();
};

