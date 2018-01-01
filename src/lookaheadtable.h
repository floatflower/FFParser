#ifndef LOOKAHEADTABLE_H
#define LOOKAHEADTABLE_H

#include <QObject>
#include <QHash>

class LookAheadTable : public QObject
{
    Q_OBJECT
public:
    explicit LookAheadTable(QObject *parent = nullptr);
    void addRule(QString nonterminal, QString terminal, int ruleNumber);
    QHash<QString, QHash<QString, int>> table() { return m_lookAheadTable; }
    int findRule(QString source, QString target);
signals:

public slots:
private:
    QHash<QString, QHash<QString, int>> m_lookAheadTable;
};

#endif // LOOKAHEADTABLE_H
