#ifndef DATASOURCEWIDGET_H
#define DATASOURCEWIDGET_H
#include "gui_common.h"
#include "dynamicdatasource.h"
#include "resolutionmapwidget.h"

class DataSourceWidget : public QWidget {
	Q_OBJECT
	public:
	DataSourceWidget(QString filename = "", QWidget* parent = 0); 
	
	DynamicDataSource* toDataSource();
	QString toXml();
	
	//DynamicDataSource wrapping, getters
	QMap<int, int> resolutions() {
		return resmap->toMap();
	}
	QString longitudeDataName() {
		return lon_line->text();
	}
	QString latitudeDataName() {
		return lat_line->text();
	}
	QString dataName() {
		return data_line->text();
	}
	int maxAltitude() {
		return max_alt_spin->value();
	}
	int baseHResolution() {
		return base_horiz_spin->value();
	}
	int bottomOffset() {
		return offset_spin->value();
	}
	bool inverted() {
		return (invert_box->checkState() == Qt::Checked) ? true : false;
	}


	public slots:
	void import(QString filename);
	void import() {
	}
	void save(QString filename) {
	}
	void save() {
	}
	//DynamicDataSource wrapping, setters
	void setResolutions(QMap<int, int> resolutions) {
		resmap->fromMap(resolutions);
	}
	void setLongitudeDataName(QString longitudedataname){
		lon_line->setText(longitudedataname);
	}
	void setLatitudeDataName(QString latitudedataname){
		lat_line->setText(latitudedataname);
	}
	void setDataName(QString dataname){
		data_line->setText(dataname);
	}
	void setMaxAltitude(int maxaltitude) {
		max_alt_spin->setValue(maxaltitude);
	}
	void setBaseHResolution(int h_res) {
		base_horiz_spin->setValue(h_res);
	}
	void setBottomOffset(int offset) {
		offset_spin->setValue(offset);
	}
	void setInverted(bool invert) {
		invert_box->setCheckState((invert) ? Qt::Checked : Qt::Unchecked);
	}

	protected:
	DynamicDataSource* ds;
	ResolutionMapWidget* resmap;
	QLabel *base_horiz_label, *max_alt_label, *offset_label, *hdf_label,
		*lat_label, *lon_label, *data_label;
	QSpinBox *base_horiz_spin, *max_alt_spin, *offset_spin;
	QLineEdit *lat_line, *lon_line, *data_line;
	QCheckBox *invert_box;
	QPushButton *import_button, *save_button;

};
#endif

