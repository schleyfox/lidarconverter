#include "colormapwidget.h"

ColorMapWidget::ColorMapWidget(QWidget* parent) :
       	QTableWidget(parent) {
	
	setColumnCount(2);
	setHorizontalHeaderLabels(QStringList() 
				<< "Base Value" << "ARGB Color");
	connect(this, SIGNAL(cellChanged(int,int)),
		       	this, SLOT(colorCell(int,int)));
	num_colors = 1024;


}

QMap<float, uint> ColorMapWidget::toMap() {
	QMap<float, uint> colors;

	for(int i = 0; i < rowCount(); i++) {
		if(item(i,0) && item(i,1)) {
			float val = item(i, 0)->text().toFloat();
			uint color = item(i, 1)->text().toUInt(0,16);
			colors[val] = color;
		}
	}

	return colors;
}



void ColorMapWidget::fromMap(QMap<float, uint> map) {
	QMapIterator<float, uint> i(map);

	for(int k = 0; k < rowCount(); k++) {
		removeRow();
	}

	int j = 0;
	while(i.hasNext()) {
		i.next();
		if(!item(j, 0) || !item(j, 1)) {
			QTableWidget::insertRow(j);
			setItem(j, 0, new QTableWidgetItem);
			setItem(j, 1, new QTableWidgetItem);
		}
		item(j, 0)->setText(QString::number(i.key()));
		item(j, 1)->setText(QString::number(i.value(),16));
		colorCell(j, 1);
		j++;
	}
}

//FIXME: This is broken
QMap<float, uint> ColorMapWidget::toBlendedMap() {
	QMap<float, uint> map = toMap();
	QMap<float, uint> cm;
	
	QList<float> ranges = map.keys();
	QList<uint> colors = map.values();

	int div = (int)floor((double)num_colors/(double)map.size());

	int start = 0;
	int upto = 0;
	for(int i = 0; i < map.size()-1; i++) {
		start += upto;
		upto += div;
		for(int j = start; j < upto; j++) {
			double frac = (double)(j-start)/(double)(upto-start);
			float val = ranges.at(i)*(1-frac) + 
				ranges.at(i+1)*frac;
			QColor c1(colors.at(i));
			QColor c2(colors.at(i+1));
			uint color = qRgba(
					c1.red()*(1-frac)+c2.red()*frac,
					c1.green()*(1-frac)+c2.green()*frac,
					c1.blue()*(1-frac)+c2.blue()*frac,
					c1.alpha()*(1-frac)+c2.alpha()*frac);
			cm[val] = color;
		}
	}
	return cm;
}

QString ColorMapWidget::toXml() {
	QMap<float, uint> colors = toMap();
	QMapIterator<float, uint> i(colors);
	
	QDomDocument doc;
	QDomElement root = doc.createElement("colormap");
	doc.appendChild(root);
	
	while(i.hasNext()) {
		i.next();
		QDomElement layer = doc.createElement("color_range");
		root.appendChild(layer);

		QDomElement base_val = doc.createElement("base_value");
		QDomText val = doc.createTextNode(QString::number(i.key()));
		QDomElement color = doc.createElement("color");
		QDomText c = doc.createTextNode(QString::number(i.value(),16));
		layer.appendChild(base_val);
		base_val.appendChild(val);
		layer.appendChild(color);
		color.appendChild(c);
	}

	return doc.toString();
}

void ColorMapWidget::colorCell(int row, int column) {
	if(column == 1) {
		QTableWidgetItem* i = item(row,column);
		if(i) {
			i->setBackground( QBrush( QColor(
				i->text().toUInt(0,16))));
		}
	}
}

void ColorMapWidget::findColorForCell() {
	if(currentColumn() == 1) {
		int row = currentRow();
		QTableWidgetItem* i = item(row, 1);
		if(i) {
			uint color = QColorDialog::getRgba();
			i->setText(QString::number(color, 16));
			colorCell(row, 1);
			return;
		}
	}
	QMessageBox::warning(this, "No Cell Selected", "Please select a cell from the \"Color RGBA\" column and then try to set the color");
}
