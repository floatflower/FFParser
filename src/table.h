#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QHash>
#include <QString>

#include "tablerecord.h"
#include "rule.h"
#include "lookaheadtable.h"

class Table : public QHash<QString, TableRecord*>
{
public:
    explicit Table();
    void addRule(QString key, Rule* rule);
    Rule* rule(int ruleNumber);
    void findFirstSet();
    void findFollowSet();
    void findPreictSet();
    QVector<QString> firstSet(QString key);
    QVector<QString> followSet(QString key);
    static Table* instance();
    bool isNonterminal(QString key) { return (find(key) != end()); }
    bool derivedLamda(QString key);
    void printTable();
    void addTerminal(QString terminal);
    QString currentFindingFollow() { return m_currentFindingFollow; }
    LookAheadTable* lookAheadTable() { return &m_lookAheadTable; }
signals:

public slots:
private:
    static Table* m_instance;
    QVector<QString> m_terminal;
    QHash<int, Rule*> m_ruleMap;
    LookAheadTable m_lookAheadTable;
    QString m_currentFindingFollow;
};

#endif // TABLE_H
