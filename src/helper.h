#ifndef HELPER_H
#define HELPER_H
#include "common.h"

/**
 * Helper  utility class that holds random abilities that assist with things
 */
class Helper {
	public:
	static QVector<DataPoint*> makeStraightLineDataPoints(
			double init_lat, double init_lon,
		       	double heading,  double spacing,
		    	float* &data, int n);
	static QVector< QPair<Angle,Angle> > makeStraightLineCoordinates(
			double init_lat, double init_lon, 
			double heading, double spacing,
		       	int n);

	static void makeKMLPath(QVector<DataPoint*> points, 
			QString filename);
};
#endif
