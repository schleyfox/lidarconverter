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
	ds->read();
	QVector<Segment> segments = ds->segment();
	QCOMPARE(segments.size(), 1);
	
	QVERIFY(segments.first().size() > 0);
	QCOMPARE(segments.first().heading().degs(),
		       	Angle::Degrees(65.04).degs());
}

QTEST_MAIN(DataSourceTests)
#include "datasourcetests.moc"

