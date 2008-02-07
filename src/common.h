//Defines common includes as well as shared structures

#include <iostream>
#include <QObject>
#include <QVector>
#include <QString>

using namespace std;

/** 
 * radius of the earth in meters
 */
#define RADIUS 6378100.0

/**
 * Delicious Pi
 */
#define PI 3.14159265

//mini-classes

/**
 * Datapoint represents a point of data on the ground and the float* column of
 * data associated with it.  It converts latitude and longitude given in 
 * degrees to the Angle format automatically
 *
 * @author Ben Hughes
 */
class DataPoint {
	public:
	DataPoint() { m_lat = m_lon = m_data = 0; }
	const Angle lon() { return m_lon; }
	const Angle lat() { return m_lat; }
	const float* data() { return m_data; }
	void setLon(double x) { m_lon = Angle::Degrees(x); }
	void setLon(Angle x) { m_lon = x; }
	void setLat(double x) { m_lat = Angle::Degrees(x); }
	void setLon(Angle x) { m_lat = x; }
	void setData(float* x) { m_data = x; }
	private:
	Angle m_lon, m_lat;
	float* m_data;
};

/**
 * Angle represents a radian/degree agnostic angle.  Requests are made on the
 * object for degree or radian explicitly through Angle#degs and Angle#rads.
 *
 * Angles are created through  Angle a = Angle::Degrees(45.0) or 
 * a = Angle::Radians(PI/4.0)
 */
class Angle {
	public:
	Angle() { m_r = 0; }
	const double degs() { return m_r * (180.0/PI); }
	const double rads() { return m_r; }
	void setDegrees(double x) { m_r = x * (PI/180.0); }
	void setRadians(double x) { m_r = x; }
	static Angle Degrees(double x) { Angle a = Angle(); 
		a.setDegrees(x); return a; }
	static Angle Radians(double x) { Angle a = Angle();
		a.setRadians(x); return a; }
	private:
	double m_r;
};
