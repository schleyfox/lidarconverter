/*
 * netlink.h
 * Class to generate NetLink KML files.
 *
 * Written by: T. Nelson Hillyer & Nicholas Gasperoni
 * Date: July 24, 2007
 */
#ifndef NETLINK_H
#define NETLINK_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include "container.h"

class netlink
{
	public:
		netlink(QDir* d, const QString head, const QString body,
			const QString foot);
		~netlink();
		void addLink(container* c);
	private:
		QString bodyTemplate;
		QString footer;
		QString header;
		container ctr;
		QFile *file;
		QTextStream *stream;
};

netlink::netlink(QDir* d, const QString head, const QString body,
	const QString foot)
{
	header = head;
	bodyTemplate = body;
	footer = foot;
	file = new QFile(QString(d->absolutePath() + d->separator() + 
		"calipso.kml"));
	file->open(QIODevice::WriteOnly);
	stream = new QTextStream(file);
	
	*stream << header << endl;
}

netlink::~netlink()
{
	*stream << footer;
	file->close();

	delete stream;
	delete file;
}

void netlink::addLink(container *c)
{
	QString buffer(bodyTemplate);
	
	buffer.replace("#NAME$", c->name);

	*stream << buffer << endl;
}

#endif
