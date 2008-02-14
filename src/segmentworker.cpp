#include "segmentworker.h"
#include "kmlbuilder.h"

void SegmentWorker::run() {
	LColorLookup* lut = makeCalipsoColorMap();
	for(int i = 0; i < m_segments.size(); i++) {
		CurveTransform ct(m_segments.at(i), lut);
		ct.transform().save(
			QString("images/%1.png").arg(
				m_segments.at(i).segmentName()), "PNG");
	}
	KMLBuilder builder(QDir("./kmlbuilder/"), QDir("./images/"));
	builder.generateFiles(m_segments);
}
