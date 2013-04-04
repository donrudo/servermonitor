#include "ServerMonitor.h"

#include <QTimer>
#include <iostream>
#include <boost/concept_check.hpp>

ServerMonitor::ServerMonitor()
{
    QTimer* timer = new QTimer(this);
		
//		tp = new ThreadPing("127.0.0.1", 443);
		tp = new ThreadPing("50.22.61.202", 443);
		connect( tp,SIGNAL(isAlive(quint16)), SLOT(output(quint16)));
		connect( tp, SIGNAL(stateChanged(QString)),  SLOT(showState(QString)));
		
    timer->start( 10 );
		tp->run();
}

ServerMonitor::~ServerMonitor()
{}

void ServerMonitor::showState(QString state)
{
//	std::cout << state.toStdString() << std::endl;;
	std::cout << state.toStdString() << std::endl;;
}

void ServerMonitor::output(quint16 lag)
{
	std::cout << "Servidor contestó en " << lag << " ms" << std::endl;;
}

#include "ServerMonitor.moc"
