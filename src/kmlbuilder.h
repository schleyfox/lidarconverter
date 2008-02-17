#ifndef KMLBUILDER_H
#define KMLBUILDER_H
#include "common.h"
#include "segment.h"

class container;

/**
 * Constructs a KML folder structure for a list of Segments.
 * The swath created in the Segments can be loaded by loading the single
 * networklink file created in the root directory of the KML folder structure
 *
 * @author T. Nelson Hillyer
 * @see LidarConverterTests::CurveTransform_transform()
 */
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
