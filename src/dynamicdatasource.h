#ifndef DYNAMICDATASOURCE_H
#define DYNAMICDATASOURCE_H

#include "common.h"
#include "datasource.h"

class DynamicDataSource : public DataSource {
	public:
	bool read();

	/**
	 * The resolution map is a QMap corresponding to the 
	 * altitude => vertical resolution table in the Algorithmic Theorectical
	 * Basis document.
	 *
	 * @returns [base altitude (in meters) => vertical res (in meters),...]
	 */ 
	QMap<int, int> resolutions() {
		return m_resolutionmap;
	}

	/**
	 * @param resolutions [base altitude (m) => vertical res (m),...]
	 */
	void setResolutions(QMap<int, int> resolutions) {
		m_resolutionmap = resolutions;
	}

	/**
	 * The longitude data name parameter tells DynamicDataSource::read()
	 * where to find the points of longitude in the HDF
	 *
	 *@return the name of the longitude values in the HDF
	 */
	QString longitudeDataName() {
		return m_longitudedataname;
	}
	/**
	 * @param longitudedataname is the data set name for the longitude
	 */
	void setLongitudeDataName(QString longitudedataname){
		m_longitudedataname = longitudedataname;
	}
	
	/**
	 * The latitude data name parameter tells DynamicDataSource::read()
	 * where to find the points of latitude in the HDF
	 *
	 *@return the name of the latitude values in the HDF
	 */
	QString latitudeDataName() {
		return m_latitudedataname;
	}
	/**
	 * @param latitudedataname is the data set name for the latitude
	 */
	void setLatitudeDataName(QString latitudedataname){
		m_latitudedataname = latitudedataname;
	}

	/**
	 * The data name tells DynamicDataSource::read() where the data is
	 * in the HDF (e.g. Total_Attenuated_Backscatter_532 for CALIPSO)
	 *
	 * @return the dataset name for the data in the HDF
	 */
	QString dataName() {
		return m_dataname;
	}
	/**
	 * @param dataname is the dataset name for the actual data
	 */
	void setDataName(QString dataname) {
		m_dataname = dataname;
	}

	/**
	 * Max altitude is the top altitude (in meters) that is "interesting"
	 * It is the point to which the image data will extend (e.g. 20km for
	 * CALIPSO)
	 */
	int maxAltitude() {
		return m_maxaltitude;
	}
	/**
	 * @param maxaltitude is the top point one is interested in in meters
	 */
	void setMaxAltitude(int maxaltitude) {
		m_maxaltitude = maxaltitude;
	}


	protected:
	QMap<int, int> m_resolutionmap;
	QString m_latitudedataname, m_longitudedataname, m_dataname;
	int m_maxaltitude;
};



#endif
