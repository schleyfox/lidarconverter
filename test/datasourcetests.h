#include <QtTest/QtTest>
#include "testdatasource.h"
#include "calipsol1datasource.h"
#include "segment.h"

class DataSourceTests: public QObject {
	Q_OBJECT
	
	private slots:
	void read();
	void calipsoRead();
	void segment();
};
