#ifndef SOURCECODEHANDLER_H
#define SOURCECODEHANDLER_H

#include <QObject>
#include <QVector>
#include <QStack>

class SourceCodeHandler : public QObject
{
    Q_OBJECT
public:
    explicit SourceCodeHandler(QObject *parent = nullptr);
    QVector<int> process(QStringList line);
    void setStartPoint(QString startPoint) { m_startPoint = startPoint; }
    void showStackStatus();
    QVector<int> ruleApplyOrder() { return m_ruleApplyOrder; }
    bool isAccept() { return m_isAccept; }
signals:

public slots:
private:
    QStack<QString> m_parseStack;
    QString m_startPoint;
    QVector<int> m_ruleApplyOrder;
    bool m_isAccept;
};

#endif // SOURCECODEHANDLER_H
