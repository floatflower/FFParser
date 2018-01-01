#include "ffparser.h"

#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QRegExp>

#include "rule.h"
#include "tablerecord.h"
#include "table.h"
#include "sourcecodehandler.h"

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
    readSourceCodeLine();

    for (QVector<QStringList>::iterator it_line = m_sourceCodeLine.begin();
         it_line != m_sourceCodeLine.end();
         it_line ++) {

        SourceCodeHandler handler;
        handler.setStartPoint(m_startPoint);
        handler.process(*it_line);
        QVector<int> result = handler.ruleApplyOrder();

        for (QStringList::iterator it_rawLine = (*it_line).begin();
             it_rawLine != (*it_line).end();
             it_rawLine ++) {
            std::cout << (*it_rawLine).toStdString().c_str() << " ";
        }

        for (QVector<int>::iterator it_result = result.begin();
             it_result != result.end();
             it_result ++) {
            std::cout << (*it_result) << " ";
        }

        handler.isAccept() ? std::cout << std::endl : std::cout << "Error" << std::endl;

    }

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
        if (tokens.at(0).toInt() == 1) {
            m_startPoint = tokens.at(1);
        }
        if (tokens.at(1) != QString("|")) {
            currentToken = tokens.at(1);
            for (int i =3; i < tokens.size(); i ++) {
                if (tokens.at(i) == "lamda") continue;
                r->addDerived(tokens.at(i));
            }
        }
        else {
            for (int i =2; i < tokens.size(); i ++) {
                if (tokens.at(i) == "lamda") continue;
                r->addDerived(tokens.at(i));
            }
        }
        Table *table = Table::instance();
        table->addRule(currentToken, r);
    }
}

void FFParser::readSourceCodeLine()
{
    while(!m_sourceCodeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Source code file cannot be opened");
    }
    while(!m_sourceCodeFile.atEnd()) {
        QString line(m_sourceCodeFile.readLine());
        line = line.trimmed();
        QStringList tokens = line.split(QRegExp("[ \t\r\n\f]"));
        m_sourceCodeLine.push_back(tokens);
    }
}
