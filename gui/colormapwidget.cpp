#include "colormapwidget.h"

ColorMapWidget::ColorMapWidget(QWidget* parent = 0) :
       	QTableWidget(parent) {
	
	setColumnCount(2);
	setHorizontalHeaderLabels(QStringList() 
				<< "Base Value" << "RGBA Color");
	connect(this, SIGNAL(cellChanged(int,int)), this, colorCell(int,int));


}

QMap<double, uint> ColorMapWidget::toMap() {
	QMap<double, uint> colors;

	for(int i = 0; i < rowCount(); i++) {
		int val = item(i, 0)->text().toDouble();
		int color = item(i, 1)->text().toUInt(0,16);
		color[val] = color;
	}

	return colors;
}



void ColorMapWidget::fromMap(QMap<double, uint> map) {
	QMapIterator<double, uint> i(map);
	clearContents();

	int j = 0;
	while(i.hasNext()) {
		i.next();
		item(j, 0)->setText(QString::number(i.key()));
		item(j, 1)->setText(QString::number(i.value(),16));
		colorCell(j, 1);
		j++;
	}
}

QString ColorMapWidget::toXml() {
	QMap<double, uint> colors = toMap();
	QMapIterator<double, uint> i(colors);
	
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
		base_alt.appendChild(val);
		layer.appendChild(color);
		v_res.appendChild(c);
	}

	return doc.toString();
}

void ColorMapWidget::colorCell(int row, int column) {
	if(column == 1) {
		QTableWidgetItem* i = item(row,column);
		if(i) {
			i->setBackground( QBrush( QColor(
				i->text().toUint(0,16))));
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


		

