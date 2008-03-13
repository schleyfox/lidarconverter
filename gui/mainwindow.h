#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "lidarprojectwidget.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
	MainWindow();

	private slots:
	void save();
	void saveAs();
	void saveDataSource();
	void saveColorMap();

	void open();
	void importDataSource();
	void importColorMap();

	void about();

	private:
	LidarProjectWidget* lidar_project;
	QMenu* file_menu;
	QMenu* help_menu;
	
	QAction* save_action;
	QAction* saveAs_action;
	QAction* saveDataSource_action;
	QAction* saveColorMap_action;
	QAction* open_action;
	QAction* importDataSource_action;
	QAction* importColorMap_action;
	QAction* about_action;
};
#endif
