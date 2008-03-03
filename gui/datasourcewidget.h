#ifndef DATASOURCEWIDGET_H
#define DATASOURCEWIDGET_H

class DataSourceWidget : public QWidget {
	Q_OBJECT
	public:
	DataSourceWidget(QString filename = "", QWidget* parent = 0); 
	
	DynamicDataSource* toDataSource();
	QString toXml();

	public slots:
	void import(QString filename);
	void import();
	void save(QString filename);
	void save();


	protected:
	DynamicDataSource* ds;
	ResolutionMapWidget* resmap;
	QLabel* base_horiz_label, max_alt_label, offset_label, hdf_label,
		lat_label, lon_label, data_label;
	QSpin* base_horiz_spin, max_alt_spin, offset_spin;
	QLineEdit* lat_line, lon_line, data_line;
	QCheckBox* invert_box;
	QPushButton* import_button, QPushButton* save_button;

};
#endif

