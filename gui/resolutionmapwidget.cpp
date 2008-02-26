#include "resolutionmapwidget.h"

ResolutionMapWidget::ResolutionMapWidget(QWidget* parent = 0) :
       	QTableWidget(parent) {
		setColumnCount(2);
		setHorizontalHeaderLabels(QStringList() 
				<< "Base Altitude" << "Vertical Resolution");
}

QMap<int, int> ResolutionMapWidget::toMap() {
	QMap<int, int> resolutions;
	
	for(int i = 0; i < rowCount(); i++) {
		int alt = item(i, 0)->text().toInt();
		int res = item(i, 1)->text().toInt();
		resolutions[alt] = res;
	}

	return resolutions;
}

void ResolutionMapWidget::fromMap(QMap<int, int> map) {
	QMapIterator<int, int> i(map);
	clearContents();

	int j = 0;
	while(i.hasNext()) {
		i.next();
		item(j, 0)->setText(QString::number(i.key()));
		item(j, 1)->setText(QString::number(i.value()));
		j++;
	}
}


QString ResolutionMapWidget::toXml() {
	QMap<int, int> resolutions = toMap();
	QMapIterator<int, int> i(resolutions);
	
	QDomDocument doc;
	QDomElement root = doc.createElement("resolutions");
	doc.appendChild(root);
	
	while(i.hasNext()) {
		i.next();
		QDomElement layer = doc.createElement("layer");
		root.appendChild(layer);

		QDomElement base_alt = doc.createElement("base_altitude");
		QDomText alt = doc.createTextNode(QString::number(i.key()));
		QDomElement v_res = doc.createElement("vertical_resolution");
		QDomText res = doc.createTextNode(QString::number(i.value()));
		layer.appendChild(base_alt);
		base_alt.appendChild(alt);
		layer.appendChild(v_res);
		v_res.appendChild(res);
	}

	return doc.toString();
}

void ResolutionMapWidget::fromXml(QString xml) {
	QMap<int, int> resolutions;
	
	QDomDocument doc;
	doc.setContent(xml);
	QDomElement root = doc.documentElement();
	if(root.tagName() != "resolutions")
		return;

	QDomNode node = root.firstChild();
	while(!node.isNull()) {
		if(node.toElement().tagName() == "layer") {
			QPair<int, int> pair;
			QDomNode subnode = node.toElement().firstChild();
			while(!subnode.isNull) {
				QDomNode childnode = subnode.firstChild();
				if(subnode.toElement().tagName() == 
						"base_altitude" && 
						childnode.isText()) {
					pair.first = childNode.toText().
						data().toInt();
				} else if(subnode.toElement().tagName() ==
						"vertical_resolution" &&
						childnode.isText()) {
					pair.second = childNode.toText().
						data.toInt();
				}
				subnode = subnode.nextSibling();
			}
			resolutions[pair.first] = pair.second;
		}
		node = node.nextSibling();
	}

	fromMap(resolutions);
}

