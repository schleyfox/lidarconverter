#ifndef ANGLE_H
#define ANGLE_H
#include "common.h"

/**
 * 180/pi as precise as I could get it
 */
#define R_TO_D 57.2957795130823

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
	double degs() const;
	double rads() const; 
	void setDegrees(double x);
	void setRadians(double x);
	static Angle Degrees(double x) { Angle a = Angle(); 
		a.setDegrees(x); return a; }
	static Angle Radians(double x) { Angle a = Angle();
		a.setRadians(x); return a; }

	protected:
	double m_r;

	virtual double formatAngle(double x) const;
};

class Latitude : public Angle {
	public:
	static Latitude Degrees(double x) { Latitude a; 
		a.setDegrees(x); return a; }
	static Latitude Radians(double x) { Latitude a;
		a.setRadians(x); return a; }
	
	protected:
	virtual double formatAngle(double x) const;
};
#endif
