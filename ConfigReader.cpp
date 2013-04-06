#include "ConfigReader.h"
#include <boost/concept_check.hpp>

ConfigReader::ConfigReader(QObject *parent) :
    QObject(parent)
{
}

ConfigReader::ConfigReader(QString FileName):
    QObject(parent)
{
	QJson::Parser parser;
	QFile configFile = new QFile(FileName);
	
	if (!configFile.open(QIODevice::ReadOnly))
  {
		qDebug() << "Could not open file " << FileName;
  }
  
	QByteArray ba = configFile.readAll();
	if(ba.isNull()){
		qDebug() << "Warning: Empty config file";
	}

	this->contents = parser.parse( ba, true );

}



#include "ConfigReader.moc"
