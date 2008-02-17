#include "datasource.h"

/**
 * Creates a new DataSource object with the filename <i>filename</i>
 */
DataSource::DataSource(QString filename) {
	data_ary = QVector<DataPoint*>();
	if(!filename.isEmpty()){
		setFilename(filename);
	}
}

/**
 * CTM Section 2.1.2
 *
 * The current release of Google Earth requires each rectangular
 * polygon to be positioned by a single control point and a heading
 * about the z-axis.  This function partitions the data into segments
 * that can be positioned with their midpoint and heading.  Heading
 * is calculated in Segment#heading(). If the calculated heading
 * changes by more than Segment#partition_threshold, a new segment
 * is started.  The final set of segments is returned as a vector.
 */
QVector<Segment> DataSource::segment() {
	QVector<Segment> segments;
	QVectorIterator<DataPoint*> i(data_ary);
	int j = 0;

	while(i.hasNext()) {
		Segment s(this);
		while(i.hasNext() && s.appendOrStop(i.next()));
		s.setSegmentNumber(j);
		segments.append(s);
		j++;
	}

	return segments;
}
