#ifndef KMLBUILDER_H
#define KMLBUILDER_H
#include "common.h"
#include "segment.h"
#include "kml/container.h"
#include "kml/kml.h"
#include "kml/collada.h"
#include "kml/netlink.h"

class KMLBuilder {
	public:
	KMLBuilder(QDir output_dir, QDir image_dir);
	bool generateFiles(QVector<Segment> segments);

	protected:
	bool readTemplates();
	bool createDirectories();
	bool relocateImages();
	
	container* readSegment(Segment s);

	enum templateNameID { KML = 0, COLLADA, NETLINK, HEAD, FOOT };
	enum subDirectories { ROOT = 0, GEFILES, MODELS, IMAGES };

	QDir output_directory, image_directory;

	QHash<int, QString> templates;
	QHash<int, QDir*> fileDirs;
	QString filePath;
	QStringList subDirNames;
};
#endif
