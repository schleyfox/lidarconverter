bool CalipsoL1DataSource::read() {
	hdf4object* data = new hdf4object(new string(filename().toAscii().data()));
	
	string* tab = new string("Total_Attenuated_Backscatter_532");
	float** tab_array = test->setToArray<float>(tab);
	string* lon = new string("Longitude");
	float* lons = test->setToArray<float>(lon);
	string* lat = new string("Latitude");
	float* lats = test->setToArray<float>(lat);
	int* dims = test->getSetDimensions(tab);
	delete tab;
	delete lon;
	delete lat;

	for(int i = 0; i < dims[0]; i++) {
		float* dp_ary = new float[dataProperties().height];
		float* column = tab_array[i];
		//crop array bounds to [8] - [498]
		column += 8;
		memcpy(dp_ary, column, 490*sizeof(float));
		
		DataPoint* dp = new DataPoint;
		dp->setLon(lons[i]); dp->setLat(lats[i]);
		dp->setData(dp_ary);
		data_ary << dp;
	}
	test->freeArray<float>(tab_array);
	test->freeArray<float>(lons);
	test->freeArray<float>(lats);

	return true;
}
