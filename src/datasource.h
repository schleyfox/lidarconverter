#include <common.h>

/**
 * The DataSourceProperties struct holds information that describes the data
 * in the DataSource.  Calculations in Segment depend on these values
 */
typedef struct{
	
	/**
	 * in meters, this is the resolution of a single datapoint on the 
	 * ground
	 */
	const double base_horiz_res;
	
	/**
	 * in meters, this is the highest altitude for which data is collected
	 */
	const double max_altitude;
	
	/**
	 * in number of datapoints, this describes the size of a column of data
	 */
	const int height;
	
	/**
	 * Many instruments have varying data resolutions by altitude.  This
	 * maps the base height (in datapoints (or bins)) to the (horizontal,
	 * vertical) resolution in meters at that level
	 */
	const QMap<int, QPair<double, double> > resolutions;
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
	virtual ~DataSource() = 0;

	void setFilename(QString filename) {
		m_filename = filename;
	}

	const QString filename() {
		return m_filename;
	}
	
	/**
	 * Reads data from filename
	 *
	 * Note: reading is purely virtual and concrete classes must implement it
	 *
	 * @return true on success
	 *
	 * Data is to be read into a QVector<DataPoint*> data_ary
	 */
	virtual bool read() = 0;
	
	/**
	 * @return the data associated with this source
	 *
	 * data is obtained through read()
	 */
	const QVector<DataPoint*> data() {
		return data_ary;
	}
	
	/**
	 * @return the description of the data as set in m_properties
	 *
	 * subclasses should set m_properties to the appropriate struct
	 * at creation
	 */
	const DataSourceProperties dataProperties() {
		return m_properties;
	}

	virtual QVector<Segment> segment();

	protected:
	QString m_filename;
	DataSourceProperties m_properties;
	QVector<DataPoint*> data_ary;
}
