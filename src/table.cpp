#include "table.h"

#include <QDebug>
#include <iostream>


Table* Table::m_instance = nullptr;

Table::Table()
{

}

void Table::addRule(QString key, Rule* rule)
{
    Table::iterator it_table = find(key);
    m_ruleMap.insert(rule->ruleNumber(), rule);
    if (it_table != end()) {
        // Exist
        (*it_table)->push_back(rule);
    }
    else {
        // Not exist
        TableRecord *r = new TableRecord;
        r->push_back(rule);
        r->setKey(key);
        insert(key, r);
    }
}

Rule *Table::rule(int ruleNumber)
{
    QHash<int, Rule*>::iterator it_rule = m_ruleMap.find(ruleNumber);
    if (it_rule != m_ruleMap.end()) {
        return *it_rule;
    }
    return nullptr;
}

void Table::findFirstSet()
{
    for (Table::iterator it_table = begin();
         it_table != end();
         it_table ++) {
        (*it_table)->findFirstSet();
        // qDebug() << "TableRecord" << it_table.key() << (*it_table)->firstSet();
    }
}

QVector<QString> Table::firstSet(QString key)
{
    Table::iterator it_table = find(key);
    return (*it_table)->firstSet();
}

void Table::findFollowSet()
{
    for (Table::iterator it_table = begin();
         it_table != end();
         it_table ++) {
        m_currentFindingFollow = it_table.key();
        (*it_table)->findFollowSet();
    }
}

QVector<QString> Table::followSet(QString key)
{
    Table::iterator it_table = find(key);
    return (*it_table)->followSet();
}

void Table::findPreictSet()
{
    for (Table::iterator it_table = begin();
         it_table != end();
         it_table ++) {

        for (TableRecord::iterator it_tableRecord = (*it_table)->begin();
             it_tableRecord != (*it_table)->end();
             it_tableRecord ++) {

            (*it_tableRecord)->findPredictSet();

        }

    }
}

bool Table::derivedLamda(QString key)
{
    Table::iterator it_table = find(key);
    return (*it_table)->derivedLamda();
}

Table* Table::instance()
{
    if (Table::m_instance == nullptr) {
        Table::m_instance = new Table;
    }
    return Table::m_instance;
}

void Table::printTable()
{
    for (Table::iterator it_table = begin();
         it_table != end();
         it_table ++) {

        for (TableRecord::iterator it_tableRecord = (*it_table)->begin();
             it_tableRecord != (*it_table)->end();
             it_tableRecord ++) {

            qDebug() << "Rule" << (*it_tableRecord)->ruleNumber() << ": \n"
                     << "Derived:" << (*it_tableRecord)->derived() << "\n"
                     << "First set: " << (*it_tableRecord)->firstSet() << "\n"
                     << "Derived lamda: " << (*it_tableRecord)->derivedLamda() << "\n"
                     << "Follow set: " << (*it_tableRecord)->followSet() << "\n"
                     << "Predict set: " << (*it_tableRecord)->predictSet() << "\n";

        }

    }
    for (Table::iterator it_table = begin();
             it_table != end();
             it_table ++) {

        for (TableRecord::iterator it_tableRecord = (*it_table)->begin();
             it_tableRecord != (*it_table)->end();
             it_tableRecord ++) {

            QVector<QString> m_derived = (*it_tableRecord)->derived();
            for (QVector<QString>::iterator it_derived = m_derived.begin();
                 it_derived != m_derived.end();
                 it_derived ++) {
                if (!isNonterminal(*it_derived) && (*it_derived) != "lamda") {
                    m_terminal.push_back(*it_derived);
                }
            }

        }

    }
    std::cout << "LL1 Table: "<< std::endl;
    for (Table::iterator it_table = begin();
             it_table != end();
             it_table ++) {
        for (TableRecord::iterator it_tableRecord = (*it_table)->begin();
             it_tableRecord != (*it_table)->end();
             it_tableRecord ++) {

            QVector<QString> predictSet = (*it_tableRecord)->predictSet();

            for (QVector<QString>::iterator it_terminal = m_terminal.begin();
                 it_terminal != m_terminal.end();
                 it_terminal ++) {
                if (predictSet.indexOf(*it_terminal) != -1) {
                    m_lookAheadTable.addRule((*it_table)->key(),
                                             *it_terminal,
                                             (*it_tableRecord)->ruleNumber());
                }
            }

        }

    }
    std::cout << "\t";
    for (QVector<QString>::iterator it_terminal = m_terminal.begin();
         it_terminal != m_terminal.end();
         it_terminal ++) {

        std::cout << (*it_terminal).toStdString().c_str() << "\t";

    }
    std::cout << std::endl;
    QHash<QString, QHash<QString, int>> lookAheadTable = m_lookAheadTable.table();
    for (QHash<QString, QHash<QString, int>>::iterator it_lookAheadTable = lookAheadTable.begin();
         it_lookAheadTable != lookAheadTable.end();
         it_lookAheadTable ++) {

        std::cout << it_lookAheadTable.key().toStdString().c_str() << "\t";
        for (QVector<QString>::iterator it_terminal = m_terminal.begin();
             it_terminal != m_terminal.end();
             it_terminal ++) {

            QHash<QString, int>::iterator it_row = (*it_lookAheadTable).find(*it_terminal);
            if (it_row != (*it_lookAheadTable).end()) {
                std::cout << *it_row << "\t";
            }
            else {
                std::cout << "\t";
            }

        }

        std::cout << std::endl;

    }
}

void Table::addTerminal(QString terminal)
{
    if (m_terminal.indexOf(terminal) == -1) {
        m_terminal.push_back(terminal);
    }
}
