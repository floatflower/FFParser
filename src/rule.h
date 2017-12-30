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
signals:

public slots:
private:
    int m_ruleNumber;
    QVector<QString> m_derived;
};

#endif // RULE_H
