#include "angle.h"

double Angle::degs() const {
	return formatAngle(m_r) * R_TO_D;
}

double Angle::rads() const {
	return formatAngle(m_r);
}

void Angle::setDegrees(double x) {
	m_r = formatAngle(x * (PI/180.0));
}

void Angle::setRadians(double x) {
	m_r = formatAngle(x);
}

/**
 * Normalizes an angle to be between 0 and 360 degrees
 *
 * @param x angle in radians
 * @return normalized angle in radians
 */
double Angle::formatAngle(double x) const {
	if(x < 0.0) {
		x = (2.0*PI)+x;
	}
	double q = floor(x/(2.0*PI));
	x = x - q*2.0*PI;
	return x;
}

double Latitude::formatAngle(double x) const {
	x = Angle::formatAngle(x);
	if(x > PI) {
		x -= PI;
	}
	if(x > (PI/2.0)) {
		x = -1.0*(x - (PI/2.0));
	}
	return x;
}
