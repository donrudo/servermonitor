#include "ConfigReader.h"
#include <boost/concept_check.hpp>

ConfigReader::ConfigReader(QObject *parent) :
    QObject()
{
}

ConfigReader::ConfigReader(QString FileName):
    QObject()
{
	bool ok = true;
	QJson::Parser parser;
	QFile *configFile = new QFile(FileName);
	
	this->error = 0;
	if (!configFile->open(QIODevice::ReadOnly))
  {
		this->error = Error_File_Not_Found;
  } else {
  
		QByteArray ba = configFile->readAll();
		configFile->close();
		if(ba.isNull()){
			this->error = Error_Config_Empty;
		}

		this->contents = parser.parse( ba, &ok ).toMap();

		if( !ok ){
			this->error = Error_Config_Parse;
		}
	}
	delete configFile;
}

QList< QVariant > ConfigReader::getServerList()
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



#include "ConfigReader.moc"
