#ifndef COLORMAPBOX_H
#define COLORMAPBOX_H

class ColorMapBox : public QGroupBox {
	public:
	ColorMapBox(QWidget* parent = 0);
	protected:
	ColorMapWidget* colormap;
	QPushButton *add_button, *remove_button, *findcolor_button;

};
#endif


