#include "rule.h"
#include "table.h"

#include <QDebug>

Rule::Rule(QObject *parent)
    : QObject(parent)
    , m_derivedLamda(true)
    , m_hasFirstSet(false)
{

}

void Rule::findFirstSet()
{
    if (m_hasFirstSet) return;
    m_hasFirstSet = true;
    Table *table = Table::instance();
    for (QVector<QString>::iterator it_derived = m_derived.begin();
         it_derived != m_derived.end();
         it_derived ++) {
        if (table->isNonterminal(*it_derived)) {

            QVector<QString> firstSet = table->firstSet(*it_derived);
            mergeFirstSet(firstSet);
            m_derivedLamda &= table->derivedLamda(*it_derived);
        }
        else {
            if (*it_derived != "lamda") {
                m_firstSet.push_back(*it_derived);
                m_derivedLamda = false;
            }
            else {
                m_derivedLamda = true;
            }
            break;
        }
        if (table->derivedLamda(*it_derived)) {

            continue;
        }
        else {
            break;
        }
    }
}

QVector<QString> Rule::firstSet()
{
    findFirstSet();
    return m_firstSet;
}

void Rule::findPredictSet()
{
    for (QVector<QString>::iterator it_firstSet = m_firstSet.begin();
         it_firstSet != m_firstSet.end();
         it_firstSet ++) {
        m_predictSet.push_back(*it_firstSet);
    }
    if (m_derivedLamda) {
        for (QVector<QString>::iterator it_followSet = m_followSet.begin();
             it_followSet != m_followSet.end();
             it_followSet ++) {
            m_predictSet.push_back(*it_followSet);
        }
    }
}

QVector<QString> Rule::predictSet()
{
    return m_predictSet;
}

void Rule::mergeFirstSet(QVector<QString>& firstSet)
{
    for (QVector<QString>::iterator it_firstSet = firstSet.begin();
         it_firstSet != firstSet.end();
         it_firstSet ++) {
        if (m_firstSet.indexOf(*it_firstSet) == -1) {
            m_firstSet.push_back(*it_firstSet);
        }
    }
}

void Rule::mergeFollowSet(QVector<QString> followSet)
{
    for (QVector<QString>::iterator it_followSet = followSet.begin();
         it_followSet != followSet.end();
         it_followSet ++) {
        if (m_followSet.indexOf(*it_followSet) == -1 && (*it_followSet) != "lamda") {
            m_followSet.push_back(*it_followSet);
        }
    }
}
