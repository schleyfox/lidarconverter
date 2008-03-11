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
	QMap<float,uint> map;
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

bool ConfigFileParser::parseDataSource(DataSourceWidget* ds) {
	QDomElement datasource = doc.elementsByTagName("datasource").item(0).toElement();
	if(!datasource.isNull()) {
		QDomNode resolutions = datasource.elementsByTagName("resolutions").item(0);
		if(!resolutions.isNull()) {
			QDomDocument resolutions_doc;
			QDomNode res_tmp = resolutions_doc.importNode(resolutions,true);
			resolutions_doc.appendChild(res_tmp);
			ConfigFileParser res_parse;
			res_parse.read(resolutions_doc.toString());
			res_parse.parseResolutions(ds->resolutionMapWidget());
		}

		QString longitude_name = datasource.elementsByTagName("longitude_name").item(0).toElement().firstChild().toText().data();
		if(!longitude_name.isNull()) ds->setLongitudeDataName(longitude_name);

		QString latitude_name = datasource.elementsByTagName("latitude_name").item(0).toElement().firstChild().toText().data();
		if(!latitude_name.isNull()) ds->setLatitudeDataName(latitude_name);

		QString data_name = datasource.elementsByTagName("data_name").item(0).toElement().firstChild().toText().data();
		if(!data_name.isNull()) ds->setDataName(data_name);

		QString base_h_res = datasource.elementsByTagName("base_h_res").item(0).toElement().firstChild().toText().data();
		if(!base_h_res.isNull()) ds->setBaseHResolution(base_h_res.toInt());

		QString bottom_offset = datasource.elementsByTagName("bottom_offset").item(0).toElement().firstChild().toText().data();
		if(!bottom_offset.isNull()) ds->setBottomOffset(bottom_offset.toInt());

		QString max_altitude = datasource.elementsByTagName("max_altitude").item(0).toElement().firstChild().toText().data();
		if(!max_altitude.isNull()) ds->setMaxAltitude(max_altitude.toInt());

		QString inverted = datasource.elementsByTagName("inverted").item(0).toElement().firstChild().toText().data();
		if(!inverted.isNull()) ds->setInverted((inverted == "true") ? true : false);
		return true;
	} else {
		return false;
	}
}

