#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QHash>
#include <QString>

#include "tablerecord.h"
#include "rule.h"

class Table : public QObject
{
    Q_OBJECT
public:
    explicit Table(QObject *parent = nullptr);
    void addRule(QString key, Rule *rule);
signals:

public slots:
private:
    QHash<QString, TableRecord*> m_table;
};

#endif // TABLE_H
