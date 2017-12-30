#ifndef TABLERECORD_H
#define TABLERECORD_H

#include <QObject>
#include <QVector>

#include "rule.h"

class TableRecord : public QObject
{
    Q_OBJECT
public:
    explicit TableRecord(QObject *parent = nullptr);
    void addRule(Rule* rule);
signals:

public slots:
private:
    QVector<Rule*> m_rules;
};

#endif // TABLERECORD_H
