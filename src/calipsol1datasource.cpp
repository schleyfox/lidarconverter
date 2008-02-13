#include "calipsol1datasource.h"
#include "hdf4object.h"

bool CalipsoL1DataSource::read() {
	hdf4object* data = new hdf4object(new string(filename().toAscii().data()));

	
	string* tab = new string("Total_Attenuated_Backscatter_532");
	float** tab_array = data->setToArray<float>(new string("Total_Attenuated_Backscatter_532")     );
	string* lon = new string("Longitude");
	float** tmplons = data->setToArray<float>(lon);
	float* lons = tmplons[0];
	string* lat = new string("Latitude");
	float** tmplats = data->setToArray<float>(lat);
	float* lats = tmplats[0];
	int* dims = data->getSetDimensions(tab);
	delete tab;
	delete lon;
	delete lat;
	
	//fucking data is upside down
	for(int i = 0; i < dims[0]; i++) {
		float* dp_ary = new float[dataProperties().height];
		float* column = tab_array[i];
		column += 80;
		//crop array bounds to [298] - [698]
		for(int j = 0; j < 200; j++)  {
			dp_ary[(2*j)+1] = dp_ary[2*j] = column[j];
		}
		
		float* dp_ary2 = dp_ary + 400;
		column += 200;
		//crop array bounds to [8] - [298]
		memcpy(dp_ary2, column, 290*sizeof(float));
			
		
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
