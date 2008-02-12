#ifndef LCOLORLOOKUP_H
#define LCOLORLOOKUP_H
#include "common.h"

#define NEGINF -1000000000.0
#define INF 1000000000.0

struct CLUTNode {
	double lbound;
	double ubound;
	uint color;
	CLUTNode* less;
	CLUTNode* more;
};

/**
 * ColorLookup Provides a simple interface to color a set of values based on
 * a range stored in m_colormap.
 */
class LColorLookup {
	public:
	
	/**
	 * Instantiates a ColorLookup table
	 */
	LColorLookup() {
	}
	virtual ~LColorLookup() { }

	QMap<float, uint> colorMap() {
		return m_colormap;
	}
	
	void setColorMap(QMap<float, uint> colormap) {
		m_colormap = colormap;
	}

	virtual uint colorify(float data, CLUTNode* node = 0);
	
	/**
	 *  Make colormap into Binary Search Tree
	 */
	void compile();

	protected:
	CLUTNode* build(QList<CLUTNode*> ranges);

	CLUTNode* colormap_root;
	QMap<float, uint> m_colormap;


};

#endif
