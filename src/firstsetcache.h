#ifndef FIRSTSETCACHE_H
#define FIRSTSETCACHE_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QVector>

class FirstSetCache : public QObject
{
    Q_OBJECT
public:
    explicit FirstSetCache(QObject *parent = nullptr);
    bool hasCache(QString searchElement);
    QVector<QString> cache(QString searchElement);
    static FirstSetCache* instance();
    static FirstSetCache* m_instance;
signals:

public slots:
private:
    QHash<QString, QVector<QString>> m_firstSet;
};

#endif // FIRSTSETCACHE_H
