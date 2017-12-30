#include "firstsetcache.h"

FirstSetCache* FirstSetCache::m_instance = nullptr;

FirstSetCache::FirstSetCache(QObject *parent) : QObject(parent)
{

}

bool FirstSetCache::hasCache(QString searchElement)
{
    return m_firstSet.find(searchElement) != m_firstSet.end();
}

QVector<QString> FirstSetCache::cache(QString searchElement)
{
    return *(m_firstSet.find(searchElement));
}

FirstSetCache* FirstSetCache::instance()
{
    if (FirstSetCache::m_instance == nullptr) {
        FirstSetCache::m_instance = new FirstSetCache();
    }
    return FirstSetCache::m_instance;
}
