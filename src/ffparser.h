#ifndef FFPARSER_H
#define FFPARSER_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include "rule.h"
#include "table.h"

class FFParser : public QObject
{
    Q_OBJECT
public:
    explicit FFParser(QObject *parent = nullptr);
    void run();
    void buildTable();
    void readSourceCodeLine();
signals:

public slots:
private:
    QStringList m_arguments;
    QString m_outputFilename;
    QFile m_cfgFile;
    QFile m_sourceCodeFile;
    QVector<QStringList> m_sourceCodeLine;
    QString m_startPoint;
};

#endif // FFPARSER_H
