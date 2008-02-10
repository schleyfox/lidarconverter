#include <QtTest/QtTest>
#include "testdatasource.h"
#include "segment.h"
#include "testhelper.h" 

class SegmentTests: public QObject {
	Q_OBJECT
	
	private slots:
	void heading();
	void fullAngle();
	void halfAngle();
	void fullAngleChord();
	void halfAngleChord();
	void base();
	void droppingDistance();
	void externalAngle();
	void leftoverLength();
	void segLength();
	void segWidth();
};
