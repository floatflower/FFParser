#include "tablerecord.h"
#include <QDebug>

TableRecord::TableRecord()
    : m_hasFirset(false)
{

}

void TableRecord::findFirstSet()
{
    int tableSize = size();
    for (int i = 0; i < tableSize; i ++) {
        mergeFirstSet(at(i)->firstSet());
    }
}

QVector<QString> TableRecord::firstSet()
{
    if (!m_hasFirset) findFirstSet();
    m_hasFirset = true;
    return m_firstSet;
}

void TableRecord::mergeFirstSet(QVector<QString> firstSet)
{
    for (QVector<QString>::iterator it_firstSet = firstSet.begin();
         it_firstSet != firstSet.end();
         it_firstSet ++) {
        if (m_firstSet.indexOf(*it_firstSet) == -1) {
            m_firstSet.push_back(*it_firstSet);
        }
    }
    m_hasFirset = true;
}

bool TableRecord::derivedLamda()
{
    bool result = false;
    int tableSize = size();
    for (int i = 0; i < tableSize; i ++) {
        result |= at(i)->derivedLamda();
    }
    return result;
}
