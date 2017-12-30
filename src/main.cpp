#include <QCoreApplication>

#include "ffparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FFParser p;
    p.run();

    return 0;
}
