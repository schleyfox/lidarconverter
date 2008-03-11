#ifndef SEGMENTWORKER_H
#define SEGMENTWORKER_H
#include "common.h"
#include "segment.h"
#include "datasource.h"
#include "curvetransform.h"
#include "lcolorlookup.h"
#include "calipsocolormap.h"
#include <QThread>

class SegmentWorker : public QThread {
	public:
	SegmentWorker(LColorLookup* cl) : QThread() {
		lut = cl;
	}
	QVector<Segment> segments() {
		return m_segments;
	}
	void addSegment(Segment s) {
		m_segments << s;
	}

	void run();
	
	protected:
	QVector<Segment> m_segments;
	LColorLookup* lut;
};
	
#endif

