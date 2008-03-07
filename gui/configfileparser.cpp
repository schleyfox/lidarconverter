#include "configfileparser.h"

bool ConfigFileParser::read(QString xml) {
	return doc.setContent(xml);
}

bool ConfigFileParser::readFile(QString fn) {
	QFile file(fn);
	if(file.open(QIODevice::ReadOnly)) {
		bool r = doc.setContent(&file);
		file.close();
		return r;
	} else {
		return false;
	}
}

bool ConfigFileParser::parseResolutions(ResolutionMapWidget* resmap) {
	qDebug() << "In parseResolutions";
	QMap<int,int> map;
	QDomElement resolutions = doc.elementsByTagName("resolutions").item(0)
		.toElement();
	if(!resolutions.isNull()) {
		qDebug() << "Found \"resolutions\"";
		QDomNodeList layers = resolutions.elementsByTagName("layer");
		qDebug() << "  " << layers.size() << " layers";
		for(int i = 0; i < layers.size();  i++) {
			QDomElement l = layers.item(i).toElement();
			if(!l.isNull()) {
				qDebug() << "In layer " << i;
				QDomElement alt = l.elementsByTagName("base_altitude").item(0).toElement();
				QDomElement res = l.elementsByTagName("vertical_resolution").item(0).toElement();
				QString key = alt.firstChild().toText().data();
				QString value = res.firstChild().toText().data();
				if(!key.isNull() && !value.isNull()) {
					map[key.toInt()] = value.toInt();
				}
			}
		}
		resmap->fromMap(map);
		return true;
	} else {
		return false;
	}
}
