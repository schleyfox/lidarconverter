//#include "stdafx.h"
#include "curvetransform.h"
#include <iostream>
#include <stdio.h>



CurveTransform::CurveTransform(QImage img, Segment s){
	this->radius = RADIUS; 
	this->h_res = s.dataSource()->dataProperties().base_horiz_res;
	this->v_res = s.dataSource()->dataProperties().max_altitude;
	this->image = img;
	this->image_width = dims[0];
	this->image_height = dims[1];

	/***
	Calculate geometry variables
	***/
	theta = convertHPixel(image_width)/radius; //angle between start and end point of dataset
	std::cout << convertHPixel(image_width) << std::endl;
	std::cout << image_width << std::endl;
	if(theta >= pi/2) {
		std::cerr << "FATAL ERROR: Angle Theta is greater than 90 degrees" << std::endl;
		throw 42;
	}

	double c1 = 2*sin(theta/2)*radius; //chord 1: chord from start point to end point through the earth
	double c2 = 2*sin(theta/4)*radius; //chord 2: chord from mid point to end point
	double B = c1/2; //base: base of triangle formed in the intersection of chord2, the radius at half theta, and chord 1
	altitude = sqrt(pow(c2,2)-pow(B,2)); //distance between chord 1 and peak of the bottom arc

	base_angle = (pi - theta)/2; //the base angle normalizes the midpoint to the 90degree axis

	double theta2 = (pi/2)-(theta/2);
	double width_x = convertHCoord(convertVPixel(image_height)*cos(theta2));

	drop_factor = sin(base_angle)*radius;

	//Proper code for image size calculation
	height = convertVCoord(altitude)+ image_height;// the height of the image is the altitude + height of the image
	width = (2*width_x)+ convertHCoord(c1);
	
	out_image = Image(Geometry((int)ceil(width), (int)ceil(height)), "none"); 
	out_image.modifyImage();
	
	std::cout << "H: " << height << " W: " << width << " Theta " << theta << " Altitude " << altitude << " DropFactor " << drop_factor << std::endl;
}

Image CurveTransform::transform() {
	for(unsigned int i = 0; i < image_width; i++) {
		for(unsigned int j = 0; j < image_height; j++) {
			CartesianPair coords = {i, j};
			drawPixels(convertToPixels(convertToCartesian(convertToPolar(coords))),coords); //Lisp, eat your heart out
			if(j%100 == 0) {
				out_image.syncPixels();
			}
		}
	}
	out_image.syncPixels();
	return out_image;	
}

PolarPair CurveTransform::convertToPolar(CartesianPair coords) {
	PolarPair result;
	result.theta = convertHPixel(coords.x)/radius; //find theta part of polar coord
	result.theta += base_angle;
	result.r = convertVPixel(coords.y)+radius;  //find radius part of polar coord
	return result;
}

CartesianPair CurveTransform::convertToCartesian(PolarPair coords) {
	CartesianPair result;
	result.x = coords.r*cos(coords.theta);
	result.y = coords.r*sin(coords.theta);
	return result;
}

CartesianPair CurveTransform::convertToPixels(CartesianPair coords) {
	CartesianPair result;
	result.x = convertHCoord(coords.x);
	result.x += width/2; //horizontal shift to  elliminate negative coordinates
	result.y = convertVCoord(coords.y);
	result.y -= convertVCoord(drop_factor);
	return result;
}

void CurveTransform::drawPixels(CartesianPair coords, CartesianPair source) {
	//bounds check
	if(coords.x < out_image.baseColumns() && coords.y < out_image.baseRows() && coords.x >= 0 && coords.y >= 0) {
		*(out_image.setPixels(coords.x, coords.y, 1, 1)) = *(image.getConstPixels(source.x, source.y, 1, 1));
		out_image.syncPixels();
	} else {
		std::cerr << "ERROR: Out of bounds pixel coordinate (" << coords.x << ", " << coords.y << ")." << std::endl;
	}
}

double CurveTransform::convertHCoord(double x) {
	return x/h_res;
}

double CurveTransform::convertVCoord(double y) {
	return y/v_res;
}

double CurveTransform::convertHPixel(double x) {
	return x*h_res;
}

double CurveTransform::convertVPixel(double y) {
	return y*v_res;
}
/*
int round_i(double foo) {
	if(foo - floor(foo) >= .5) {
		return ceil(foo);
	} else {
		return floor(foo);
	}
}
*/

