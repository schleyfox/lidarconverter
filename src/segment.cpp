#include "segment.h"
#include "datasource.h"

/**
 * Must be instantiated with a datasource
 * 
 * properties of data are discovered through this interface
 */
Segment::Segment(DataSource* datasource) : QVector<DataPoint*>() {
	m_datasource = datasource;
	partition_threshold = 0.1;
}

/**
 * CTM Section 2.1.2
 *
 * "Heading of a segment is the angle between arcs a and c on a spherical 
 * triangle.  The variable c is the line of longitude which faces due north
 * and a is the arc of the great circle joining points B and C. B and C are the
 * initial and final Earth surface points of a segment.  Using the sine rule,
 * heading (angle B) is calculated in Eq. 2.1 where A is the longitude 
 * difference
 */ 
Angle Segment::heading() const {
	if(size() == 0) {
		return Angle::Radians(0);
	}
	Angle A, C, a, b, c;

	//Calipso Technical Manual Equation 2.1
	//Add or subtract longitude depending on relationship to prime meridian
	if( first()->lon().degs() > 0.0 && last()->lon().degs() > 0.0) {
		A = Angle::Degrees( first()->lon().degs()
			      	- last()->lon().degs() 
				); //same side of meridian
	} else {
		A = Angle::Degrees( first()->lon().degs()
			      	+ last()->lon().degs() 
				); //opposite sides of meridian
	}
	
	c = Angle::Degrees( 90.0 - last()->lat().degs()
			); //Polar Distance of end point

	b = Angle::Degrees( 90.0 - first()->lat().degs()
			); //Polar Distance of start point

	a = Angle::Radians( acos(cos(b.rads()) * cos(c.rads())
			       	+ sin(b.rads()) * sin(c.rads()) * cos(A.rads()))
			); //cosine rule

	C = Angle::Radians( asin(sin(A.rads()) * sin(c.rads())
			       	/ sin(a.rads())) ); //sine rule
	return C;
}

/**
 * CTM Section 2.1.3
 *
 * Theta1, the angle created by connecting the center of the Earth to the 
 * endpoints of the Segment, is calculated according to Eq. 2.2 where segment
 * length is the length of the Segment vector (Segment#length strangely enough
 * ) the horizontal resolution is defined in the DataSourceProperties struct
 * as base_horiz_res.  The radius of the Earth is assumed to be a constant
 * 63781000 meters
 */
Angle Segment::fullAngle() const {
	double horizontal_resolution = 
		dataSource()->dataProperties().base_horiz_res;
	//CTM Eq. 2.2
	return Angle::Radians((size() * horizontal_resolution)/RADIUS);
}

/** 
 * Half of fullAngle or Theta2 = (Theta1)/2
 */
Angle Segment::halfAngle() const {
	return Angle::Radians(fullAngle().rads()/2.0);
}

/**
 * fullAngleChord() or Chord1 is the chord formed by the straight line passing
 * through the end points of the segment as calculated in Eq. 2.2
 */
double Segment::fullAngleChord() const {
	return findChord(fullAngle());
}

/**
 * halfAngleChord() or Chord2 is the chord formed by the straight line passing
 * through one end point and the midpoint of the segment via Eq. 2.4
 */
double Segment::halfAngleChord() const {
	return findChord(halfAngle());
}

/**
 * Helper implementation of Eq. 2.4
 */
double Segment::findChord(Angle theta) const {
	//CTM Eq. 2.4
	return 2.0 * sin(theta.rads() / 2.0) * RADIUS;
}

/**
 * Base is half of Chord1
 */
double Segment::base() const {
	return fullAngleChord() / 2.0;
}

/**
 * droppingDistance is the negative altitude required to make the midpoint 
 * flush with the Earth's surface.  It can be found via the Pythagorean Theorem
 * as show in Eq. 2.3
 */
double Segment::droppingDistance() const {
	//CTM Eq. 2.3
	return sqrt(pow(halfAngleChord(), 2) - pow(base(), 2));
}

/**
 * externalAngle() or Theta3 is the angle between the "fanned-out" LIDAR data
 * and the line that forms Chord1.  Eq. 2.5
 */
Angle Segment::externalAngle() const {
	//CTM Eq. 2.5
	return Angle::Degrees(90.0 - halfAngle().degs());
}

/**
 * leftoverLength() is the distance between the last point of LIDAR on the
 * ground and the boundaries of the image needed to render it curved.  See
 * Eq. 2.6
 */
double Segment::leftoverLength() const {
	double max_altitude = dataSource()->dataProperties().max_altitude;
	//CTM Eq. 2.6
	return cos(externalAngle().rads()) * max_altitude;
}

/**
 * segLength() is the required length of the image (in pixels) to hold the 
 * curved LIDAR.
 *
 * length() was already used by QVector
 */
double Segment::segLength() const {
	//CTM Eq. 2.7
	return 2.0 * leftoverLength() + fullAngleChord();
}

/**
 * seqWidth() is the required width of the image (in pixels) to hold the
 * curved LIDAR.
 */
double Segment::segWidth() const {
	double max_altitude = dataSource()->dataProperties().max_altitude;
	//CTM Eq. 2.8
	return droppingDistance() + max_altitude;
}

/**
 * appendOrStop() tests the heading() change caused by a DataPoint* dp. If this
 * change is greater than partition_threshold, dp is not appended and false is
 * returned.  Otherwise, dp is appended with the return value true.  The first
 * two DataPoints are always appended to seed the heading.
 */
bool Segment::appendOrStop(DataPoint* dp) {
	if( size() > 1) {
		Angle heading1 = heading();
		append(dp);
		if( abs(heading1.degs() - heading().degs())
			       	> partition_threshold ) {
			pop_back();
			return false;
		} else {
			return true;
		}
	} else {
		append(dp);
		return true;
	}
}

