#include "ffparser.h"

#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QRegExp>

#include "rule.h"
#include "tablerecord.h"
#include "table.h"


FFParser::FFParser(QObject *parent) : QObject(parent)
{
    QCoreApplication *app = QCoreApplication::instance();
    m_arguments = app->arguments();
    for (QStringList::iterator it_arguments = m_arguments.begin();
         it_arguments != m_arguments.end();
         it_arguments ++) {
        if ((*it_arguments) == "-o" || (*it_arguments) == "--output") {
            m_outputFilename = *(it_arguments + 1);
        }
        else if ((*it_arguments) == "-s" || (*it_arguments) == "--source") {
            m_sourceCodeFile.setFileName(*(it_arguments + 1));
        }
        else if ((*it_arguments) == "-c" || (*it_arguments) == "--cfg") {
            m_cfgFile.setFileName(*(it_arguments + 1));
        }
    }
}

void FFParser::run()
{
    if (!m_sourceCodeFile.exists()) {
        qFatal("Source code file is required");
    }
    if (!m_cfgFile.exists()) {
        qFatal("CFG file is required.");
    }
    buildTable();
    Table *table = Table::instance();
    table->findFirstSet();
    table->findFollowSet();
    table->findPreictSet();
    table->printTable();
}

void FFParser::buildTable()
{
    if (!m_cfgFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("CFG file cannot be opened.");
    }
    QString currentToken;
    while (!m_cfgFile.atEnd()) {
        QString line(m_cfgFile.readLine());
        line = line.trimmed();
        QStringList tokens = line.split(QRegExp("[ \t\r\n\f]"));
        Rule *r = new Rule();
        r->setRuleNumber(tokens.at(0).toInt());
        if (tokens.at(1) != QString("|")) {
            currentToken = tokens.at(1);
            for (int i =3; i < tokens.size(); i ++) {
                r->addDerived(tokens.at(i));
            }
        }
        else {
            for (int i =2; i < tokens.size(); i ++) {
                r->addDerived(tokens.at(i));
            }
        }
        Table *table = Table::instance();
        table->addRule(currentToken, r);
    }
}
