/* kmlbuilder.cpp
 * This program generates and organizes KML files for use in Google Earth. It 
 * uses the QT 4.0 C++ toolkit.
 *
 * Team: CALIPSO Data Visulization, Summer 2007
 *
 * Written by: 	T. Nelson Hillyer (DEVELOP NASA)
 * 		Nicholas Gasperoni (DEVELOP NASA)
 * 
 * Date: July 11, 2007
 * Version: 0.2 (alpha)
 */

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "container.h"
#include "kml.h"
#include "collada.h"
#include "netlink.h"

enum templateNameID { KML = 0, COLLADA, NETLINK, HEAD, FOOT };
enum subDirectories { ROOT = 0, GEFILES, MODELS, IMAGES };

bool readTemplates(void);
bool createDirectories(void);
bool generateFiles(void);
bool relocateImages(void);

container* readFile(QFile *file);

QString templateNames[] = {	"kml_template.template",
				"collada_template.template",
				"network_link_template.template",
				"header_template.template",
				"footer_template.template" };
QString *templates[5];
QDir *fileDir[4], *executableDir;
QString *filePath;
QString subDirName[] = { "", "ge_files", "models", "images" };

/*
 * This function initiates the KML build process.
 */
int main(int argc, char** argv)
{
	if (*(++argv) == NULL)
	{
		qDebug() << "\aERROR Improper Usage!!!" << endl << endl;
		qDebug() << "Correct Usage:" << endl;
		qDebug() << "kmlbuilder FILE_DIRECTORY_NAME" << endl;
		return EXIT_FAILURE;
	}
	executableDir = new QDir(".");
	filePath = new QString(*argv);
	subDirName[ROOT] = *filePath;
	fileDir[ROOT] = new QDir(*filePath);
	
	if (!fileDir[ROOT]->exists())
	{
		qDebug() << *filePath << "\a NOT FOUND!!!" << endl;
		return EXIT_FAILURE;
	}

	if (!readTemplates())
		return EXIT_FAILURE;

	if (!createDirectories())
		return EXIT_FAILURE;
	
	generateFiles();
	
	if (!relocateImages())
		return EXIT_FAILURE;

	for (int i = 0; i < 4; i++)
		delete fileDir[i];
	
	delete filePath;
	delete executableDir;
	return EXIT_SUCCESS;
}

/*
 * Reads the templates into QStrings stored in memory to reduce File I/O
 * operations.
 */
bool readTemplates(void)
{
	bool readStatus = 1;
	QFile *readFile;
	
	for (int i = 0; i < 5; i++)
	{
		readFile = new QFile(templateNames[i]);
		if (!readFile->exists())
		{
			qDebug() << templateNames[i] << "\a DOES NOT EXIST "
 				<< "IN EXECUTABLE DIRECTORY!!!" << endl;
			readStatus = 0;
		}
		else
		{
			if (!readFile->open(QIODevice::ReadOnly))
			{
				qDebug() << templateNames[i] << "\a I/O "
					<< "ERROR";
				readStatus = 0;
			}
			else
			{
				QTextStream stream(readFile);
				
				templates[i] = new QString();
				while (!stream.atEnd())
					*templates[i] += stream.readLine()
						+= '\n';
				readFile->close();
			}
		}
		delete readFile;
	}
	
	return readStatus;
}

/*
 * This function creates the directories where the files will be stored.
 */
bool createDirectories(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (!fileDir[i]->mkdir(subDirName[i+1]))
		{
			qDebug() << "ERROR WHILE CREATING " << subDirName[i+1];
			return 0;
		}
		else
		{
			fileDir[i]->cd(subDirName[i+1]);
			fileDir[i+1] = new QDir(fileDir[i]->absolutePath());
			fileDir[i]->cdUp();
		}	
	}

	return 1;
}

/*
 * Creates the KML, COLLADA and Network Link KML files for use in Google Earth.
 */
bool generateFiles(void)
{
	QStringList filter;
	filter << "*.txt";

	fileDir[ROOT]->setNameFilters(filter);
	QDirIterator iterator(*fileDir[ROOT]);
	container* c;
	QFile *file;
	kml *kmlFile;
	collada *colladaFile;
	netlink *netlinkFile;
	netlinkFile = new netlink(fileDir[ROOT], templates[HEAD],
		templates[NETLINK], templates[FOOT]);
	while (iterator.hasNext())
	{
		file = new QFile(iterator.next());
		if ((c = readFile(file)) == NULL)
			return 0;
		kmlFile = new kml(fileDir[GEFILES], c, templates[KML]);
		colladaFile = new collada(fileDir[MODELS], c,
			templates[COLLADA]);
		netlinkFile->addLink(c);
		delete kmlFile;
		delete c;
	}
	delete netlinkFile;
	return 1;	
}

/* FIX ME ----> ADD IN READ I/O CHECKS!!!
 * Reads in the text file containing CALIPSO geometric data.
 */
container* readFile(QFile *file)
{
	if (!file->open(QIODevice::ReadOnly))
		return NULL;
	QTextStream stream(file);
	container *c = new container();
	
	stream >> c->initLat; 
	stream >> c->endLat;
	stream >> c->initLong;
	stream >> c->endLong;
	stream >> c->midLat;
	stream >> c->midLong;
	stream >> c->heading;
	stream >> c->altitude;
	stream >> c->width;
	stream >> c->length;	
	QString fileName = file->fileName();
	
	fileName.resize(fileName.lastIndexOf('.'));
	fileName.remove(0, 
		fileName.lastIndexOf(QString(fileDir[0]->separator()))+1);
	c->name = fileName;
	return c;
}

/*
 * Move the images to the images folder.
 */
bool relocateImages(void)
{
	bool status = 1;
	QStringList filters;
	filters << "*.png";

	fileDir[ROOT]->setNameFilters(filters);
	QDirIterator iterator(*fileDir[ROOT]);
	QFile *file;
	QString *name;

	while(iterator.hasNext() && status)
	{
		file = new QFile(iterator.next());
		name = new QString(file->fileName());
		name->remove(0, 
		     name->lastIndexOf(QString(fileDir[ROOT]->separator()))+1);
		status = file->copy(fileDir[IMAGES]->absolutePath() +
			fileDir[IMAGES]->separator() + *name);
		file->remove();
		delete file;
		delete name;
	}

	return status;
}

