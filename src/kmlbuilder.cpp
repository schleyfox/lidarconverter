#include "kmlbuilder.h"

KMLBuilder::KMLBuilder(QDir output_dir, QDir image_dir) {
	output_directory = output_dir;
	image_directory = image_dir;
	
	readTemplates();
	createDirectories();

}

/**
 * Reads the templates into QStrings stored in memory to reduce File I/O
 * operations.
 */
bool KMLBuilder::readTemplates() {
	QStringList templateNames;
	templateNames <<  "kml" <<
			  "collada" <<
  			  "network_link" <<
			  "header" <<
			  "footer";
	
	for (int i = 0; i < templateNames.size(); i++) {
		QFile readFile(QString(":/%1_template.template").arg(templateNames.at(i)));
		
		if (!readFile.exists()) {
			qDebug() << templateNames.at(i) << "\a DOES NOT EXIST ";
			return false;
		} 
		if (!readFile.open(QIODevice::ReadOnly)) {
			qDebug() << templateNames.at(i) << "\a I/O "
				<< "ERROR";
			return false;
		} 
		
		QTextStream in(&readFile);
		
		templates[templateNames.at(i)] = in.readAll();
		readFile.close();
	}
	
	return true;
}

/**
 * This function creates the directories where the files will be stored.
 */
bool KMLBuilder::createDirectories() {
	subDirNames << "" << "ge_files" << "models" << "images";
	for(int i = 0; i < subDirNames.size()-1; i++) {
		if (!output_directory.mkdir(subDirNames[i+1])) {
			qDebug() << "ERROR WHILE CREATING " << subDirNames[i+1];
			return false;
		} else {
			output_directory.cd(subDirNames[i+1]);
			fileDirs[i] =  new QDir(output_directory.absolutePath());
			output_directory.cdUp();
		}
	}	

	return true;
}

/*
 * Creates the KML, COLLADA and Network Link KML files for use in Google Earth.
 */
bool KMLBuilder::generateFiles(QVector<Segment> segments) {
	container* c;
	kml *kmlFile;
	collada *colladaFile;
	netlink *netlinkFile;
	netlinkFile = new netlink(fileDirs[ROOT], templates["header"],
		templates["network_link"], templates["footer"]);
	for(int i = 0; i < segments.size(); i++) {	
		if ((c = readSegment(segments.at(i))) == NULL)
			return 0;
		kmlFile = new kml(fileDirs[GEFILES], c, templates["kml"]);
		colladaFile = new collada(fileDirs[MODELS], c,
			templates["collada"]);
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
container* KMLBuilder::readSegment(Segment s) {
	container *c = new container();
	
	c->initLat = s.first()->lat().degs(); 
	c->endLat = s.last()->lat().degs();
	c->initLong = s.first()->lon().degs();
	c->endLong = s.last()->lon().degs();
	c->midLat = s.midpoint()->lat().degs();
	c->midLong = s.midpoint()->lon().degs();
	c->heading = s.heading().degs();
	c->altitude = s.droppingDistance();
	c->width = s.width();
	c->length = s.length();	
	c->name = s.segmentName();
	return c;
}

/*
 * Move the images to the images folder.
 */
bool KMLBuilder::relocateImages()
{
	bool status = 1;
	QStringList filters;
	filters << "*.png";

	fileDirs[ROOT]->setNameFilters(filters);
	QDirIterator iterator(*fileDirs[ROOT]);
	QFile *file;
	QString *name;

	while(iterator.hasNext() && status)
	{
		file = new QFile(iterator.next());
		name = new QString(file->fileName());
		name->remove(0, 
		     name->lastIndexOf(QString(fileDirs[ROOT]->separator()))+1);
		status = file->copy(fileDirs[IMAGES]->absolutePath() +
			fileDirs[IMAGES]->separator() + *name);
		file->remove();
		delete file;
		delete name;
	}

	return status;
}

