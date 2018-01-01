#include "lookaheadtable.h"

LookAheadTable::LookAheadTable(QObject *parent) : QObject(parent)
{

}

void LookAheadTable::addRule(QString nonterminal, QString terminal, int ruleNumber)
{
    QHash<QString, QHash<QString,int>>::iterator it_terminalMap
            = m_lookAheadTable.find(nonterminal);

    if (it_terminalMap != m_lookAheadTable.end()) {
        (*it_terminalMap).insert(terminal, ruleNumber);
    }
    else {
        QHash<QString, int> newRow;
        newRow.insert(terminal, ruleNumber);
        m_lookAheadTable.insert(nonterminal, newRow);
    }
}
