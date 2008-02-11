#ifndef HDF4OBJECT_H
#define HDF4OBJECT_H

#include "mfhdf.h"
#include <string>
#include <iostream>
#include <fstream>

/** 
 * hdf4object.h
 * HDF4Object Class
 * A more objective way to read data from HDF files.
 *
 * @author T. Nelson Hillyer, DEVELOP National Program, NASA
 * 
 * date: August 15, 2007
 * version: 0.3 (BETA)
 */
class hdf4object
{
	public:
		hdf4object(std::string* filename);
		~hdf4object();

		std::string* getDataSets();
		int getNumberOfSets();
		int getSetRank(std::string* setName);
		int* getSetDimensions(std::string* setName);
		template <class T>
		T** setToArray(std::string* setName);
		template <class T>
		bool setToFile(std::string* setName, std::string* fileName);
		template <class T>
		void freeArray(T** array);
	
	private:
		int sd_id, sds_id;
		int status;
		int n_datasets, n_file_attrs, index;
		int dim_sizes[MAX_VAR_DIMS];
		int rank, data_type, n_attrs;

		char name[MAX_NC_NAME];
		std::string* setNames;
		int* setRank;
		int** setDimensions;
};


#endif
