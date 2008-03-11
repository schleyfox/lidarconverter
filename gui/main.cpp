#include <QApplication>
#include "lidarprojectwidget.h" 

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	
	LidarProjectWidget* w = new LidarProjectWidget();
	w->show();
	return app.exec();
}
