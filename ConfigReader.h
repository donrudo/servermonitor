#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QObject>
#include <QFile>
#include <QVariant>
#include <qjson/parser.h>
#include <qjson/serializer.h>

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit ConfigReader(QObject *parent = 0);
    explicit ConfigReader(QString configFile);
    
signals:
    
public slots:
	
private:
	 QVariantMap contents;
	
};

#endif // CONFIGREADER_H
