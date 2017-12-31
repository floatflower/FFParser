#include "table.h"
#include <QDebug>

Table* Table::m_instance = nullptr;

Table::Table()
{

}

void Table::addRule(QString key, Rule* rule)
{
    qDebug() << "Add rule" << rule->ruleNumber() << ", left-hand side:" << key;
    Table::iterator it_table = find(key);
    if (it_table != end()) {
        // Exist
        (*it_table)->push_back(rule);
    }
    else {
        // Not exist
        TableRecord *r = new TableRecord;
        r->push_back(rule);
        insert(key, r);
    }
}

void Table::findFirstSet()
{
    qDebug() << "Table find first set";
    for (Table::iterator it_table = begin();
         it_table != end();
         it_table ++) {
        (*it_table)->findFirstSet();
        qDebug() << "TableRecord" << it_table.key() << (*it_table)->firstSet();
    }
}

QVector<QString> Table::firstSet(QString key)
{
    Table::iterator it_table = find(key);
    return (*it_table)->firstSet();
}

bool Table::derivedLamda(QString key)
{
    Table::iterator it_table = find(key);
    qDebug() << key << "derived lamda? " << (*it_table)->derivedLamda();
    return (*it_table)->derivedLamda();
}

Table* Table::instance()
{
    if (Table::m_instance == nullptr) {
        Table::m_instance = new Table;
    }
    return Table::m_instance;
}
