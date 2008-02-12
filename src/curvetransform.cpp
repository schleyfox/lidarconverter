//#include "stdafx.h"
#include "curvetransform.h"
#include <iostream>
#include <stdio.h>



CurveTransform::CurveTransform(QImage img, Segment s, LColorLookup* lut){
	this->lut = lut;
	this->segment = s;
	this->pi = PI;
	this->radius = RADIUS; 
	this->h_res = s.dataSource()->dataProperties().h_res;
	this->v_res = s.dataSource()->dataProperties().v_res;
	this->image = img;
	this->image_width = s.size();
	this->image_height = s.dataSource()->dataProperties().height;

	/***
	Calculate geometry variables
	***/
	theta = s.fullAngle().degs();
	if(theta >= pi/2) {
		std::cerr << "FATAL ERROR: Angle Theta is greater than 90 degrees" << std::endl;
		throw 42;
	}

	altitude = convertVPixel(s.droppingDistance()); 

	base_angle = (pi - theta)/2; //the base angle normalizes the midpoint to the 90degree axis


	drop_factor = sin(base_angle)*radius;

	//Proper code for image size calculation
	height = s.width();
	width = s.length(); 
	
	out_image = QImage((int)ceil(width), (int)ceil(height), QImage::Format_ARGB32); 
	
	std::cout << "H: " << height << " W: " << width << " Theta " << theta << " Altitude " << altitude << " DropFactor " << drop_factor << std::endl;
}

QImage CurveTransform::transform() {
	for(unsigned int i = 0; i < image_width; i++) {
		for(unsigned int j = 0; j < image_height; j++) {
			CartesianPair coords = {i, j};
			drawPixels(convertToPixels(convertToCartesian(convertToPolar(coords))),coords); //Lisp, eat your heart out
		}
	}
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
	if(coords.x < out_image.width() && coords.y < out_image.height() && coords.x >= 0 && coords.y >= 0) {
		out_image.setPixel((int)coords.x, (int)coords.y, 
				lut->colorify(segment.at((int)source.x)->data()[(int)source.y]));
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

