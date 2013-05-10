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
    
    this->lib = None;
    
    QSystemTrayIcon notifier(this);
    this->init =
        (NotificationInit)      notify.resolve( "notify_init");  
    
    if(this->notify.isLoaded()) {
        
        this->dialog=
            (NotificationDialog)    notify.resolve( "notify_notification_new");
        this->category =
            (NotificationCategory)  notify.resolve( "notify_notification_set_category");
        this->timeout =
            (NotificationTimeout)   notify.resolve( "notify_notification_set_timeout");
        this->send =
            (NotificationShow)      notify.resolve( "notify_notification_show");   
        this->message =
            ( Message *)            notify.resolve( "NotifyNotification");  
 
        
        this->lib = LibNotify;
        
    } else if(notifier.supportsMessages()){
        this->lib = QTShowMessage;
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
    
    
    switch (this->lib) {
            
        case LibNotify: {
        
            this->init(" ");
            
            this->message = ( Message *)dialog(title.toStdString().data(), msg.toStdString().data()," ");
            this->timeout(message, 3000);
            this->send(message,NULL);
        
            break;
        }
        case KNotification:
        case QTShowMessage: {
        
            QSystemTrayIcon notifier(this);
            notifier.showMessage(title, msg);
            
            //                this->init(" ");
            //                this->message = (Message *) dialog("Notifications are supported", " ", " ");
            //                this->timeout(message, 3000);
            //                this->send(message,NULL);
            
        }
        case None:
        default: {
            
            qDebug() << title << " " << msg;
                
            break;
        }
    }
    
}

#include "Notification.moc"
