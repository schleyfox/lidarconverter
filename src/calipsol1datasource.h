#ifndef CALIPSOL1DATASOURCE_H
#define CALIPSOL1DATASOURCE_H
#include "datasource.h"
#include "hdf4object.h"

class CalipsoL1DataSource : public DataSource {
	public:
	CalipsoL1DataSource(QString filename = "") : DataSource(filename) {
		m_properties.base_horiz_res = 333; //333m
		m_properties.max_altitude = 20000; //20km
		m_properties.height = 490;
		m_properties.resolutions[0] = QPair<double,double>(333,30);
		m_properties.resolutions[290] = QPair<double,double>(1000,60);
	}

	bool read();
};
#endif
