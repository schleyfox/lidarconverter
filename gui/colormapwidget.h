#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

class ColorMapWidget : public QTableWidget {
	public:
	ColorMapWidget(QWidget* parent = 0);

	QMap<double, uint> toMap();
	void fromMap(QMap<double, uint> map);
	
	QString toXml();
	
	public slots:
	void colorCell(int row, int column);
	void findColorForCell();
	void insertRow() {
		insertRow(rowCount());
	}
	void removeRow() {
		removeRow(rowCount()-1);
	}
};

#endif
