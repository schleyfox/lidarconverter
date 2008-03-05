#include <QApplication>
#include "colormapwidget.h" 

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	ColorMapWidget* cm = new ColorMapWidget();
	QVBoxLayout* a = new QVBoxLayout;
	a->addWidget(cm);
	QHBoxLayout* b = new QHBoxLayout;
	QPushButton *c, *d;
	c = new QPushButton("Add");
	d = new QPushButton("Remove");
	b->addStretch();
	b->addWidget(c);
	b->addWidget(d);
	a->addLayout(b);
	QObject::connect(c, SIGNAL(clicked()), cm, SLOT(insertRow()));
	QWidget* w = new QWidget();
	w->setLayout(a);
	w->show();
	return app.exec();
}
