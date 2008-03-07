#ifndef COLORMAPBOX_H
#define COLORMAPBOX_H
#include "gui_common.h"
#include "colormapwidget.h"

class ColorMapBox : public QGroupBox {
	public:
	ColorMapBox(QWidget* parent = 0);

	ColorMapWidget* colorMap() {
		return colormap;
	}
	protected:
	ColorMapWidget* colormap;
	QPushButton *add_button, *remove_button, *findcolor_button;

};
#endif


