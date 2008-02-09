#include <QtTest/QtTest>
#include "testdatasource.h"
#include "segment.h"

class DataSourceTests: public QObject {
	Q_OBJECT
	
	private slots:
	void read();
	void segment();
};
