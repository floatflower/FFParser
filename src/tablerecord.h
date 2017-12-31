#ifndef TABLERECORD_H
#define TABLERECORD_H

#include <QObject>
#include <QVector>

#include "rule.h"

class TableRecord : public QVector<Rule*>
{
public:
    explicit TableRecord();
    void findFirstSet();
    QVector<QString> firstSet();
    void mergeFirstSet(QVector<QString> firstSet);
    bool derivedLamda();
signals:

public slots:
private:
    bool m_hasFirset;
    QVector<QString> m_firstSet;
};

#endif // TABLERECORD_H
