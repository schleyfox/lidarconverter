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
	
	Segment cape_town_to_beijing = DRAW_TEST_LINE(cape_town, beijing);
	
	QCOMPARE(fuzzy_round(cape_town_to_beijing.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(-58.31).degs(),2));
	

	//Oslo to Brussels
	DataPoint* oslo = new DataPoint;
	oslo->setLat(59.9333); oslo->setLon(10.75);
	DataPoint* brussels = new DataPoint;
	brussels->setLat(50.85); brussels->setLon(4.35);
	Segment oslo_to_brussels = DRAW_TEST_LINE(oslo, brussels); 
	QCOMPARE(fuzzy_round(oslo_to_brussels.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(155.51).degs(),2));

	//Oslo to Douglas
	DataPoint* douglas = new DataPoint;
	douglas->setLat(54.14521); douglas->setLon(-4.48172);
	Segment oslo_to_douglas = DRAW_TEST_LINE(oslo, douglas); 
	QCOMPARE(fuzzy_round(oslo_to_douglas.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(118.35).degs(),2));

	//Douglas to Almaty
	DataPoint* almaty = new DataPoint;
	almaty->setLat(43.2775); almaty->setLon(76.8958);
	Segment douglas_to_almaty = DRAW_TEST_LINE(douglas, almaty); 
	QCOMPARE(fuzzy_round(douglas_to_almaty.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(-66.49).degs(),2));

	//Longyearbyen to Qaanaaq
	DataPoint* longyearbyen = new DataPoint;
	longyearbyen->setLat(78.21666); longyearbyen->setLon(15.55);
	DataPoint* qaanaaq = new DataPoint;
	qaanaaq->setLat(77.483333); qaanaaq->setLon(-69.33333);
	Segment longyearbyen_to_qaanaaq = DRAW_TEST_LINE(longyearbyen, qaanaaq);
	QCOMPARE(fuzzy_round(longyearbyen_to_qaanaaq.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(50.11).degs(),2));

	//Mt. Erebus to Montagu Island
	DataPoint* mt_erebus = new DataPoint;
	mt_erebus->setLat(-77.53); mt_erebus->setLon(167.17);
	DataPoint* montagu = new DataPoint;
	montagu->setLat(-58.416667); montagu->setLon(-26.383333);
	Segment mt_erebus_to_montagu = DRAW_TEST_LINE(mt_erebus, montagu);
	QCOMPARE(fuzzy_round(mt_erebus_to_montagu.heading().degs(), 2),
			fuzzy_round(Angle::Degrees(50.11).degs(),2));


 

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
