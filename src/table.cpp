#include "table.h"

Table::Table(QObject *parent) : QObject(parent)
{

}

void Table::addRule(QString key, Rule *rule)
{
    QHash<QString, TableRecord*>::iterator it_record = m_table.find(key);
    if (it_record != m_table.end()) {
        // Record exist
        (*it_record)->addRule(rule);
    }
    else {
        TableRecord *record = new TableRecord;
        record->addRule(rule);
        m_table.insert(key, record);
    }
}
