#include <QtTest/QtTest>
#include "common.h"
#include "segment.h"
#include "datasource.h"
#include "testdatasource.h"
#include "testsegment.h"
#include "calipsol1datasource.h"
#include "testhelper.h"
#include "lcolorlookup.h"
#include "curvetransform.h"
#include "calipsocolormap.h"

class LidarConverterTests : public QObject {
	Q_OBJECT 
	private slots:
	void Segment_heading() {
		//Jakarta to Mecca
		DataPoint *jakarta = new DataPoint;
		jakarta->setLat(-6.08); jakarta->setLon(106.45);
		DataPoint *mecca = new DataPoint;
		mecca->setLat(21.26); mecca->setLon(39.49);
		QCOMPARE(fuzzy_round(Segment::heading(jakarta, mecca).degs(), 2)
				, fuzzy_round(Angle::Degrees(65.04).degs(), 2));

	
		//Cape Town to Beijing
		DataPoint *cape_town = new DataPoint;
		cape_town->setLat(-33.56); cape_town->setLon(18.28);
		DataPoint *beijing = new DataPoint;
		beijing->setLat(39.55); beijing->setLon(116.26);
		QCOMPARE(fuzzy_round(Segment::heading(cape_town, beijing).degs()
			, 2), fuzzy_round(Angle::Degrees(-58.31).degs(), 2));
		Segment cape_town_to_beijing = DRAW_TEST_LINE(cape_town, beijing);
		QCOMPARE(fuzzy_round(cape_town_to_beijing.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(-58.31).degs(), 2));


		//Oslo to Brussels
		DataPoint *oslo = new DataPoint;
		oslo->setLat(59.9333); oslo->setLon(10.75);
		DataPoint *brussels = new DataPoint;
		brussels->setLat(50.85); brussels->setLon(4.35);
		Segment oslo_to_brussels = DRAW_TEST_LINE(oslo, brussels);
		QCOMPARE(fuzzy_round(oslo_to_brussels.heading().degs(), 2),
		  fuzzy_round(Angle::Degrees(155.51).degs(), 2));

		//Oslo to Douglas
		DataPoint *douglas = new DataPoint;
		douglas->setLat(54.14521); douglas->setLon(-4.48172);
		Segment oslo_to_douglas = DRAW_TEST_LINE(oslo, douglas);
		QCOMPARE(fuzzy_round(oslo_to_douglas.heading().degs(), 2),
		  fuzzy_round(Angle::Degrees(118.35).degs(), 2));

		//Douglas to Almaty
		DataPoint *almaty = new DataPoint;
		almaty->setLat(43.2775); almaty->setLon(76.8958);
		Segment douglas_to_almaty = DRAW_TEST_LINE(douglas, almaty);
		QCOMPARE(fuzzy_round(douglas_to_almaty.heading().degs(), 2),
		  fuzzy_round(Angle::Degrees(-66.49).degs(), 2));

		//Longyearbyen to Qaanaaq
		DataPoint *longyearbyen = new DataPoint;
		longyearbyen->setLat(78.21666); longyearbyen->setLon(15.55);
		DataPoint *qaanaaq = new DataPoint;
		qaanaaq->setLat(77.483333); qaanaaq->setLon(-69.33333);
		Segment longyearbyen_to_qaanaaq =
			DRAW_TEST_LINE(longyearbyen, qaanaaq);
		QCOMPARE(fuzzy_round(longyearbyen_to_qaanaaq.heading().degs(), 2),
		  fuzzy_round(Angle::Degrees(50.11).degs(), 2));

	//Mt. Erebus to Montagu Island
	//Fails miserably
	/*DataPoint* mt_erebus = new DataPoint;
	   mt_erebus->setLat(-77.53); mt_erebus->setLon(167.17);
	   DataPoint* montagu = new DataPoint;
	   montagu->setLat(-58.416667); montagu->setLon(-26.383333);
	   Segment mt_erebus_to_montagu = DRAW_TEST_LINE(mt_erebus, montagu);
	   QCOMPARE(fuzzy_round(mt_erebus_to_montagu.heading().degs(), 2),
	   fuzzy_round(Angle::Degrees(50.11).degs(),2)); */

	//Novaya Zemlya to Eureka (Ellesmere Island)
	/*DataPoint* zemlya = new DataPoint;
	   zemlya->setLat(74); zemlya->setLon(56);
	   DataPoint* eureka = new DataPoint;
	   eureka->setLat(80.216667); eureka->setLon(-86.18333);
	   Segment zemlya_to_eureka = DRAW_TEST_LINE(zemlya, eureka);
	   QCOMPARE(fuzzy_round(zemlya_to_eureka.heading().degs(), 2),
	   fuzzy_round(Angle::Degrees(50.11).degs(),2)); */
	} 
	
