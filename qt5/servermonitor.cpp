#include "servermonitor.h"

#include <QTimer>
#include <QLibrary>
#include <iostream>
#include <QSocketNotifier>
#include <boost/concept_check.hpp>

ServerMonitor::ServerMonitor()
{
		const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
		QString filename = home + "/.config/ServerMonitor/config.json";
		this->reader = new ConfigReader(filename);
		
		if(reader->getError() == 0){ 
			this->init();
		} else {
			std::cout << filename.toStdString() << " Error : " << (int) reader->getError() << std::endl;
			exit(reader->getError());
		}
}

ServerMonitor::ServerMonitor ( QStringList args ) : QObject()
{
		this->reader = new ConfigReader(args.value(1));
		
		if(reader->getError() < 0){ 
			this->init();
		} else {
			std::cout << "Error : " << (int) reader->getError() << std::endl;
			exit(reader->getError());
		}
	
}

ServerMonitor::~ServerMonitor()
{}


    /**
	* Creates a timer for each host/port found at the config file
	*/
	
void ServerMonitor::init()
{
	
	this->serverList = this->reader->getServerList();
    
    Notification notice();
    if(notice == NULL){
    }
	std::cout << serverList.size() << std::endl;
	QVariant data;
	QVariant port;
	foreach(data, serverList){
		
        QVariantMap content = data.toMap();
		QList<QVariant> ports =  content["port"].toList();
		
    	foreach (port, ports){
			
			QTimer* timer = new QTimer(this);
			ThreadPing *tping = new ThreadPing( content["host"].toString(), (quint16) port.toInt());
			
			connect( timer, SIGNAL(timeout()), tping, SLOT(run()));
			connect( tping,SIGNAL(isAlive(quint16)), SLOT(output(quint16)));
			connect( tping, SIGNAL(stateChanged(QString)),  SLOT(showState(QString)));
			
			timer->start( reader->getInterval() * 1000);
		}
	}
	
	
}

void ServerMonitor::showState(QString state)
{
    

//        std::cout << state.toStdString() << std::endl;;
//		qDebug() <<  "Unsupported notification system or not found";

}

void ServerMonitor::output(quint16 lag)
{
    
    std::cout << "Servidor contest en " << lag << " ms" << std::endl;;
}

