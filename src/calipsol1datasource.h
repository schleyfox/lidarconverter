#ifndef CALIPSOL1DATASOURCE_H
#define CALIPSOL1DATASOURCE_H
#include "datasource.h"

class CalipsoL1DataSource : public DataSource {
	public:
	CalipsoL1DataSource(QString filename = "") : DataSource(filename) {
		m_properties.h_res = 333; //333m
		m_properties.v_res = 30; //30m
		m_properties.max_altitude = 20000; //20km
		m_properties.height = 690;
	}

	bool read();
};
#endif
