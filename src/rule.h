#ifndef RULE_H
#define RULE_H

#include <QObject>
#include <QString>
#include <QVector>

class Rule : public QObject
{
    Q_OBJECT
public:
    explicit Rule(QObject *parent = nullptr);
    void setRuleNumber(int number) { m_ruleNumber = number; }
    int ruleNumber() { return m_ruleNumber; }
    void addDerived(QString derived) { m_derived.push_back(derived); }
    QVector<QString> derived() { return m_derived; }
    bool derivedLamda() { return m_derivedLamda; }
    void findFirstSet();
    QVector<QString> firstSet();
    void findFollowSet();
    QVector<QString> followSet();
    QVector<QString> predictSet();
    void mergeFirstSet(QVector<QString> &firstSet);
signals:

public slots:
private:
    int m_ruleNumber;
    QVector<QString> m_derived;
    QVector<QString> m_firstSet;
    QVector<QString> m_followSet();
    bool m_derivedLamda;
    bool m_hasFirstSet;
};

#endif // RULE_H
