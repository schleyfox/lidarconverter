#include <QtTest/QtTest>
#include "testdatasource.h"
#include "segment.h"

class DataSourceTests: public QObject {
	Q_OBJECT
	
	private slots:
	void read();
	void segment();
};

void DataSourceTests::read() {
	DataSource* ds = new TestDataSource();
	ds->read();
	QVERIFY(ds->data().size() > 0);
	delete ds;
}

void DataSourceTests::segment() {
	DataSource* ds = new TestDataSource();
	//ds->read();
	//QVector<Segment> segments = ds->segment();
	//QCOMPARE(segments.size(), 1);
	
	Segment s(ds);
	DataPoint* jakarta = new DataPoint();
	DataPoint* mecca = new DataPoint();
	jakarta->setLat(-6.08); jakarta->setLon(106.45);
	mecca->setLat(21.26); mecca->setLon(39.49);
	s.append(jakarta);
	s.append(mecca);
	QCOMPARE(s.heading().degs(), 65.04);
	
	//QVERIFY(segments.first().size() > 0);
	//QCOMPARE(segments.first().heading().degs(),
	//	       	Angle::Degrees(65.04).degs());
}

QTEST_MAIN(DataSourceTests)
#include "datasourcetests.moc"

