#include <QApplication>
#include "datasourcewidget.h" 

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	DataSourceWidget* cm = new DataSourceWidget();
	cm->show();
	return app.exec();
}
