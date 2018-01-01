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
    QVector<QString> followSet() { return m_followSet; }
    void findPredictSet();
    QVector<QString> predictSet();
    void mergeFirstSet(QVector<QString> &firstSet);
    void mergeFollowSet(QVector<QString> followSet);
signals:

public slots:
private:
    int m_ruleNumber;
    QVector<QString> m_derived;
    QVector<QString> m_firstSet;
    QVector<QString> m_followSet;
    QVector<QString> m_predictSet;
    bool m_derivedLamda;
    bool m_hasFirstSet;
};

#endif // RULE_H
