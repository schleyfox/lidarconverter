#ifndef KMLBUILDER_H
#define KMLBUILDER_H
#include "common.h"
#include "segment.h"

class container;

class KMLBuilder {
	public:
	KMLBuilder(QDir output_dir, QDir image_dir);
	bool generateFiles(QVector<Segment> segments);

	protected:
	bool readTemplates();
	bool createDirectories();
	bool relocateImages();
	
	container* readSegment(Segment s);

	QDir output_directory, image_directory;

	QHash<QString, QString> templates;
	QHash<QString, QDir*> fileDirs;
	QString filePath;
	QStringList subDirNames;
};
#endif
