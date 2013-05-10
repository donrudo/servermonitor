/*
    Bridge to use Desktop Notifications libraries depending on the libs available on the current system.
    Copyright (C) 2013  Carlos A. Morales <carlos.morales@playfulplay.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QString>
#include <QLibrary>
#include <QObject>
#include <QDebug>

enum FreedesktopNotificationType {
	None = 0,
	KNotification = 1,
	LibNotify = 2
	
	//TODO Add some Windows, Mac or Android Notifications lib support.
};


// libnotify support
typedef void *Message;
typedef void (*NotificationInit)(const char[]);
typedef Message (*NotificationDialog)(const char[],const char[],const char[]);
typedef void (*NotificationCategory)(Message *,const char[]);
typedef void (*NotificationTimeout)(Message *, quint32);
typedef void (*NotificationShow)(Message *, void *);
//// END libnotify support

class Notification : public QObject
{
	Q_OBJECT;
	
public:
  Notification();
  virtual ~Notification();
	
	void sendNotification(QString, QString);
	void operator<<(QString);
	FreedesktopNotificationType getLib();
    void load();
    
public slots:
	void clickHandler();
signals:
	void libNotFound();
	void msgTrigger();
	
private:
	void libNotifySendMessage(QString, qint16);
	void knotificationSendMessage(QString, qint16);
	
	QLibrary notificationLib;
	FreedesktopNotificationType lib;
    
    QLibrary notify;
    
    // for libnotify support
    Message *message;
    NotificationInit init;
    NotificationDialog dialog;
    NotificationCategory category;
    NotificationTimeout timeout;
    NotificationShow send;
    
    //// END libnotify support
    
};

#endif // NOTIFICATION_H
