#ifndef DATAPOINT_H
#define DATAPOINT_H

#include "angle.h"

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
		m_lat = Latitude::Degrees(0);
		m_lon = Angle::Degrees(0);
		m_data = 0;
       	}
	Angle lon() const { return m_lon; }
	Angle lat() const { return m_lat; }
	float* data() const { return m_data; }
	void setLon(double x) { m_lon = Angle::Degrees(x); }
	void setLon(Angle x) { m_lon = x; }
	void setLat(double x) { m_lat = Latitude::Degrees(x); }
	void setLat(Latitude x) { m_lat = x; }
	void setData(float* &x) { m_data = x; }
	private:
	Angle m_lon;
       	Latitude m_lat;
	float* m_data;
};

#endif
