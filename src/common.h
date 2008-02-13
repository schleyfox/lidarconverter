#ifndef COMMON_H
#define COMMON_H
//Defines common includes as well as shared structures

#include <cmath>
#include <iostream>
#include <QObject>
#include <QVector>
#include <QString>
#include <QPair>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QDir>
#include <QDirIterator>


using namespace std;

/** 
 * radius of the earth in meters
 */
#define RADIUS 6378100.0

/**
 * Delicious Pi
 */
#define PI 3.14159265358979

double fuzzy_round(double x, int y);

//mini-classes


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
	double degs() const { return m_r * (180.0/PI); }
	double rads() const { return m_r; }
	void setDegrees(double x) { m_r = x * (PI/180.0); }
	void setRadians(double x) { m_r = x; }
	static Angle Degrees(double x) { Angle a = Angle(); 
		a.setDegrees(x); return a; }
	static Angle Radians(double x) { Angle a = Angle();
		a.setRadians(x); return a; }
	private:
	double m_r;
};

/**
 * Datapoint represents a point of data on the ground and the float* column of
 * data associated with it.  It converts latitude and longitude given in 
 * degrees to the Angle format automatically
 *
 * @author Ben Hughes
 */
class DataPoint {
	public:
	DataPoint() { 
		m_lat = m_lon = Angle::Degrees(0);
		m_data = 0;
       	}
	Angle lon() const { return m_lon; }
	Angle lat() const { return m_lat; }
	float* data() const { return m_data; }
	void setLon(double x) { m_lon = Angle::Degrees(x); }
	void setLon(Angle x) { m_lon = x; }
	void setLat(double x) { m_lat = Angle::Degrees(x); }
	void setLat(Angle x) { m_lat = x; }
	void setData(float* &x) { m_data = x; }
	private:
	Angle m_lon, m_lat;
	float* m_data;
};
#endif
