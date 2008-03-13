#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H
#include "gui_common.h"

class ColorMapWidget : public QTableWidget {
	Q_OBJECT
	public:
	ColorMapWidget(QWidget* parent = 0);

	QMap<float, uint> toMap();
	void fromMap(QMap<float, uint> map);

	QMap<float, uint> toBlendedMap();
	
	QString toXml();
	
	public slots:
	void colorCell(int row, int column);
	void findColorForCell();
	void import(QString filename);
	void import();
	void save(QString filename);
	void save();
	void insertRow() {
		QTableWidget::insertRow(rowCount());
	}
	void removeRow() {
		QTableWidget::removeRow(rowCount()-1);
	}
	protected:
	int num_colors;
	QString save_to_filename;
};

#endif
