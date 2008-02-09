#include "datasourcetests.h"

int main() {
	
	DataSourceTests data_source_tests;
	QTest::qExec(&data_source_tests);

	return 0;
}
