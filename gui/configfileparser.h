#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H

class ConfigFileParser {
	public:
	ConfigFileParser(DataSourceWidget* ds, ResolutionMapWidget* rm,
		       ColorMapWidget* cm);	
	bool parseFile(QString fn);
	bool parse(QString xml);

	protected:
	bool parseLidarProject(QDomNode node);
	bool parseDataSource(QDomNode node);
	bool parseColormap(QDomNode node);
	bool parseResolutions(QDomNode node);

	DataSourceWidget* datasourse;
       	ResolutionMapWidget* resmap;
	ColorMapWidget* colormap;

	QDomDocument* doc;
};
#endif
