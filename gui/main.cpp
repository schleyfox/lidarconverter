#include <QApplication>
#include "colormapwidget.h" 
#include "datasourcewidget.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	

	QWidget* w = new QWidget();
	QHBoxLayout* z = new QHBoxLayout;
	DataSourceWidget* ds = new DataSourceWidget();
	z->addWidget(ds); z->addLayout(a);
	w->setLayout(z);
	w->show();
	return app.exec();
}
