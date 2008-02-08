#ifndef TESTDATASOURCE_H
#define TESTDATASOURCE_H
#include "datasource.h"
#include "testsegment.h"
#include "helper.h"

class TestDataSource : public DataSource {
	public:
	TestDataSource() : DataSource(){
		m_properties.base_horiz_res = 10000; //10km
		m_properties.max_altitude = 10000; //10km
		m_properties.height = 10;
		m_properties.resolutions[0] = 
			QPair<double, double>(10000, 1000);  //10kmx1km constant
	}


	bool read();
	QVector<Segment> segment();
};
#endif
