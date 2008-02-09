#include "datasourcetests.h"

void DataSourceTests::read() {
	DataSource* ds = new TestDataSource();
	ds->read();
	QVERIFY(ds->data().size() > 0);
	delete ds;
}

void DataSourceTests::segment() {
	DataSource* ds = new TestDataSource();
	ds->read();
	QVector<Segment> segments = ds->segment();
	QCOMPARE(segments.size(), 2);
	
	//write out sample kml
	Helper::makeKMLPath(ds->data(), "kml/full_swath.kml");
	Helper::makeKMLPath(segments.first(), "kml/jakarta_to_mecca.kml");
	Helper::makeKMLPath(segments.last(), "kml/mecca_to_izmir.kml");
	
	//Jakarta to Mecca	
	QVERIFY(segments.first().size() > 0);
	QCOMPARE((int)segments.first().heading().degs()*100,
		       	(int)Angle::Degrees(65.04).degs()*100); //fuck doubles

	//Mecca to Izmir
	QVERIFY(segments.last().size() > 0);
	QCOMPARE((int)segments.last().heading().degs()*100,
		       	(int)Angle::Degrees(29.5).degs()*100); //fuck doubles
}