	void DataSource_read() {
		DataSource *ds = new TestDataSource();
		ds->read();
		QVERIFY(ds->data().size() > 0);
		delete ds;
    	}

	void DataSource_calipsoRead() {
		CalipsoL1DataSource *ds =
	    	new CalipsoL1DataSource("calipsol1test.hdf");
		ds->read();
		QCOMPARE(ds->data().size(), 56175);
		Helper::makeKMLPath(ds->data(), "kml/calipsol1test.kml");
		QVector <Segment> segments = ds->segment();
		qDebug() << segments.size() << " segments";
		QVERIFY(segments.size() > 0);

		QVector < DataPoint * >segment_path;
		for (int i = 0; i < segments.size(); i++) {
			segment_path << segments.at(i).first();
			segment_path << segments.at(i).last();
		}
		Helper::makeKMLPath(segment_path, "kml/calipsol1test-segment.kml");
		delete ds;
	}

	void DataSource_segment() {
		DataSource *ds = new TestDataSource();
		ds->read();
		QVector < Segment > segments = ds->segment();
		QCOMPARE(segments.size(), 2);

		//write out sample kml
		Helper::makeKMLPath(ds->data(), "kml/full_swath.kml");
		Helper::makeKMLPath(segments.first(), "kml/jakarta_to_mecca.kml");
		Helper::makeKMLPath(segments.last(), "kml/mecca_to_izmir.kml");

		//Jakarta to Mecca      
		QVERIFY(segments.first().size() > 0);
		QCOMPARE((int) segments.first().heading().degs() * 100, (int) Angle::Degrees(65.04).degs() * 100);	//fuck doubles

		//Mecca to Izmir
		QVERIFY(segments.last().size() > 0);
		QCOMPARE((int) segments.last().heading().degs() * 100, (int) Angle::Degrees(29.5).degs() * 100);	//fuck doubles
	}

	void LColorLookup_colorify() {
		QMap<float, uint> cm;
		cm[0.5] = qRgba(255,255,255,255);
		cm[1.0] = qRgba(0,255,255,255);
		cm[1.5] = qRgba(255,0,255,255);
		cm[2.0] = qRgba(255,255,0,255);

		LColorLookup lut;
		lut.setColorMap(cm);
		lut.compile();
		QCOMPARE(lut.colorify(0.5), qRgba(255,255,255,255));
		QCOMPARE(lut.colorify(1.0), qRgba(0,255,255,255));
		QCOMPARE(lut.colorify(1.49), qRgba(0,255,255,255));
		//I hate floating point rounding
		QCOMPARE(lut.colorify(1.51), qRgba(255,0,255,255));
		QCOMPARE(lut.colorify(2.0), qRgba(255,255,0,255));
	}

	void CurveTransform_transform() {
		
		LColorLookup* lut = makeCalipsoColorMap();

		CalipsoL1DataSource *ds =
	    		new CalipsoL1DataSource("calipsol1test.hdf");
		ds->read();
		QCOMPARE(ds->data().size(), 56175);
		QVector<Segment> segments = ds->segment();
		qDebug() << segments.size() << " segments";
		CurveTransform ct(segments.at(15), lut);
		QVERIFY(ct.transform().save("test.png", "PNG"));
		QVERIFY(segments.size() > 0);
	}


};

QTEST_MAIN(LidarConverterTests)
#include "tests.moc"
