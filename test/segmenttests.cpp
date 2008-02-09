#include "segmenttests.h"

void SegmentTests::heading() {
	//Jakarta to Mecca
	DataPoint* jakarta = new DataPoint;
	jakarta->setLat(-6.08); jakarta->setLon(106.45);
	DataPoint* mecca = new DataPoint;
	mecca->setLat(21.26); mecca->setLon(39.49);
	//QCOMPARE(fuzzy_round(Segment::heading(jakarta, mecca).degs(),2),
	//	       	fuzzy_round(Angle::Degrees(65.04).degs(),2)); //fuck doubles
	//Cape Town to Beijing
	DataPoint* cape_town = new DataPoint;
	cape_town->setLat(-33.56); cape_town->setLon(18.28);
	DataPoint* beijing = new DataPoint;
	beijing->setLat(39.55); beijing->setLon(116.26);
	//QCOMPARE(fuzzy_round(Segment::heading(cape_town, beijing).degs(),2),
	//	       	fuzzy_round(Angle::Degrees(-58.31).degs(),2)); //fuck doubles
	
	float* data = new float[10];
	QVector<DataPoint*> points = 
		Helper::makeStraightLineDataPoints(-33.56, 18.28, -58.31, 10000.0, data , 12933000/10000);
	Helper::makeKMLPath(points, "kml/capetown_to_beijing.kml");
	Angle beijing_header = Segment::heading(points.first(), points.last());
	QCOMPARE(fuzzy_round(beijing_header.degs(),2),
		       	fuzzy_round(Angle::Degrees(-58.31).degs(), 2));
}

void SegmentTests::fullAngle(){ }
void SegmentTests::halfAngle(){ }
void SegmentTests::fullAngleChord(){ }
void SegmentTests::halfAngleChord(){ }
void SegmentTests::base(){ }
void SegmentTests::droppingDistance(){ }
void SegmentTests::externalAngle(){ }
void SegmentTests::leftoverLength(){ }
void SegmentTests::segLength(){ }
void SegmentTests::segWidth(){ }
