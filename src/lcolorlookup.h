#ifndef LCOLORLOOKUP_H
#define LCOLORLOOKUP_H
#include "common.h"

#define NEGINF -1000000000000000000000000000000000000000000000000000000000000.0
#define INF     1000000000000000000000000000000000000000000000000000000000000.0

/** @struct CLUTNode
 * Forms a node in the binary search tree that forms the lookup table
 *
 * @note automatically handled by LColorLookup::compile()
 */
struct CLUTNode {
	/**
	 * Lower bound of the scalar range that gets the color in 
	 * CLUTNode.color
	 */
	double lbound;

	/**
	 * The upper bound of the scalar range
	 */
	double ubound;
	
	/**
	 * RGBA color for values in the range
	 * 
	 * generated through qRgba() in many cases
	 */
	uint color;
	
	/**
	 * pointer to left branch with value ranges less than the current
	 */
	CLUTNode* less;
	
	/**
	 * pointer to right branch
	 */
	CLUTNode* more;
};

/**
 * ColorLookup Provides a simple interface to color a set of values based on
 * a range stored in m_colormap.
 *
 * @see LidarConverterTests::LColorLookup_colorify()
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
	
	/**
	 * Sets the color map to the provided QMap. This should then be
	 * compiled into a fast binary search tree.
	 *
	 * @see makeCalipsoColorMap()
	 */
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
