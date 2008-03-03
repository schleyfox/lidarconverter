#include "colormapwidget.h"

ResolutionMapWidget::ResolutionMapWidget(QWidget* parent = 0) :
       	QTableWidget(parent) {
		setColumnCount(2);
		setHorizontalHeaderLabels(QStringList() 
				<< "Base Value" << "Color");
}



