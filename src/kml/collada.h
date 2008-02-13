/*
 * collada.h
 * Class to generate a COLLADA model file.
 */
#ifndef COLLADA_H
#define COLLADA_H

#include <QString>
#include <QFile>
#include <QTime>
#include <QDate>
#include "container.h"

class collada
{
	public:
		collada(QDir* d, container* c, const QString t);
		~collada();
	private:
		void applyGeometries();
		bool writeFile();
		QString templateFile;
		container ctr;
		QDir dir;
};

collada::collada(QDir* d, container* c, const QString t)
{
	templateFile = QString(t);
	dir = *d;
	ctr = *c;
	applyGeometries();
	writeFile();
}

collada::~collada() {}

void collada::applyGeometries()
{
	QString geometry, str;

	str.sprintf("%lf %lf %lf ", 0.0, (ctr.length / 2.0),
		(ctr.width - ctr.altitude));
	geometry.append(str);	
	str.sprintf("%lf %lf %lf ", 0.0, -(ctr.length / 2.0),
		(-ctr.altitude));
	geometry.append(str);
	str.sprintf("%lf %lf %lf ", 0.0, (ctr.length / 2.0),
		(-ctr.altitude));
	geometry.append(str);
	str.sprintf("%lf %lf %lf ", 0.0, -(ctr.length / 2.0),
		(ctr.width - ctr.altitude));
	geometry.append(str);
	
	templateFile.replace("#GEOM$", geometry);
	templateFile.replace("#NAME$", ctr.name);
	templateFile.replace("#TIME$",
		QString(QTime::currentTime().toString("hh:mm:ss")));
	templateFile.replace("#DATE$",
		QString(QDate::currentDate().toString("yyyy-MM-dd")));
}

bool collada::writeFile()
{
	QFile file(QString(dir.absolutePath() + dir.separator() +
		ctr.name + ".dae"));
	if (!file.open(QIODevice::WriteOnly))
		return 0;
	QTextStream stream(&file);
	stream << templateFile << endl;

	file.close();

	return 1;
}

#endif
