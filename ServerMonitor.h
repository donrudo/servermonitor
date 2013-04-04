#ifndef ServerMonitor_H
#define ServerMonitor_H

#include <QtCore/QObject>
#include "ThreadPing.h"

class ServerMonitor : public QObject
{
Q_OBJECT
public:
    ServerMonitor();
    virtual ~ServerMonitor();
private slots:
		void showState(QString);
    void output(quint16);
private:
		ThreadPing *tp;
};

#endif // ServerMonitor_H
