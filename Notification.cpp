/*
    <one line to give the library's name and an idea of what it does.>
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


#include "Notification.h"

Notification::Notification() :  notify("libnotify.so")
{
    
    
    
    this->message =
        ( Message *) notify.resolve("NotifyNotification");
    this->init =
        (NotificationInit)  notify.resolve( "notify_init");
    this->dialog=
        (NotificationDialog)  notify.resolve("notify_notification_new");
    this->category =
        (NotificationCategory)  notify.resolve("notify_notification_set_category");
    this->timeout =
        (NotificationTimeout)  notify.resolve("notify_notification_set_timeout");
    this->send =
        (NotificationShow)  notify.resolve( "notify_notification_show");
    
    if(this->notify.isLoaded()) {
        this->lib = LibNotify;
    } else {
        qDebug() << "load none";
        this->lib = None;
    }
    
  //  qDebug() << "ran notification constructor";

}

Notification::~Notification()
{
	
}

FreedesktopNotificationType Notification::getLib(){
    return this->lib;
}

	/**
	* to be used when the desktop supports pointer events
	*/
void Notification::clickHandler()
{
	
}

void Notification::sendNotification(QString title,QString msg)
{
    
    QSystemTrayIcon notifier(this);
    
    if(notifier.supportsMessages()){
        notifier.showMessage("Pruebala", "Prueba esta!!", QSystemTrayIcon::Information , 1000);
        
        
        this->init("prueba esta");
        this->message = (Message *) dialog("Notifications are supported", " ", " ");
        this->timeout(message, 3000);
		this->send(message,NULL);
    } else {
   
        if (this->lib == LibNotify){
            
            this->init("prueba esta");
            
            this->message = ( Message *)dialog(title.toStdString().data(), msg.toStdString().data(),"probando");
            
            this->timeout(message, 3000);
            
            this->send(message,NULL);
            
        } 
    }
    
}

#include "Notification.moc"
