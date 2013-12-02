#include "configreader.h"
#include <boost/concept_check.hpp>

//ConfigReader::ConfigReader(QObject *parent) :
//    QObject()
//{
//}

ConfigReader::ConfigReader(QString FileName):
    QObject()
{
	QFile *configFile = new QFile(FileName);
	
	this->error = 0;
	if (!configFile->open(QIODevice::ReadOnly))
  {
		this->error = Error_File_Not_Found;
  } else {
  
		QByteArray ba = configFile->readAll();
		configFile->close();
		if(ba.isNull())
    {
			this->error = Error_Config_Empty;
		} 
		else 
    {
      QJsonParseError *err = NULL;
			QJsonDocument doc = QJsonDocument::fromJson(ba, err);
			if( err != NULL || doc.isNull() )
      {
				this->error = Error_Config_Parse;
        err = NULL;
			}
            
      QJsonObject jsonContents = doc.object();
      contents = jsonContents.toVariantMap();
    } 

	}
}

QList<QVariant > ConfigReader::getServerList()
{
	return this->contents["server"].toList();
}

quint32 ConfigReader::getInterval()
{

	return (quint32)(this->contents["interval"].toInt());
}


quint16 ConfigReader::getError()
{
	return this->error;
}
