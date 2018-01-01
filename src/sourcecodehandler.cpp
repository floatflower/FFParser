#include "sourcecodehandler.h"
#include "table.h"
#include "lookaheadtable.h"

#include <QDebug>
#include <iostream>

SourceCodeHandler::SourceCodeHandler(QObject *parent)
    : QObject(parent)
    , m_isAccept(false)
{

}

QVector<int> SourceCodeHandler::process(QStringList line)
{
    QVector<int> result;

    Table *table = Table::instance();
    LookAheadTable *lookAheadTable = table->lookAheadTable();

    m_parseStack.push(m_startPoint);

    while(!m_parseStack.isEmpty() && line.size() != 0) {
        if (table->isNonterminal(m_parseStack.top())) {
            QString top = m_parseStack.top();
            int ruleNumber = lookAheadTable->findRule(top, line.at(0));
            if (ruleNumber == -1) { break; }
            m_ruleApplyOrder.push_back(ruleNumber);
            qDebug() << "Apply rule number" << ruleNumber;
            Rule* applyRule = table->rule(ruleNumber);
            QVector<QString> derived = applyRule->derived();
            if (derived.size() > 0) {
                m_parseStack.pop();
                for (QVector<QString>::reverse_iterator rit_derived = derived.rbegin();
                     rit_derived != derived.rend();
                     rit_derived ++) {
                    m_parseStack.push_back(*rit_derived);
                }
                while( ((!m_parseStack.isEmpty())&&(line.size()!=0))
                        &&(m_parseStack.top() == line.at(0)) )
                {
                    qDebug() << "matched" << m_parseStack.top();
                    m_parseStack.pop();
                    line.pop_front();
                }
            }
            else {
                m_parseStack.pop();
            }
        }
        else {
            if (m_parseStack.top() == line.at(0)) {
                while( ((!m_parseStack.isEmpty())&&(line.size()!=0))
                       &&(m_parseStack.top() == line.at(0)) )
                {
                    qDebug() << "matched!" << m_parseStack.top();
                    m_parseStack.pop();
                    line.pop_front();
                }
            }
            else {
                break;
            }
        }
    }

    if (m_parseStack.isEmpty() && line.size() == 0) {
        qDebug() << "Accept\n";
        m_isAccept = true;
    }
    else {
        qDebug() << "Error\n";
        m_isAccept = false;
    }

    return result;
}

void SourceCodeHandler::showStackStatus()
{
    for (QStack<QString>::iterator it_parseStack = m_parseStack.begin();
         it_parseStack != m_parseStack.end();
         it_parseStack ++) {
        std::cout << (*it_parseStack).toStdString().c_str() << " ";
    }
    std::cout << std::endl;
}
