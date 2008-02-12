#ifndef TESTDATASOURCE_H
#define TESTDATASOURCE_H
#include "datasource.h"
#include "testsegment.h"
#include "helper.h"

class TestDataSource : public DataSource {
	public:
	TestDataSource() : DataSource(){
		m_properties.h_res = 10000; //10km
		m_properties.v_res = 1000; //1km
		m_properties.max_altitude = 10000; //10km
		m_properties.height = 10;
	}


	bool read();
	QVector<Segment> segment();
};
#endif
