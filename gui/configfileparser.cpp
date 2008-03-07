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
	QMap<int,int> map;
	QDomElement resolutions = doc.elementsByTagName("resolutions").item(0)
		.toElement();
	if(!resolutions.isNull()) {
		QDomNodeList layers = resolutions.elementsByTagName("layer");
		for(int i = 0; i < layers.size();  i++) {
			QDomElement l = layers.item(i).toElement();
			if(!l.isNull()) {
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

bool ConfigFileParser::parseColorMap(ColorMapWidget* colormap) {
	QMap<double,uint> map;
	QDomElement colors = doc.elementsByTagName("colormap").item(0).toElement();
	if(!colors.isNull()) {
		QDomNodeList color_ranges = colors.elementsByTagName("color_range");
		for(int i = 0; i < color_ranges.size(); i++) {
			QDomElement c = color_ranges.item(i).toElement();
			if(!c.isNull()) {
				QDomElement base_value = c.elementsByTagName("base_value").item(0).toElement();
				QDomElement color = c.elementsByTagName("color").item(0).toElement();
				QString key = base_value.firstChild().toText().data();
				QString value = color.firstChild().toText().data();
				if(!key.isNull() && !value.isNull()) {
					map[key.toDouble()] = value.toUInt(0,16);
				}
			}
		}
		colormap->fromMap(map);
		return true;
	} else {
		return false;
	}
}
