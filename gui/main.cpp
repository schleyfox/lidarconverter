#include <QApplication>
#include "lidarprojectwidget.h" 
#include "configfileparser.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	ConfigFileParser p;
	p.readFile("calipso_colormap.xml");
	LidarProjectWidget* w = new LidarProjectWidget();
	p.parseColorMap(w->colorMapWidget());
	w->show();
	return app.exec();
}
