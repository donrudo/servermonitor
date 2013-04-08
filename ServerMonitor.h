#ifndef ServerMonitor_H
#define ServerMonitor_H

#include <QtCore/QObject>
#include <QVariant>
#include <QDesktopServices>
#include <QVariantMap>
#include <QMap>
#include <QList>
#include <QStringList>
#include "ConfigReader.h"
#include "ThreadPing.h"

class ServerMonitor : public QObject
{
Q_OBJECT
public:
    ServerMonitor();
		ServerMonitor( QStringList args );
		virtual void init();
    virtual ~ServerMonitor();
private slots:
		void showState(QString);
    void output(quint16);
private:
		ThreadPing *tp;
		ConfigReader *reader;
		
		QMap<QString,QVariant> config;
		QList<QVariant> serverList;
};

#endif // ServerMonitor_H
