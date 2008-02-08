#include "testdatasource.h"

/**
 * Populates data_ary with data corresponding to a straight line from
 * Jakarta to Mecca.  Based on http://krysstal.com/sphertrig.html
 */
bool TestDataSource::read() {
	float* data_temp = new float[10];
	
	for(int i = 0; i < 10; i++)
		data_temp[i] = (i < 3 || i > 5)? 1.0 : 0.0;
	data_ary = Helper::makeStraightLineDataPoints(
			-6.08, //Latitude of Jakarta
			106.45, //Longitude of Jakarta
			65.04, //heading from Jakarta to Mecca
			dataProperties().base_horiz_res,
			data_temp,
			(int)ceil(7912000.0/dataProperties().base_horiz_res));
	return true;

}

