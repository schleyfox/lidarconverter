#ifndef LCOLORLOOKUP_H
#define LCOLORLOOKUP_H
#include "common.h"

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

	virtual uint colorify(float data);
	
	/**
	 * Optimize colormap for fast lookups
	 */
	void compile();

	protected:
	QHash<int, QMap<float, uint> > m_compcolormap;
	QMap<float, uint> m_colormap;
	double multiplier;
	double b;


};

#endif
