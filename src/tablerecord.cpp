#include "tablerecord.h"
#include <QDebug>

TableRecord::TableRecord(QObject *parent) : QObject(parent)
{

}

void TableRecord::addRule(Rule *rule)
{
    qDebug() << "Add new rule: rule" << rule->ruleNumber() << ": " << rule->derived();
    m_rules.push_back(rule);
}
