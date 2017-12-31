#include "table.h"
#include <QDebug>

Table* Table::m_instance = nullptr;

Table::Table()
{

}

void Table::addRule(QString key, Rule* rule)
{
    Table::iterator it_table = find(key);
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
        if ((*it_table)->derivedLamda()) {
            (*it_table)->findFollowSet();
        }
    }
}

QVector<QString> Table::followSet(QString key)
{
    Table::iterator it_table = find(key);
    return (*it_table)->followSet();
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
                     << "First set: " << (*it_tableRecord)->firstSet() << "\n"
                     << "Derived lamda: " << (*it_tableRecord)->derivedLamda() << "\n"
                     << "Follow set: " << (*it_tableRecord)->followSet() << "\n";

        }

    }
}
