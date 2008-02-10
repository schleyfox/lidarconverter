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
	
	Segment cape_town_to_beijing;
	cape_town_to_beijing = DRAW_TEST_LINE(cape_town, beijing);
	
	QCOMPARE(fuzzy_round(cape_town_to_beijing.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(-58.31).degs(),2));

	//Oslo to Brussels
	DataPoint* oslo = new DataPoint;
	oslo->setLat(59.9333); oslo->setLon(10.75);
	DataPoint* brussels = new DataPoint;
	brussels->setLat(50.85); brussels->setLon(4.35);
	Segment oslo_to_brussels;
	oslo_to_brussels += DRAW_TEST_LINE(oslo, brussels); 
	QCOMPARE(fuzzy_round(oslo_to_brussels.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(155.51).degs(),2));

	//Oslo to Douglas
	DataPoint* douglas = new DataPoint;
	douglas->setLat(54.14521); douglas->setLon(-4.48172);
	Segment oslo_to_douglas;
	oslo_to_douglas += DRAW_TEST_LINE(oslo, douglas); 
	QCOMPARE(fuzzy_round(oslo_to_douglas.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(118.35).degs(),2));

	//Douglas to Almaty
	DataPoint* almaty = new DataPoint;
	almaty->setLat(43.2775); almaty->setLon(76.8958);
	Segment douglas_to_almaty;
	douglas_to_almaty += DRAW_TEST_LINE(douglas, almaty); 
	QCOMPARE(fuzzy_round(douglas_to_almaty.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(-66.49).degs(),2));
 

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
