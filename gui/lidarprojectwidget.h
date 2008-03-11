#ifndef LIDARPROJECTWIDGET_H
#define LIDARPROJECTWIDGET_H
#include "gui_common.h"

class LidarProjectWidget : public QWidget {
	public:
	LidarProjectWidget(QWidget* parent = 0);

	QString toXml();
	DataSourceWidget* dataSourceWidget() {
		return datasource;
	}
	ColorMapWidget* colorMapWidget() {
		return colormapbox->colorMap();
	}

	public slots:
	void addFile();
	void removeFile();
	void save();
	void save(QString filename);

	void import();
	void import(QString filename);

	void toKml();
	void toKml(QString output_dir);
	void launchGoogleEarth();

	protected:
	DataSourceWidget* datasource;
	ColorMapBox* colormapbox;
	QListWidget* filelist;
	QPushButton *tokml_button, *launchge_button, *addfile_button, 
		    *removefile_button;
	QProcess* googleearth;

	QString save_to_filename;
};
#endif


