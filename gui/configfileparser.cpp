#include "configfileparser.h"

ConfigFileParser::ConfigFileParser(DataSourceWidget* ds, ResolutionMapWidget* rm
		,ColorMapWidget* cm) {
	datasource = ds;
	resmap = rm;
	colormap = cm;
	doc = 0;
}

bool ConfigFileParser::parse(QString xml) {
	if(doc)
		delete doc;

	doc = new QDomDocument();
	doc->setContent(xml);
	QDomElement root = doc->documentElement();

	if(root.tagName() == "lidar_project") {
		if(!parseLidarProject(root))
			return false;
	} else if(root.tagName() == "datasource") {
		if(!parseDataSource(root))
			return false;
	} else if(root.tagName() == "colormap") {
		if(!parseColorMap(root))
			return false;
	} else if(root.tagName() == "resolutions") {
		if(!parseResolutions(root))
			return false;
	}

	return true;
}

bool ConfigFileParser::parseLidarProject(QDomNode node) {
	QDomNodeList children = node.childNodes();
	for(int i = 0; i < children.size(); i++) {
		QDomElement child = children.at(i).toElement();
		if(child.tagName() == "datasource") {
			if(!parseDataSource(children.at(i)))
				return false;
		} else if(child.tagName() == "colormap") {
			if(!parseColorMap(children.at(i)))
				return false;
		} else if(child.tagName() == "resolutions") {
			if(!parseResolutions(children.at(i)))
				return false;
		}
	}
	return true;
}

bool ConfigFileParser::parseDataSource(QDomNode node) {
	QDomNodeList children = node.childNodes();
	for(int i = 0; i < children.size(); i++) {
		QDomNode txt = children.at(i).firstChild();
		QDomElement child = children.at(i).toElement();
		if(child.tagName() == "resolutions") {
			if(!parseResolutions(children.at(i)))
				return false;
		} else if(!txt.isNull() && txt.isText() && datasource) {
			QString str = txt.toText().data();
			if(child.tagName() == "bottom_offset") {
				datasource->setBottomOffset(str.toInt());
		    	} else if(child.tagName() == "max_altitude") {
				datasource->setMaxAltitude(str.toInt());
			} else if(child.tagName() == "data_name") {
				datasource->setDataName(str);
			} else if(child.tagName() == "longitude_name") {
				datasource->setLongitudeDataName(str);
			} else if(child.tagName() == "latitude_name") {
				datasource->setLatitudeDataName(str);
			} else if(child.tagName() == "base_h_res") {
				datasource->setBaseHResolution(str.toInt());
			} else if(child.tagName() == "inverted") {
				datasource->setInverted(
					(str == "true") ? true : false);
			}
		}
	}
	return true;
}

bool ConfigFileParser::parseResolutions(QDomNode node) {
	if(!resmap) 
		return true;

	QDomNodeList children = node.childNodes();
	QMap<int, int> resolutions;
	for(int i = 0; i < children.size(); i++) {
		QDomNode child = children.at(i);
		QDomElement child_elem = child.toElement();
		if(child_elem.tagName() == "layer") {
			QDomNodeList subchildren = child.childNodes();
			QPair<int, int> key_val;
			for(int j = 0; j < subchildren.size(); j++) {
				QDomNode subchild = subchildren.at(i);
				QDomNode txt = subchild.firstChild();
				QDomElement subchild_elem = 
					subchild.toElement();
				if(!txt.isText()) {
					return false;
				}
				int str = txt.toText().data().toInt();
				if(subchild_elem.tagName() == "base_altitude") {
					key_val.first = str;
				} else if(subchild_elem.tagName() == 
						"vertical_resolution") {
					key_val.second = str;
				}
			}
			resolutions[key_val.first] = key_val.second;
		}
	}
	resmap->fromMap(resolutions);
	return true;
}
			
bool ConfigFileParser::parseColorMap(QDomNode node) {
	if(!colormap) 
		return true;

	QDomNodeList children = node.childNodes();
	QMap<double, uint> colors;
	for(int i = 0; i < children.size(); i++) {
		QDomNode child = children.at(i);
		QDomElement child_elem = child.toElement();
		if(child_elem.tagName() == "colorrange") {
			QDomNodeList subchildren = child.childNodes();
			QPair<double, uint> key_val;
			for(int j = 0; j < subchildren.size(); j++) {
				QDomNode subchild = subchildren.at(i);
				QDomNode txt = subchild.firstChild();
				QDomElement subchild_elem = 
					subchild.toElement();
				if(!txt.isText()) {
					return false;
				}
				QString str = txt.toText().data();
				if(subchild_elem.tagName() == "base_value") {
					key_val.first = str.toDouble();
				} else if(subchild_elem.tagName() == 
						"color") {
					key_val.second = str.toUInt();
				}
			}
			colors[key_val.first] = key_val.second;
		}
	}
	colormap->fromMap(colors);
	return true;
}

bool ConfigFileParser::parseFile(QString fn) {
	QFile file(fn);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QTextStream in(&file);
	return parse(in.readAll());
}
