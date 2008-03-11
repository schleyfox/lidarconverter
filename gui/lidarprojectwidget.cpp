#include "lidarprojectwidget.h"

LidarProjectWidget::LidarProjectWidget(QWidget* parent) : QWidget(parent) {
	QHBoxLayout* root_layout = new QHBoxLayout;
	 QVBoxLayout* right_layout = new QVBoxLayout;
	  QHBoxLayout* main_project_layout = new QHBoxLayout;
	   QVBoxLayout* project_layout = new QVBoxLayout;
	    filelist = new QListWidget(this);
	    project_layout->addWidget(filelist);
	    QHBoxLayout* project_button_layout = new QHBoxLayout;
	     addfile_button = new QPushButton("Add File", this);
	     removefile_button = new QPushButton("Remove File", this);
	     project_button_layout->addStretch();
	     project_button_layout->addWidget(addfile_button);
	     project_button_layout->addWidget(removefile_button);
	    project_layout->addLayout(project_button_layout);
	   main_project_layout->addLayout(project_layout);
	   QVBoxLayout* kml_layout = new QVBoxLayout;
	    tokml_button = new QPushButton("Export KML", this);
	    launchge_button = new QPushButton("Launch Google Earth", this);
	    kml_layout->addWidget(tokml_button);
	    kml_layout->addWidget(launchge_button);
	   main_project_layout->addLayout(kml_layout);
	  right_layout->addLayout(main_project_layout);
	  datasource = new DataSourceWidget();
	  right_layout->addWidget(datasource);
	  colormapbox = new ColorMapBox();
	  root_layout->addLayout(right_layout);
	  root_layout->addWidget(colormapbox);

	 googleearth = new QProcess(this);

	 setLayout(root_layout);
	 connect(tokml_button, SIGNAL(clicked()), this, SLOT(toKml()));
	 connect(launchge_button, SIGNAL(clicked()), this, 
			 SLOT(launchGoogleEarth()));
	 connect(addfile_button, SIGNAL(clicked()), this, SLOT(addFile()));
	 connect(removefile_button, SIGNAL(clicked()), this,
			 SLOT(removeFile()));
	 save_to_filename = "";
}

QString LidarProjectWidget::toXml() {
	QDomDocument doc;
	QDomElement root = doc.createElement("lidar_project");
	doc.appendChild(root);

	QDomDocument datasource_doc;
	datasource_doc.setContent(dataSourceWidget()->toXml());
	root.appendChild(datasource_doc.documentElement());
	
	QDomDocument colormap_doc;
	colormap_doc.setContent(colorMapWidget()->toXml());
	root.appendChild(colormap_doc.documentElement());

	return doc.toString();
}

void LidarProjectWidget::import() {
	QString filename = QFileDialog::getOpenFileName(this,
				"Import Lidar Project from File", "",
			       	"XML (*.xml)");
	import(filename);
}
void LidarProjectWidget::import(QString filename) {
	if(!filename.isEmpty()) {
		ConfigFileParser conf;
		conf.readFile(filename);
		conf.parseDataSource(dataSourceWidget());
		conf.parseColorMap(colorMapWidget());
	}
}


void LidarProjectWidget::save() {
	if(save_to_filename.isEmpty()) {
		save_to_filename = QFileDialog::getSaveFileName(this,
				"Save Lidar Project", "",
				"XML (*.xml)");
	}
	save(save_to_filename);
}

void LidarProjectWidget::save(QString filename) {
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&file);
		out << toXml();
	}
}

void LidarProjectWidget::addFile() {
	filelist->addItems(QFileDialog::getOpenFileNames(this,
				"Load HDF Files", "", "HDF (*.hdf)"));
}

void LidarProjectWidget::removeFile() {
	filelist->takeItem(filelist->count()-1);
}

void LidarProjectWidget::toKml() {
	toKml(QFileDialog::getExistingDirectory(this, "Select directory to save KML files to", ""));
}

void LidarProjectWidget::toKml(QString output_dir) {
	QDir out(output_dir);
	int thread_count = QThread::idealThreadCount();
	QProgressBar* progress = new QProgressBar(this);
	progress->setMaximum(filelist->count());
	progress->show();
	LColorLookup* lut = new LColorLookup();
	lut->setColorMap(colorMapWidget()->toMap());
	qDebug() << lut->colorMap().size();
	lut->compile();
	if(out.exists()) {
		QVector<Segment> all_segments;
		for(int i = 0; i < filelist->count(); i++) {
			DynamicDataSource* ds = 
				dataSourceWidget()->toDataSource();
			ds->setFilename(filelist->item(i)->text());
			ds->read();
			QVector<Segment> segments = ds->segment();
			all_segments += segments;
			QVector<SegmentWorker*> sw;
			sw.resize(thread_count);
			int div = (int)floor((double)segments.size()
					/(double)sw.size());
			QVectorIterator<Segment> x(segments);
			for(int i = 0; i < sw.size(); i++) {
				sw[i] = new SegmentWorker(lut);
				if(i == sw.size()-1)
					div = segments.size()-
						((sw.size()-1)*div);
				for(int j = 0; j < div; j++) {
					sw.at(i)->addSegment(x.next());
				}
				sw.at(i)->start();
			}
			while(true) {
				sleep(1);
				bool quit = true;
				for(int i = 0; i < sw.size(); i++) {
					if(sw.at(i)->isRunning())
						quit = false;
				}
				qDebug("Spinning");
				if(quit == true)
					break;
			}
			progress->setValue(progress->value() + 1);
		}
		KMLBuilder builder(out, QDir("./images"));
		builder.generateFiles(all_segments);
	}
	progress->hide();
	delete progress;
}

void LidarProjectWidget::launchGoogleEarth() {
	QString dir = QUuid::createUuid().toString();
	toKml(dir);
	if(googleearth->state() != QProcess::NotRunning) {
		googleearth->terminate();
	}
	googleearth->start("googleearth", QStringList() << QDir(dir).absoluteFilePath("calipso.kml"));
}


