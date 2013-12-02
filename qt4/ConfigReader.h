#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QVariant>
#include <QMap>
#include <qjson/parser.h>
#include <qjson/serializer.h>

enum Error {
	Error_File_Not_Found = 404,
	Error_Config_Parse = 400,
	Error_Config_Empty = 401
};

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit ConfigReader(QObject *parent = 0);
    ConfigReader(QString configFile);
		QList< QVariant > getServerList();
		quint32 getInterval();
		quint16 getError();
    
signals:
    
public slots:
	
private:
	 QVariantMap contents;
	quint16 error;
	
};

#endif // CONFIGREADER_H
