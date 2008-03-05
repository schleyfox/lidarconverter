#ifndef RESOLUTIONMAPWIDGET_H
#define RESOLUTIONMAPWIDGET_H
#include "gui_common.h"


class ResolutionMapWidget : public QTableWidget {
	Q_OBJECT
	public:
	ResolutionMapWidget(QWidget* parent = 0);

	QMap<int, int> toMap();
	void fromMap(QMap<int, int> map);
	
	QString toXml();

	public slots:
	void insertRow() {
		QTableWidget::insertRow(rowCount());
	}
	void removeRow() {
		QTableWidget::removeRow(rowCount()-1);
	}
};

#endif
