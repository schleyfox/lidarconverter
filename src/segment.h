#ifndef SEGMENT_H
#define SEGMENT_H
#include "common.h"

class DataSource;

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
	Segment(DataSource* datasource = 0);
	
	DataSource* dataSource() const {
		return m_datasource;
	}

	//CTM Section 2.1.2
	Angle heading() const;
	static Angle heading(DataPoint* start, DataPoint* end);
	bool appendOrStop(DataPoint* dp);  //partitions
	
	//CTM Section 2.1.3: Segment Geometry
	Angle fullAngle() const; //theta_1
	Angle halfAngle() const; //theta_2
	double fullAngleChord() const; //chord_1
	double halfAngleChord() const; //chord_2
	double base() const; //base
	double droppingDistance() const; //distance_dropping

	//CTM Section 2.1.4: Dimensions
	Angle externalAngle() const; //theta_3
	double leftoverLength() const;  //length_leftover
	double segLength() const; //length, naming conflict :(
	double segWidth() const ; //width
	

	protected:
	DataSource* m_datasource;
	double partition_threshold;

	double findChord(Angle theta) const;
};
#endif
