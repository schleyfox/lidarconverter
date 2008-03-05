#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H
#include "gui_common.h"
#include "datasourcewidget.h"
#include "resolutionmapwidget.h"
#include "colormapwidget.h"

class ConfigFileParser {
	public:
	ConfigFileParser(DataSourceWidget* ds = 0, ResolutionMapWidget* rm = 0,
		       ColorMapWidget* cm = 0);	
	bool parseFile(QString fn);
	bool parse(QString xml);

	protected:
	bool parseLidarProject(QDomNode node);
	bool parseDataSource(QDomNode node);
	bool parseColorMap(QDomNode node);
	bool parseResolutions(QDomNode node);

	DataSourceWidget* datasource;
       	ResolutionMapWidget* resmap;
	ColorMapWidget* colormap;

	QDomDocument* doc;
};
#endif
