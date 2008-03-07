#include "colormapbox.h"

ColorMapBox::ColorMapBox(QWidget* parent) : QGroupBox(parent) {
	setTitle("Color Map");
	colormap = new ColorMapWidget();
	QVBoxLayout* root = new QVBoxLayout;
	root->addWidget(colormap);
	QHBoxLayout* buttons = new QHBoxLayout;
	add_button = new QPushButton("Add");
	remove_button = new QPushButton("Remove");
	findcolor_button = new QPushButton("Find Color");
	buttons->addWidget(findcolor_button);
	buttons->addStretch();
	buttons->addWidget(add_button);
	buttons->addWidget(remove_button);
	root->addLayout(buttons);
	QObject::connect(findcolor_button, SIGNAL(clicked()), 
			colormap, SLOT(findColorForCell()));
	QObject::connect(add_button, SIGNAL(clicked()),
		       	colormap, SLOT(insertRow()));
	QObject::connect(remove_button, SIGNAL(clicked()),
		       	colormap, SLOT(removeRow()));
	setLayout(root);
}
