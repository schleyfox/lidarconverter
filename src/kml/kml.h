/*
 * kml.h
 * Class to generate a KML file.
 */
#ifndef KML_H
#define KML_H

#include <QString>
#include <QFile>
#include "container.h"

class kml
{
	public:
		kml(QDir* d, container* c, const QString* t);
		~kml();
	private:
		void applyGeometries();
		bool writeFile();
		QString* templateFile;
		container ctr;
		QDir dir;
};

kml::kml(QDir* d, container* c, const QString* t)
{
	templateFile = new QString(*t);
	dir = *d;
	ctr = *c;
	applyGeometries();
	writeFile();
	delete templateFile;
}

kml::~kml() {}

void kml::applyGeometries()
{
	QString str;
	templateFile->replace("#NAME$", QString(ctr.name));
	str.sprintf("%lf", ctr.midLong);
	templateFile->replace("#LONG$", str);
	str.sprintf("%lf", ctr.midLat);
	templateFile->replace("#LAT$", str);
	str.sprintf("%lf", ctr.heading);
	templateFile->replace("#HEAD$", str);
}

bool kml::writeFile()
{
	QFile file(QString(dir.absolutePath() + 
		dir.separator() + ctr.name + ".kml"));
	if (!file.open(QIODevice::WriteOnly))
		return 0;
	QTextStream stream(&file);
	stream << *templateFile << endl;
	
	file.close();
	
	return 1;
}

#endif
