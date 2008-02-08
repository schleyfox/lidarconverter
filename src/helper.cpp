#include "helper.h"

/**
 * Wrapper around Helper::makeStraightLineCoordinates() that returns a vector
 * of DataPoints()
 *
 * @param data a float array that is assigned to each DataPoint()
 * @return a vector of DataPoints
 * @see makeStraightLineCoordinates()
 */ 
QVector<DataPoint*> Helper::makeStraightLineDataPoints(
		double init_lat, double init_lon,
	       	double heading, double spacing,
	    	float* &data, int n) {
	QVector< QPair<Angle,Angle> > coords = 
		makeStraightLineCoordinates(init_lat, init_lon, heading,
			       	spacing, n);
	QVector<DataPoint*> dps;
	for(int i = 0; i < coords.size(); i++) {
		DataPoint* dp = new DataPoint();
		dp->setLat(coords[i].first);
		dp->setLon(coords[i].second);
		dp->setData(data);
		dps.append(dp);
	}
	qDebug() << QString("Start: %1, %2").arg(
			dps.first()->lat().degs()).arg(
			dps.first()->lon().degs());
	qDebug() << QString("End: %1, %2").arg(
			dps.last()->lat().degs()).arg(
			dps.last()->lon().degs());
	return dps;
}

/**
 * For testing purposes it is often desired to make a straight line along a
 * heading with a defined spacing for n points. This is calculated using 
 * spherical trigonometry 
 *
 * @param init_lat initial latitude (in degrees)
 * @param init_lon initial longitude (in degrees)
 * @param heading (in degrees)
 * @param spacing space between datapoints (in meters)
 * @param n number of datapoints
 *
 * @return a vector of (Latitude, Longitude) coordinate pairs
 *
 * \f$\phi_1=90^\circ -\arccos (\cos a\cos (90^\circ -\phi_0)+\sin 
 * a\sin (90^\circ -\phi_0)\cos C)\f$
 *
 * \f$\lambda_1=\arcsin (\frac{\sin a\sin C}{\sin(90^\circ -\phi_1)})+\lambda_0\f$
 */
QVector< QPair<Angle,Angle> > Helper::makeStraightLineCoordinates(
		double init_lat, double init_lon, 
		double heading, double spacing, int n) {
	QVector< QPair<Angle,Angle> > coords;
	Angle A, B, C, a, b, c;
	C = Angle::Degrees(-1.0 * heading);
	b = Angle::Degrees(90.0 - init_lat);

	for(int i = 0; i < n; i++) {
		//law of cosines
		a = Angle::Radians( ((double)i*spacing)/RADIUS );
		c = Angle::Radians( acos( cos(a.rads())*cos(b.rads()) +
				sin(a.rads())*sin(b.rads())*cos(C.rads())));

		//law of sines
		A = Angle::Radians( asin( sin(a.rads())*sin(C.rads()) /
					sin(c.rads())) );

		coords.append(QPair<Angle, Angle>(
				Angle::Degrees(90.0 - c.degs()),
				Angle::Degrees(A.degs() + init_lon)));
	}
	return coords;

}
