#include "lcolorlookup.h"

/**
 * Lookup data in colormap and return color
 */
uint LColorLookup::colorify(float data, CLUTNode* node = 0) {
	if(!node)
		node = colormap_root;
	if(data < node->lbound) {
		return colorify(data, node->less);
	} else if(data > note->ubound) {
		return colorify(data, node->more);
	}
	return color;
}

void LColorLookup::compile() {
	//Pad to Infinity
	m_colormap[NEGINF] = m_colormap.values().first();
	m_colormap[INF] = m_colormap.values().last();
	
	QList<float> keys = m_colormap.keys();
	QList<uint> values = m_colormap.values();
	QList<CLUTNode*> ranges;
	for(int i = 0; i < keys.size()-1; i++) {
		CLUTNode* cn = new CLUTNode;
		cn->lbound = keys.at(i);
		cn->ubound = keys.at(i+1);
		cn->color = values.at(i);
		ranges << cn;
	}
	colormap_root = build(ranges);
}

CLUTNode* build(QVector<CLUTNode*> ranges) {
	if(ranges.size() == 0) {
		return 0;
	}

	QList<CLUTNode*> p_1, p2;
	CLUTNode* root;
	int length_i = (int)floor((double)ranges.size()/2.0);
	root = ranges.takeAt(length_i);
	p_1 = ranges.mid(0,length_i);
	p_2 = ranges.mid(length_i);
	
	root->less = build(p_1);
	root->more = build(p_2);
	return root;
}
