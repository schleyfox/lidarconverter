#include "datasourcewidget.h"
#include "configfileparser.h"
#define MAX_SPIN 999999

DataSourceWidget::DataSourceWidget(QString filename, QWidget* parent) : 
	QGroupBox(parent) {

	setTitle("Data Source");	

	//Oh huzzay, widget layout
	QVBoxLayout* root_layout = new QVBoxLayout;
	 QHBoxLayout* top_layout = new QHBoxLayout;
	  QVBoxLayout* resmap_layout = new QVBoxLayout;
	   resmap = new ResolutionMapWidget(this);
	   resmap_layout->addWidget(resmap);
	   QHBoxLayout* resmap_buttons_layout = new QHBoxLayout;
	    QPushButton* addrow_button = new QPushButton("Add");
	    QPushButton* remrow_button = new QPushButton("Remove");
	    resmap_buttons_layout->addStretch();
	    resmap_buttons_layout->addWidget(addrow_button);
	    resmap_buttons_layout->addWidget(remrow_button);
	   resmap_layout->addLayout(resmap_buttons_layout);
	  top_layout->addLayout(resmap_layout);
	  QVBoxLayout* res_layout = new QVBoxLayout;
	   QHBoxLayout* base_horiz_layout = new QHBoxLayout;
	    base_horiz_label = 
		new QLabel("Base Horizontal Resolution (m)",this);
	    base_horiz_spin = new QSpinBox(this);
	    base_horiz_spin->setMaximum(MAX_SPIN);
	    base_horiz_layout->addWidget(base_horiz_label);
	    base_horiz_layout->addWidget(base_horiz_spin);
	   res_layout->addLayout(base_horiz_layout);
	   QHBoxLayout* max_alt_layout = new QHBoxLayout;
	    max_alt_label = 
		    new QLabel("Maximum Altitude (m)", this);
	    max_alt_spin = new QSpinBox(this);
	    max_alt_spin->setMaximum(MAX_SPIN);
	    max_alt_layout->addWidget(max_alt_label);
	    max_alt_layout->addWidget(max_alt_spin);
	   res_layout->addLayout(max_alt_layout);
	   QHBoxLayout* offset_layout = new QHBoxLayout;
	    offset_label = new QLabel("Offset (bins)", this);
	    offset_spin = new QSpinBox(this);
	    offset_spin->setMaximum(MAX_SPIN);
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
	connect(addrow_button, SIGNAL(clicked()), resmap, SLOT(insertRow()));
	connect(remrow_button, SIGNAL(clicked()), resmap, SLOT(removeRow()));


	import(filename);
}

QString DataSourceWidget::toXml() {
	QDomDocument doc;
	QDomElement root = doc.createElement("datasource");
	doc.appendChild(root);

	QDomDocument resolutions;
	resolutions.setContent(resmap->toXml());
	root.appendChild(resolutions.documentElement());

	QDomElement longitude_name = doc.createElement("longitude_name");
	QDomText longitude_name_txt = doc.createTextNode(longitudeDataName());
	longitude_name.appendChild(longitude_name_txt);
	root.appendChild(longitude_name);

	QDomElement latitude_name = doc.createElement("latitude_name");
	QDomText latitude_name_txt = doc.createTextNode(latitudeDataName());
	latitude_name.appendChild(latitude_name_txt);
	root.appendChild(latitude_name);

	QDomElement data_name = doc.createElement("data_name");
	QDomText data_name_txt = doc.createTextNode(dataName());
	data_name.appendChild(data_name_txt);
	root.appendChild(data_name);

	QDomElement base_h_res = doc.createElement("base_h_res");
	QDomText base_h_res_txt = doc.createTextNode(QString::number(baseHResolution()));
	base_h_res.appendChild(base_h_res_txt);
	root.appendChild(base_h_res);

	QDomElement bottom_offset = doc.createElement("bottom_offset");
	QDomText bottom_offset_txt = doc.createTextNode(QString::number(bottomOffset()));
	bottom_offset.appendChild(bottom_offset_txt);
	root.appendChild(bottom_offset);

	QDomElement max_altitude = doc.createElement("max_altitude");
	QDomText max_altitude_txt = doc.createTextNode(QString::number(maxAltitude()));
	max_altitude.appendChild(max_altitude_txt);
	root.appendChild(max_altitude);


	QDomElement inverted1 = doc.createElement("inverted");
	QDomText inverted_txt = doc.createTextNode((inverted()) ? "true" : "false");
	inverted1.appendChild(inverted_txt);
	root.appendChild(inverted1);

	return doc.toString();
}

DynamicDataSource* DataSourceWidget::toDataSource() {
	DynamicDataSource* ds = new DynamicDataSource();
	ds->setResolutions(resolutions());
	ds->setLongitudeDataName(longitudeDataName());
	ds->setLatitudeDataName(latitudeDataName());
	ds->setDataName(dataName());
	ds->setMaxAltitude(maxAltitude());
	ds->setBaseHResolution(baseHResolution());
	ds->setBottomOffset(bottomOffset());
	ds->setInverted(inverted());

	return ds;
}

void DataSourceWidget::import() {
	QString filename = QFileDialog::getOpenFileName(this,
				"Import Data Source from File", "",
			       	"XML (*.xml)");
	import(filename);
}
void DataSourceWidget::import(QString filename) {
	if(!filename.isEmpty()) {
		ConfigFileParser conf;
		conf.readFile(filename);
		conf.parseDataSource(this);
	}
}

void DataSourceWidget::save() {
	if(save_to_filename.isEmpty()) {
		save_to_filename = QFileDialog::getSaveFileName(this,
				"Save Data Source", "",
				"XML (*.xml)");
	}
	save(save_to_filename);
}

void DataSourceWidget::save(QString filename) {
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&file);
		out << toXml();
	}
}
