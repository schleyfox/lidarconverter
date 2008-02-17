#ifndef CALIPSOL1DATASOURCE_H
#define CALIPSOL1DATASOURCE_H
#include "datasource.h"

/**
 * Concrete implementation of DataSource for Calipso Level 1 data.
 * @see LidarConverterTests::DataSource_calipsoRead()
 */
class CalipsoL1DataSource : public DataSource {
	public:
	/**
	 * Sets up the description of the CALIPSO data.
	 * It is important to notice that the variables correspond to the
	 * normalized data.  CALIPSO Level 1 data has 583 vertical bins that
	 * go to 40km altitude with different resolutions along the way, but
	 * for the visualization we are only interested in 0-20km and we
	 * produce a data array with 690 vertical bins to allow for all data
	 * to represent one pixel in the final image at 30m resolution
	 */
	CalipsoL1DataSource(QString filename = "") : DataSource(filename) {
		m_properties.h_res = 333; //333m
		m_properties.v_res = 30; //30m
		m_properties.max_altitude = 20000; //20km
		m_properties.height = 690;
	}

	bool read();
};
#endif
