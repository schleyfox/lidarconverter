#include "dynamicdatasource.h"

/**
 * Read in data and set DataProperties to the proper values
 * based on the Dynamic attributes for this class
 */
bool DynamicDataSource::read() {
	//compute the size and resolution of the normalized data structure
	QList<int> res = resolutions().values();
	qSort(res);
	min_res = res.first();

	QList<int> alts = resolutions().keys();


	int max_height = 0;
	for(int i = 0; i < alts.size(); i++) {
		if(alts.at(i+1) > alts.at(i) &&
			       	alts.at(i+1) <  maxAltitude()) {
			max_height += (int)ceil((alts.at(i+1) 
						- alts.at(i))/min_res);
		} else {
			max_height += (int)ceil((maxAltitude() - alts.at(i))/
					min_res);
			break;
		}
	}
	
	//set properties
	m_properties.max_altitude = maxAltitude();
	m_properties.h_res = baseHorizontalResolution();
	m_properties.v_res = min_res;
	m_properties.height = max_height;

	//initialize data source and read from hdf
	hdf4object* data = new hdf4object(
			new string(filename().toAscii().data()));
	string* tab = new string(dataName().toAscii().data());
	float** tab_array = data->setToArray<float>(tab);
	string* lon = new string(longitudeDataName().toAscii().data());
	float** tmplons = data->setToArray<float>(lon);
	float* lons = tmplons[0];
	string* lat = new string(latitudeDataName().toAscii().data());
	float** tmplats = data->setToArray<float>(lat);
	float* lats = tmplats[0];
	int* dims = data->getSetDimensions(tab);
	delete tab;
	delete lon;
	delete lat;

	for(int i = 0; i < dims[0]; i++) {
		float* dp_ary = new float[dataProperties().height];
		copyData(tab_array[i], dp_ary);
		DataPoint* dp = new DataPoint;
		dp->setLon(lons[i]); dp->setLat(lats[i]);
		dp->setData(dp_ary);
		data_ary << dp;
	}
	data->freeArray<float>(tab_array);
	data->freeArray<float>(tmplons);
	data->freeArray<float>(tmplats);

	return true;
}

void DynamicDataSource::copyData(float* source, float* sink) {
	QList<int> alts = resolutions().keys();
	QMap<int, int> multipliers;
	for(int i = 0; i < alts.size(); i++) {
		multipliers[alts.at(i)] = (int)fuzzy_round(
				resolutions().value(alts.at(i))/min_res, 0);
	}
	//copy data into the DataPoint float array
	for(int i = 0; i < alts.size(); i++) {
		int t = 0;
		bool b = false;
		if(alts.at(i+1) > alts.at(i) &&
				alts.at(i+1) < maxAltitude()) {
			t = (int)fuzzy_round((alts.at(i+1)-alts.at(i))/
				resolutions().value(alts.at(i)), 0);
		} else {
			t = (int)fuzzy_round((maxAltitude()-alts.at(i))/
				resolutions().value(alts.at(i)), 0);
			b = true;
		}
		int m = multipliers.value(alts.at(i));
		for(int j = 0; j < t; j++) {
			for(int k = 0; k < m; k++) {
				sink++ = source;
			}
			source++;
		}
		
		if(b)
			break;
	}

}

