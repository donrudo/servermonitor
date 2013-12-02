#include <QCoreApplication>
#include "ServerMonitor.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    ServerMonitor foo;
    return app.exec();
}
