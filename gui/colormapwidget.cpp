#include "colormapwidget.h"
#include "configfileparser.h"

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

//FIXME: This is broken, lulz
QMap<float, uint> ColorMapWidget::toBlendedMap() {
	QMap<float, uint> map = toMap();
	QMap<float, uint> cm;
	
	QList<float> dataRange = map.keys();
	QList<uint> colors = map.values();
	QList<QColor> colors2;
	QList<float> r,g,b,a;
	for(int i = 0; i < colors.size(); i++) {
		colors2 << QColor(colors.at(i));
		r << (double)colors2.at(i).red()/255.0;
		g << (double)colors2.at(i).green()/255.0;
		b << (double)colors2.at(i).blue()/255.0;
		a << (double)colors2.at(i).alpha()/255.0;
	}
	//From code written by Jonathan Gleason
	//This code survives every revision even though it isn't particularly
	//elegant or fitting for the style of code.  Its major advantage is
	//that it works.
	int numColors = num_colors;
	int numRanges = map.size()-1;

	double dataValue;
	int *rangeIndex = new int[numColors];
	int *rangeIndexRunningSum = new int[numColors];
	int *rangeIndexSum = new int[numRanges];
	int indexPtr = 0;
	for(int i = 0; i < numRanges; i++)
		rangeIndexSum[i] = 0;

	for(int i = 0; i < numColors; i++)
	{
		dataValue = dataRange[0] + ((double)i)/((double)(numColors-1))
			*(dataRange[numRanges] - dataRange[0]);
		while (dataValue > dataRange[indexPtr+1])
			indexPtr++;
		rangeIndex[i] = indexPtr;
		rangeIndexSum[indexPtr] += 1; 
		rangeIndexRunningSum[i] = rangeIndexSum[indexPtr];
	}
	
	
	double red, green, blue, alpha, range;
	double f;	
	for(int i = 0; i < numColors; i++)	
	{
		f = (double)rangeIndexRunningSum[i] / 
			((double)rangeIndexSum[rangeIndex[i]]);
		range = dataRange[rangeIndex[i]]*(1-f) + 
			dataRange[rangeIndex[i]+1]*f;
		red   = r[rangeIndex[i]]*(1-f) + r[rangeIndex[i]+1]*f;
		green = g[rangeIndex[i]]*(1-f) + g[rangeIndex[i]+1]*f;
		blue  = b[rangeIndex[i]]*(1-f) + b[rangeIndex[i]+1]*f;
		alpha = a[rangeIndex[i]]*(1-f) + a[rangeIndex[i]+1]*f;
		cm[range] = qRgba(red*255, green*255, blue*255, alpha*255);
	}
	qDebug() << "Blended Colors: " << cm.size();
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

void ColorMapWidget::import() {
	QString filename = QFileDialog::getOpenFileName(this,
				"Import Color Map from File", "",
			       	"XML (*.xml)");
	import(filename);
}
void ColorMapWidget::import(QString filename) {
	if(!filename.isEmpty()) {
		ConfigFileParser conf;
		conf.readFile(filename);
		conf.parseColorMap(this);
	}
}

void ColorMapWidget::save() {
	if(save_to_filename.isEmpty()) {
		save_to_filename = QFileDialog::getSaveFileName(this,
				"Save Color Map", "",
				"XML (*.xml)");
	}
	save(save_to_filename);
}

void ColorMapWidget::save(QString filename) {
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&file);
		out << toXml();
	}
}
