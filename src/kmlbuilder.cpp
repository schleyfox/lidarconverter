#include "kmlbuilder.h"
#include "kml/container.h"
#include "kml/kml.h"
#include "kml/collada.h"
#include "kml/netlink.h"

/**
 * Creates the directory structure in output_dir/
 *
 * @param output_dir the directory into which the files should be placed
 * @param image_dir the directory where the image files are located for
 * relocation
 */
KMLBuilder::KMLBuilder(QDir output_dir, QDir image_dir) {
	output_directory = output_dir;
	image_directory = image_dir;
	
	fileDirs["root"] = new QDir(output_dir);
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
	subDirNames << "root" << "ge_files" << "models" << "images";
	for(int i = 1; i < subDirNames.size(); i++) {
		if (!fileDirs[subDirNames.at(i-1)]->exists(subDirNames.at(i)) &&
					!fileDirs[subDirNames.at(i-1)]->mkdir(subDirNames[i])) {
			qDebug() << "ERROR WHILE CREATING " << subDirNames[i];
			return false;
		} else {
			fileDirs[subDirNames.at(i-1)]->cd(subDirNames[i]);
			fileDirs[subDirNames.at(i)] =  new QDir(fileDirs[subDirNames.at(i-1)]->absolutePath());
			qDebug() << fileDirs[subDirNames.at(i)]->absolutePath();
			fileDirs[subDirNames.at(i-1)]->cdUp();
		}
	}	

	return true;
}

/**
 * Creates the KML, COLLADA and Network Link KML files for use in Google Earth.
 *
 * @param segments A vector of individual swath segments for processing.
 */
bool KMLBuilder::generateFiles(QVector<Segment> segments) {
	container* c;
	kml *kmlFile;
	collada *colladaFile;
	netlink *netlinkFile;
	netlinkFile = new netlink(fileDirs["root"], templates["header"],
		templates["network_link"], templates["footer"]);
	for(int i = 0; i < segments.size(); i++) {	
		if ((c = readSegment(segments.at(i))) == NULL)
			return 0;
		kmlFile = new kml(fileDirs["ge_files"], c, templates["kml"]);
		colladaFile = new collada(fileDirs["models"], c,
			templates["collada"]);
		netlinkFile->addLink(c);
		delete kmlFile;
		delete c;
	}
	delete netlinkFile;
	
	relocateImages();
	return 1;	
}

/**
 * Reads in the text file containing CALIPSO geometric data.
 *
 * @param s segment to used to create a container object.
 */
container* KMLBuilder::readSegment(Segment s) {
	container *c = new container();
	
	c->initLat = s.first()->lat().degs(); 
	c->endLat = s.last()->lat().degs();
	c->initLong = s.first()->lon().degs();
	c->endLong = s.last()->lon().degs();
	c->midLat = s.midpoint()->lat().degs();
	c->midLong = s.midpoint()->lon().degs();
	c->heading = fuzzy_round(s.heading().degs(),0);
	c->altitude = s.droppingDistance();
	c->width = s.width();
	c->length = s.length();	
	c->name = s.segmentName();
	return c;
}

/**
 * Move the images to the images folder.
 */
bool KMLBuilder::relocateImages() {
	QStringList filters;
	filters << "*.png";

	image_directory.setNameFilters(filters);
	qDebug() << image_directory.entryList().size();
	QDirIterator iterator(image_directory);
	QFile *file;
	QString name;

	while(iterator.hasNext())
	{
		file = new QFile(iterator.next());
		QString fn = QFileInfo(*file).fileName();
		file->copy(fileDirs["images"]->absolutePath() + QDir::separator() + fn);
		file->remove();
		delete file;
	}

	return true;
}

