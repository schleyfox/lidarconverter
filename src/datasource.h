#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "common.h"
#include "segment.h"

/** @struct DataSource Properties
 * The DataSourceProperties struct holds information that describes the data
 * in the DataSource.  Calculations in Segment depend on these values
 */
typedef struct{
	
	/**
	 * in meters, this is the horizontal resolution of a single datapoint
	 */
	double h_res;

	/**
	 * in meters, this is the vertical resolution of a single datapoint
	 */
	double v_res;
	
	/**
	 * in meters, this is the highest altitude for which data is collected
	 */
	double max_altitude;
	
	/**
	 * in number of datapoints, this describes the size of a column of data
	 */
	int height;
	
} DataSourceProperties;

/**
 * DataSource is the abstract class of readers that provide data for 
 * segmentation.  This class should be subclassed into a concrete
 * implementation for use.  Ex. CalipsoL1Source for a class that reads CALIPSO
 * Level 1 Data.
 *
 * @author Ben Hughes
 */
class DataSource {
	public:
	DataSource(QString filename = "" );
	virtual ~DataSource() {
		for(int i = 0; i < data_ary.size(); i++) {
			delete data_ary.at(i);
			data_ary.remove(i);
		}
	}

	void setFilename(QString filename) {
		m_filename = filename;
	}

	QString filename() const {
		return m_filename;
	}
	
	/**
	 * Reads data from filename
	 *
	 * @note reading is purely virtual and concrete classes must implement it
	 *
	 * Data is to be read into a QVector<DataPoint*> data_ary
	 */
	virtual bool read() = 0;
	
	/**
	 * @return the data associated with this source
	 *
	 * data is obtained through read()
	 */
	QVector<DataPoint*> data() const {
		return data_ary;
	}
	
	/**
	 * @return the description of the data as set in m_properties
	 *
	 * subclasses should set m_properties to the appropriate struct
	 * at creation
	 */
	DataSourceProperties dataProperties() const {
		return m_properties;
	}

	virtual QVector<Segment> segment();

	protected:
	QString m_filename;
	DataSourceProperties m_properties;
	QVector<DataPoint*> data_ary;
};
#endif
