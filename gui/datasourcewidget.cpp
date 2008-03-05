#include "datasourcewidget.h"
#include "configfileparser.h"
DataSourceWidget::DataSourceWidget(QString filename, QWidget* parent) : 
	QWidget(parent) {

		import(filename);
	

	//Oh huzzay, widget layout
	QVBoxLayout* root_layout = new QVBoxLayout;
	 QHBoxLayout* top_layout = new QHBoxLayout;
	  resmap = new ResolutionMapWidget(this);
	  top_layout->addWidget(resmap);
	  QVBoxLayout* res_layout = new QVBoxLayout;
	   QHBoxLayout* base_horiz_layout = new QHBoxLayout;
	    base_horiz_label = 
		new QLabel("Base Horizontal Resolution (m)",this);
	    base_horiz_spin = new QSpinBox(this);
	    base_horiz_layout->addWidget(base_horiz_label);
	    base_horiz_layout->addWidget(base_horiz_spin);
	   res_layout->addLayout(base_horiz_layout);
	   QHBoxLayout* max_alt_layout = new QHBoxLayout;
	    max_alt_label = 
		    new QLabel("Maximum Altitude (m)", this);
	    max_alt_spin = new QSpinBox(this);
	    max_alt_layout->addWidget(max_alt_label);
	    max_alt_layout->addWidget(max_alt_spin);
	   res_layout->addLayout(max_alt_layout);
	   QHBoxLayout* offset_layout = new QHBoxLayout;
	    offset_label = new QLabel("Offset (bins)", this);
	    offset_spin = new QSpinBox(this);
	    offset_layout->addWidget(offset_label);
	    offset_layout->addWidget(offset_spin);
	   res_layout->addLayout(offset_layout);
	   invert_box = new QCheckBox("Invert", this);
	   res_layout->addWidget(invert_box);
	  top_layout->addLayout(res_layout);
	 root_layout->addLayout(top_layout);
	 QVBoxLayout* bottom_layout = new QVBoxLayout;
	  QVBoxLayout* hdf_layout = new QVBoxLayout;
	   hdf_label = new QLabel("Enter the HDF data set names that correspond to each field", this);
	   hdf_layout->addWidget(hdf_label);
	   QHBoxLayout* field_layout = new QHBoxLayout;
	    lat_label = new QLabel("Latitude",this);
	    lat_line = new QLineEdit(this);
	    lon_label = new QLabel("Longitude",this);
	    lon_line = new QLineEdit(this);
	    data_label = new QLabel("Data", this);
	    data_line = new QLineEdit(this);
	    field_layout->addWidget(lat_label);
	    field_layout->addWidget(lat_line);
	    field_layout->addStretch();
	    field_layout->addWidget(lon_label);
	    field_layout->addWidget(lon_line);
	    field_layout->addStretch();
	    field_layout->addWidget(data_label);
	    field_layout->addWidget(data_line);
	   hdf_layout->addLayout(field_layout);
	  bottom_layout->addLayout(hdf_layout);
	  bottom_layout->addStretch();
	  QHBoxLayout* import_save_layout = new QHBoxLayout;
	   import_button = new QPushButton("Import", this);
	   save_button = new QPushButton("Save", this);
	   import_save_layout->addWidget(import_button);
	   import_save_layout->addStretch();
	   import_save_layout->addWidget(save_button);
	 bottom_layout->addLayout(import_save_layout);
	root_layout->addLayout(bottom_layout);
	setLayout(root_layout);

	connect(import_button, SIGNAL(clicked()), this, SLOT(import()));
	connect(save_button, SIGNAL(clicked()), this, SLOT(save()));

}

void DataSourceWidget::import(QString filename) {
	if(!filename.isEmpty()) {
		ConfigFileParser conf(this);
		conf.parseFile(filename);
	}
}

