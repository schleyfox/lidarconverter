#include "lcolorlookup.h"

/**
 * Lookup data in colormap and return color
 */
uint LColorLookup::colorify(float data) {
	int bucket = (int)floor(data*multiplier - b);
	qDebug() << "Looking in Bucket " << bucket;
	QMap<float, uint> colors = m_compcolormap.value(bucket);
	qDebug() << colors.key(0);
	if(data <= colors.key(0)) {
		return colors.value(0);
	}
	for(int i = 1; i < colors.size()-1; i++) {
		if(data <= colors.key(i))
			return colors.value(i);
	}

	return colors.value(colors.size()-1);
}

void LColorLookup::compile() {
	QList<float> keys = colorMap().keys();
	double range = keys.last() - keys.first();
	double total = 0;
	for(int i = 0; i < keys.size(); i++) 
		total += keys.at(i);
	double average = total/((double)keys.size());
	double tmp_v = 0;
	for(int i = 0; i < keys.size(); i++) 
		tmp_v += pow(keys.at(i) - average, 2.0);
	double stdev = sqrt(tmp_v/((double)keys.size()));
	
	double halfstd = stdev/2.0;

	multiplier = 1.0/halfstd;
	b = keys.first();
	
	
	QMapIterator<float, uint> j(colorMap());
	int buckets = (int)floor(range*multiplier);
	for(int i = 0; i < buckets; i++) {
		qDebug() << "Bucket " << i;
		while(j.hasNext()) {
			if(floor(j.peekNext().key()*multiplier - b) <= i) {
				qDebug() << "  Adding " << j.peekNext().key() << " => " << j.peekNext().value();
				(m_compcolormap[i])[j.peekNext().key()] = j.peekNext().value();
				qDebug() << (m_compcolormap[i])[j.next().key()];
			} else {
				break;
			}
		}
	}
}

