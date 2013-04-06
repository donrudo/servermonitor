#include "ServerMonitor.h"

#include <QTimer>
#include <iostream>
#include <boost/concept_check.hpp>

ServerMonitor::ServerMonitor()
{
		QString filename = "~/.config/ServerMonitor/config.json";
		this->reader = new ConfigReader(filename);
		
		
		if(reader->getError() < 0){ 
			this->init();
		} else {
			std::cout << "Error : " << (int) reader->getError();
		}
}

ServerMonitor::ServerMonitor ( QStringList args ) : QObject()
{
	
		this->reader = new ConfigReader(args.value(1));
		
		if(reader->getError() < 0){ 
			this->init();
		} else {
			
			std::cout << "Error : " << (int) reader->getError();
			
		}
	
}

ServerMonitor::~ServerMonitor()
{}

void ServerMonitor::init()
{
	this->config = this->reader->getServerList();
	
	QTimer* timer = new QTimer(this);
	connect( tp,SIGNAL(isAlive(quint16)), SLOT(output(quint16)));
//	connect( tp, SIGNAL(stateChanged(QString)),  SLOT(showState(QString)));
	connect( timer, SIGNAL(timeout()), tp, SLOT(run()));
	timer->start( reader->getInterval() );
	
}

void ServerMonitor::showState(QString state)
{
	std::cout << state.toStdString() << std::endl;;
}

void ServerMonitor::output(quint16 lag)
{
    std::cout << "Servidor contest en " << lag << " ms" << std::endl;;
}

#include "ServerMonitor.moc"
