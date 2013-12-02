#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QString>
#include <QLibrary>
#include <QObject>
#include <QDebug>
#include <QSystemTrayIcon>

enum FreedesktopNotificationType {
	None = 0,
	KNotification = 1,
	LibNotify = 2,
	QTShowMessage = 3
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
	Q_OBJECT
	
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
