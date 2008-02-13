/* container.h
 * Stores the data read in from CALIPSO data files to be passed to the file
 * generation functions.
 *
 * Written by: T. Nelson Hillyer & Nicholas Gasperoni
 * Date: July 24, 2007
 */
#ifndef CONTAINER_H
#define CONTAINER_H

#include <QString>

class container
{
	public:
		container();
		QString name;
		double initLat, endLat;
		double initLong, endLong;
		double midLat, midLong;
		double heading;
		double altitude;
		double width, length;
};

container::container() { }

#endif
