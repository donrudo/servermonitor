#ifndef ServerMonitor_H
#define ServerMonitor_H

#include <QtCore/QObject>
#include <QVariant>

 //  replaced for QT 5 
 // #include <QDesktopServices>
 // QT 5
#include <QStandardPaths>
#include <QVariantMap>
#include <QMap>
#include <QList>
#include <QStringList>
#include "notification.h"
#include "configreader.h"
#include "threadping.h"

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
