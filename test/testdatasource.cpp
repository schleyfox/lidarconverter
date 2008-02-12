#include "testdatasource.h"

/**
 * Populates data_ary with data corresponding to a straight line from
 * Jakarta to Mecca.  Based on http://krysstal.com/sphertrig.html
 *
 * Add a Second Segment from Mecca to Izmir
 */
bool TestDataSource::read() {
	float* data_temp = new float[10];
	
	for(int i = 0; i < 10; i++)
		data_temp[i] = (i < 3 || i > 5)? 1.0 : 0.0;
	
	//Jakarta to Mecca
	data_ary = Helper::makeStraightLineDataPoints(
			-6.08, //Latitude of Jakarta
			106.45, //Longitude of Jakarta
			65.04, //heading from Jakarta to Mecca
			dataProperties().h_res,
			data_temp,
			(int)ceil(7912000.0/dataProperties().h_res));
	qDebug() << "Jakarta: " << data_ary.first()->lat().degs() << ", "
		<< data_ary.first()->lon().degs();
	qDebug() << "Mecca: " << data_ary.last()->lat().degs() << ", "
		<< data_ary.last()->lon().degs();
	
	//Mecca to Izmir
	data_ary.pop_back();
	data_ary += Helper::makeStraightLineDataPoints(
			21.254, //Latitude of Mecca
			39.5114, //Longitude of Mecca
			29.0, //heading from Mecca to Izmir
			dataProperties().h_res,
			data_temp,
			(int)ceil(2252400.0/dataProperties().h_res));
	qDebug() << "Izmir: " << data_ary.last()->lat().degs() << ", "
		<< data_ary.last()->lon().degs();
	
	return true;

}

QVector<Segment> TestDataSource::segment() {
	QVector<Segment> segments;
	QVectorIterator<DataPoint*> i(data_ary);

	while(i.hasNext()) {
		TestSegment s(this);
		while(i.hasNext() && s.appendOrStop(i.next()));
		segments.append(s);
	}

	return segments;
}
