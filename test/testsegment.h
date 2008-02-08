#ifndef TESTSEGMENT_H
#define TESTSEGMENT_H
#include "segment.h"

class TestSegment: public Segment {
	public:
	TestSegment(DataSource* ds = 0) : Segment(ds) {
		partition_threshold = 1;
	}
};
#endif
