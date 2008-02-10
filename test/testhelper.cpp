#include "testhelper.h"

namespace TestHelper {

	Segment drawTestLine(DataPoint* from, QString froms, DataPoint* to,
		       	QString tos) {
		float* data = new float[10];
		Segment s;
		s += Helper::makeStraightLineDataPoints(from,
		 	      	to, 10000, data);
		Helper::makeKMLPath(s, QString("kml/%1_to_%2.kml").arg(
					froms).arg(tos));
		return s;
	}
}

