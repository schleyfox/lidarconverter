#ifndef RESOLUTIONMAPWIDGET_H
#define RESOLUTIONMAPWIDGET_H

class ResolutionMapWidget : public QTableWidget {
	public:
	ResolutionMapWidget(QWidget* parent = 0);

	QMap<int, int> toMap();
	void fromMap(QMap<int, int> map);
	
	QString toXml();

	public slots:
	void insertRow() {
		insertRow(rowCount());
	}
	void removeRow() {
		removeRow(rowCount()-1);
	}
};

#endif
