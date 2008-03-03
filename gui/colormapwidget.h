#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

class ColorMapWidget : public QTableWidget {
	public:
	ColorMapWidget(QWidget* parent = 0);

	QMap<double, uint> toMap();
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

class ColorMapDelegate : public QItemDelegate {
	public:
	ColorMapWidgetDelegate(QObject* parent = 0) :  QItemDelegate(parent) {
	}

	QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

class ColorMapEditor : public QWidget {
	ColorMapEditor(QWidget* parent) : QWidget(parent) {
	}
};

#endif
