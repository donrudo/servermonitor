/*
    Copyright (c) 2013, Carlos A. Morales <carlos.morales@playfulplay.com>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Carlos A. Morales <carlos.morales@playfulplay.com> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Carlos A. Morales <carlos.morales@playfulplay.com> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "ThreadPing.h"

ThreadPing::ThreadPing ( QString hostname, quint16 port ) : QObject()
{
	this->hostname = hostname;
	this->port = port;
	this->server = new QTcpSocket(this);
	
	this->timeout = new QTimer();
	this->lag = 0;
}

ThreadPing::~ThreadPing()
{

}


void ThreadPing::run()
{
	server->abort(); // sets the socket to a initial connection
	if( !server->open(QIODevice::ReadWrite)){
		qDebug() << "Failed to get access to Network Card";
		return;
	}
	
	timeout->setInterval(1000);
	
	qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
	qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
	
	connect(timeout, SIGNAL(timeout()), this, SLOT(increaseLag()));
	connect(server, SIGNAL(connected()), this, SLOT(connected()));
	connect(server, SIGNAL(stateChanged(QAbstractSocket::SocketState)),this, SLOT(printState()));
	
	timeout->start();
	server->connectToHost(hostname, port);
	
}

/**
 * Slots
 */
void ThreadPing::increaseLag()
{
	this->lag += timeout->interval();
}

void ThreadPing::connected()
{
	timeout->stop();
	server->disconnectFromHost();
	this->state = "True";
	
	
	qDebug() << "INTERNAL > Servidor contestó en " << lag << " ms";
	emit isAlive(lag);
	
}
void ThreadPing::printState()
{
	QString str_currentState;
	
	switch(server->state()){
		case 0:
		{
			str_currentState = "The socket is not connected.";
			break;
		}
		case 1:
		{
			str_currentState = "The socket is performing a host name lookup.";
			break;
		}
		case 2:
		{
			str_currentState = "The socket has started establishing a connection.";
			break;
		}
		case 3:
		{
			str_currentState = "A connection is established.";
			break;
		}
		case 4:
		{
			str_currentState = "The socket is bound to an address and port (for servers).";
			break;
		}
		case 5:
		{
			str_currentState = "Unknown state (internal use).";
			break;
		}
		case 6:
		{
			str_currentState = "The socket is about to close (data may still be waiting to be written).";
			break;
		}
	}
	
	qDebug() << "INTERNAL > " << str_currentState;
	emit stateChanged(str_currentState);
}


/**
 * Getters
 */


quint16 ThreadPing::getElapsedTime() const
{
	return lag;
}

QString ThreadPing::getHostname() const
{
	return this->hostname;
}

quint16 ThreadPing::getPort() const
{
	return this->port;
}


/**
 * Just for debug
 */


QString ThreadPing::printBool ( bool value ) const
{
	if( !value ){
		return "False";
	}
	
	return "True";
}

#include "ThreadPing.moc"
