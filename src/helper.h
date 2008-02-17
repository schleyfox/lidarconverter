#ifndef HELPER_H
#define HELPER_H
#include "common.h"
#include "segment.h"

/**
 * Helper  utilities that hold random abilities that assist with things
 */
namespace Helper {
	QVector<DataPoint*> makeStraightLineDataPoints(
			double init_lat, double init_lon,
		       	double heading,  double spacing,
		    	float* &data, int n);
	QVector<DataPoint*> makeStraightLineDataPoints(
			DataPoint* start, DataPoint* end,
			double spacing, float* &data);
	QVector< QPair<Angle,Angle> > makeStraightLineCoordinates(
			double init_lat, double init_lon, 
			double heading, double spacing,
		       	int n);

	void makeKMLPath(QVector<DataPoint*> points, 
			QString filename);
}
#endif
