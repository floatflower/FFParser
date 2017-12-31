#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QHash>
#include <QString>

#include "tablerecord.h"
#include "rule.h"

class Table : public QHash<QString, TableRecord*>
{
public:
    explicit Table();
    void addRule(QString key, Rule* rule);
    void findFirstSet();
    QVector<QString> firstSet(QString key);
    static Table* instance();
    bool isNonterminal(QString key) { return (find(key) != end()); }
    bool derivedLamda(QString key);
signals:

public slots:
private:
    static Table* m_instance;
};

#endif // TABLE_H
