#include "segmentworker.h"

void SegmentWorker::run() {
	for(int i = 0; i < m_segments.size(); i++) {
		CurveTransform ct(m_segments.at(i), lut);
		ct.transform().save(
			QString("./images/%1.png").arg(
				m_segments.at(i).segmentName()), "PNG");
	}
}
