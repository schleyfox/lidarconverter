#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H
#include "gui_common.h"
#include "datasourcewidget.h"
#include "resolutionmapwidget.h"
#include "colormapwidget.h"

class ConfigFileParser {
	public:
	bool readFile(QString fn);
	bool read(QString xml);
	
	bool parseDataSource(DataSourceWidget* ds);
	bool parseColorMap(ColorMapWidget* colormap);
	bool parseResolutions(ResolutionMapWidget* resmap);

	protected:

	QDomDocument doc;
};
#endif
