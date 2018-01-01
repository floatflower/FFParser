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

int LookAheadTable::findRule(QString source, QString target)
{
    QHash<QString, QHash<QString,int>>::iterator it_terminalMap
            = m_lookAheadTable.find(source);

    QHash<QString, int>::iterator it_row = (*it_terminalMap).find(target);
    if (it_row != (*it_terminalMap).end()) {
        return *it_row;
    }
    else return -1;
}
