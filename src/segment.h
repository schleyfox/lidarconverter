#include "common.h"

/**
 * The Segment class is an abstract class representing a segment of a 
 * DataSource.  Segment should be subclassed to change default parameters
 * like partition_threshold. (Of course it is complete enough that if 0.1 is
 * good enough for your purposes, it can be dropped in as it stands).
 *
 * @author Ben Hughes
 */
class Segment : public QVector<DataPoint*> {
	public:
	Segment(DataSource* datasource);
	virtual ~Segment();
	
	const DataSource* dataSource() {
		return m_datasource;
	}

	//CTM Section 2.1.2
	const Angle heading();
	bool appendOrStop(DataPoint* dp);  //partitions
	
	//CTM Section 2.1.3: Segment Geometry
	const Angle fullAngle(); //theta_1
	const Angle halfAngle(); //theta_2
	const double fullAngleChord(); //chord_1
	const double halfAngleChord(); //chord_2
	const double base(); //base
	const double droppingDistance(); //distance_dropping

	//CTM Section 2.1.4: Dimensions
	const Angle externalAngle(); //theta_3
	const double leftoverLength();  //length_leftover
	const double segLength(); //length, naming conflict :(
	const double segWidth(); //width
	

	protected:
	DataSource* m_datasource;
	double partition_threshold;

	double findChord(Angle theta);
}

