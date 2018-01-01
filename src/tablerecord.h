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
    void findFollowSet();
    QVector<QString> followSet();
    void mergeFirstSet(QVector<QString> firstSet);
    void mergeFollowSet(QVector<QString> followSet);
    bool derivedLamda();
    void setKey(QString key) { m_key = key; }
    QString key() { return m_key; }
    void setHasFollowSet(bool set) { m_hasFollowSet = set; }
    bool hasFollowSet() { return m_hasFollowSet; }
signals:

public slots:
private:
    bool m_hasFirset;
    QVector<QString> m_firstSet;
    QString m_key;
    bool m_hasFollowSet;
    QVector<QString> m_followSet;
};

#endif // TABLERECORD_H
