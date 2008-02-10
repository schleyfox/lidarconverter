#ifndef TESTHELPER_H
#define TESTHELPER_H

#include "common.h"
#include "segment.h"
#include "helper.h"

#define DRAW_TEST_LINE(from, to) TestHelper::drawTestLine(from, #from, to, #to)

namespace TestHelper {

	Segment drawTestLine(DataPoint* from, QString froms, DataPoint* to,
		       	QString tos); 
}

#endif
