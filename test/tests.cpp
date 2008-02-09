#include "datasourcetests.h"
#include "segmenttests.h"

int main() {
	
	DataSourceTests data_source_tests;
	QTest::qExec(&data_source_tests);

	SegmentTests segment_tests;
	QTest::qExec(&segment_tests);
	
	return 0;
}
