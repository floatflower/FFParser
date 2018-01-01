#include "tablerecord.h"
#include <QDebug>
#include "table.h"

TableRecord::TableRecord()
    : m_hasFirset(false)
    , m_hasFollowSet(false)
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

void TableRecord::findFollowSet()
{
    //qDebug() << "Find Follow" << key();

    Table *table = Table::instance();
    //qDebug() << "Current finding is:" << table->currentFindingFollow();
    for (TableRecord::iterator it_tableRecord = begin();
         it_tableRecord != end();
         it_tableRecord ++) {
        // iterate all rule.

        /**
         * Iterator whole table to find who derive the "key()"
         */

        for (Table::iterator it_searchTable = table->begin();
             it_searchTable != table->end();
             it_searchTable ++) {
            //qDebug() << "Searching Record..." << it_searchTable.key();
            for (TableRecord::iterator it_searchTableRecord = (*it_searchTable)->begin();
                 it_searchTableRecord != (*it_searchTable)->end();
                 it_searchTableRecord ++) {
                //qDebug() << "Searching Rule..." << (*it_searchTableRecord)->ruleNumber();
                QVector<QString> derived = (*it_searchTableRecord)->derived();
                int derivedSize = derived.size();
                int derivedIndex = derived.indexOf(key());
                bool tmp_derivedLamda = false;

                if (derivedIndex != -1) {
                    for (int i = derivedIndex + 1; i < derivedSize; i ++) {
                        //qDebug() << "Find first " << derived.at(i);
                        if (table->isNonterminal(derived.at(i))) {
                            QVector<QString> tmp_firstSet = table->firstSet(derived.at(i));

                            (*it_tableRecord)->mergeFollowSet(tmp_firstSet);

                            tmp_derivedLamda = table->derivedLamda(derived.at(i));

                        }
                        else {
                            QVector<QString> terminal;
                            terminal.push_back(derived.at(i));
                            (*it_tableRecord)->mergeFollowSet(terminal);
                            tmp_derivedLamda = false;
                        }
                        if (!tmp_derivedLamda) break;

                    }
                    if (derivedIndex + 1 == derivedSize) {
                        //qDebug() << "is last element";
                        tmp_derivedLamda = true;
                    }
                    if (tmp_derivedLamda
                            && table->currentFindingFollow() != (*it_searchTable)->key()) {
                        //qDebug() << "get follow set" << (*it_searchTable)->key();
                        (*it_tableRecord)->mergeFollowSet(table->followSet((*it_searchTable)->key()));
                    }
                }


            }

        }

    }
}

QVector<QString> TableRecord::followSet()
{
    if (!m_hasFollowSet) {
        findFollowSet();
        for (TableRecord::iterator it_tableRecord = begin();
             it_tableRecord != end();
             it_tableRecord ++) {
                mergeFollowSet((*it_tableRecord)->followSet());
        }
    }
    return m_followSet;
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

void TableRecord::mergeFollowSet(QVector<QString> followSet)
{
    for (QVector<QString>::iterator it_followSet = followSet.begin();
         it_followSet != followSet.end();
         it_followSet ++) {
        if (m_followSet.indexOf(*it_followSet) == -1) {
            m_followSet.push_back(*it_followSet);
        }
    }
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
