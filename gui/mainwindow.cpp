#include "mainwindow.h"

MainWindow::MainWindow() {
	lidar_project = new LidarProjectWidget();
	setCentralWidget(lidar_project);

	save_action = new QAction("Save", this);
	save_action->setShortcut("Ctrl+S");
	connect(save_action, SIGNAL(triggered()), this, SLOT(save()));

	saveAs_action = new QAction("Save As", this);
	connect(saveAs_action, SIGNAL(triggered()), this, SLOT(saveAs()));

	saveDataSource_action = new QAction("Save Data Source", this);
	connect(saveDataSource_action, SIGNAL(triggered()), this, 
			SLOT(saveDataSource()));

	saveColorMap_action = new QAction("Save Color Map", this);
	connect(saveColorMap_action, SIGNAL(triggered()), this,
			SLOT(saveColorMap()));

	open_action = new QAction("Open", this);
	connect(open_action, SIGNAL(triggered()), this, SLOT(open()));

	importDataSource_action = new QAction("Import Data Source", this);
	connect(importDataSource_action, SIGNAL(triggered()), this,
			SLOT(importDataSource()));

	importColorMap_action = new QAction("Import Color Map", this);
	connect(importColorMap_action, SIGNAL(triggered()), this,
			SLOT(importColorMap()));

	about_action = new QAction("About Lidar Converter", this);
	connect(about_action, SIGNAL(triggered()), this, SLOT(about()));

	file_menu = menuBar()->addMenu("File");
	file_menu->addAction(open_action);
	file_menu->addAction(save_action);
	file_menu->addAction(saveAs_action);
	file_menu->addSeparator();
	file_menu->addAction(importDataSource_action);
	file_menu->addAction(saveDataSource_action);
	file_menu->addAction(importColorMap_action);
	file_menu->addAction(saveColorMap_action);

	menuBar()->addSeparator();

	help_menu = menuBar()->addMenu("Help");
	help_menu->addAction(about_action);

	setWindowIcon(QIcon(":/images/icon.png"));
}

void MainWindow::save() {
	lidar_project->save();
}

void MainWindow::saveAs() {
	QString fn = QFileDialog::getSaveFileName(this,
		"Save Lidar Project", "", "XML (*.xml)");
	fn->save(fn);
}

void MainWindow::open() {
	lidar_project->import();
}

void MainWindow::saveDataSource() {
	lidar_project->dataSourceWidget()->save();
}

void MainWindow::importDataSource() {
	lidar_project->dataSourceWidget()->import();
}

void MainWindow::saveColorMap() {
	lidar_project->colorMapWidget()->save();
}

void MainWindow::importColorMap() {
	lidar_project->colorMapWidget()->import();
}

void MainWindow::about() {
	QMessageBox::information(this, "About Lidar Converter",
			"Written by: Ben Hughes and Nelson Hillyer for the \
			DEVELOP National Program");
}
