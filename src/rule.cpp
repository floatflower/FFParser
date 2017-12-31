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
    //qDebug() << "Rule" << m_ruleNumber
    //         << ", First set: " << m_firstSet
    //         << ", derived lamda: " << m_derivedLamda;
}

QVector<QString> Rule::firstSet()
{
    if (!m_hasFirstSet) findFirstSet();
    return m_firstSet;
}

void Rule::findFollowSet()
{

}

QVector<QString> Rule::predictSet()
{

}

void Rule::mergeFirstSet(QVector<QString>& firstSet)
{
    for (QVector<QString>::iterator it_firstSet = firstSet.begin();
         it_firstSet != firstSet.end();
         it_firstSet ++) {
        if (m_firstSet.indexOf(*it_firstSet) == -1) {
            m_firstSet.append(*it_firstSet);
        }
    }
}
