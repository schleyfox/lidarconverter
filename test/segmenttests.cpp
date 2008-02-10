#include "segmenttests.h"

void SegmentTests::heading() {
	//Jakarta to Mecca
	DataPoint* jakarta = new DataPoint;
	jakarta->setLat(-6.08); jakarta->setLon(106.45);
	DataPoint* mecca = new DataPoint;
	mecca->setLat(21.26); mecca->setLon(39.49);
	QCOMPARE(fuzzy_round(Segment::heading(jakarta, mecca).degs(),2),
		       	fuzzy_round(Angle::Degrees(65.04).degs(),2)); //fuck doubles
	//Cape Town to Beijing
	DataPoint* cape_town = new DataPoint;
	cape_town->setLat(-33.56); cape_town->setLon(18.28);
	DataPoint* beijing = new DataPoint;
	beijing->setLat(39.55); beijing->setLon(116.26);
	QCOMPARE(fuzzy_round(Segment::heading(cape_town, beijing).degs(),2),
		       	fuzzy_round(Angle::Degrees(-58.31).degs(),2)); //fuck doubles
	float* data = new float[10];
	Segment cape_town_to_beijing;
	cape_town_to_beijing += Helper::makeStraightLineDataPoints(cape_town,
		       	beijing, 10000, data);
	Helper::makeKMLPath(cape_town_to_beijing, "kml/cape_town_to_beijing.kml");
	QCOMPARE(fuzzy_round(cape_town_to_beijing.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(-58.31).degs(),2));

	//Oslo to Brussels
	DataPoint* oslo = new DataPoint;
	oslo->setLat(59.9333); oslo->setLon(10.75);
	DataPoint* brussels = new DataPoint;
	brussels->setLat(50.85); brussels->setLon(4.35);
	Segment oslo_to_brussels;
	oslo_to_brussels += Helper::makeStraightLineDataPoints(oslo,
		       	brussels, 10000, data);
	Helper::makeKMLPath(oslo_to_brussels, "kml/oslo_to_brussels.kml");
	QCOMPARE(fuzzy_round(oslo_to_brussels.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(123.18).degs(),2));
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
