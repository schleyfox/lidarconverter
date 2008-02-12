#ifndef CURVE_TRANSFORM_H
#define CURVE_TRANSFORM_H

#include "common.h"
#include "segment.h"
#include "datasource.h"
#include "lcolorlookup.h"
#include <QImage>
#include <math.h>
#include <iostream>
#include <exception>

/*! \mainpage CALIPSO converter
 * CALIPSO converter is a utility to convert CALIPSO backscatter curtain files into PNGs that can be viewed in Google Earth.  The program uses a polar coordinate conversion to curve the data to fit the earth.
 *
 * CALIPSO converter is designed to work with CALIPSO data but it can also process other data with a similar schema.
 */


/** \struct CartesianPair
 * Represents a Cartesian coordinate pair
 */
typedef struct {
	double x;
	double y;
} CartesianPair;

/** \struct PolarPair
 * Represents a polar coordinate pair
 */
typedef struct {
	double theta;
	double r;
} PolarPair;

/** CurveTransform
 * This class abstracts the generation of a curved image according to polar coordinates.
 * 
 * In this class <i>unit</i> refers to the "real-world" unit of measurement (meters, feet, furlongs) while <i>pixel</i> refers to the actual image pixel representation.
 */
class CurveTransform {
public:
	
	/**
	 * \param img The image to be curved. 
	 * \warning If theta (image's horizontal dimensions times the horizontal resolution divided by radius) is greater than 90 degrees, an exception will be thrown.
	 */
	CurveTransform(QImage img, Segment s, LColorLookup* lut);
	
	/**
	 * Convert rectangular image to a curved image
	 * \return The new, processed image ready for writing or further processing
	 */
	QImage transform();
	
protected:
	
	/**
	 * Convert rectangular image coordinates into polar coordinates
	 * \param coords The row and column in the image to be curved.
	 * \return The polar coordinate (r and theta) equivalent of the image location curved around the radius
	 */
	PolarPair convertToPolar(CartesianPair coords);

	/**
	 * Convert polar coordinates to cartesian (r*cos(theta), etc.
	 */
	CartesianPair convertToCartesian(PolarPair coords);

	/**
	 * Convert cartesian coordinates into new image coordinates
	 */
	CartesianPair convertToPixels(CartesianPair coords);

	/**
	 * Copy pixels from source to the new curved canvas.
	 */
	void drawPixels(CartesianPair coords, CartesianPair source);

	
	/**
	 * Convert a horizontal coordinate into a pixel at the horizontal resolution
	 */
	double convertHCoord(double x);

	/**
	 * Convert a vertical coordinate into a pixel at the vertical resolution
	 */
	double convertVCoord(double y);

	/**
	 * Convert a horizontal pixel into the internal coordinate system
	 */
	double convertHPixel(double x);

	/**
	 * Convert a vertical pixel into the internal coordinate system
	 */
	double convertVPixel(double y);

	double pi;
	double radius;
	double h_res;
	double v_res;

	double base_angle;
	double theta;

	double altitude;

	QImage image;
	QImage out_image;

	double height;
	double width;

	double drop_factor;

	double image_width;
	double image_height;

	Segment segment;
	LColorLookup* lut;
};



//int round_i(double foo);

#endif
