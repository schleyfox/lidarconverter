#include "calipsocolormap.h"
/**
 * Creates an LColorLookup for CALIPSO data.
 * This is a slightly modified version of the VTK ColorLookupTable code written
 * by Jonathon Gleason.
 *
 * @author Jonathon Gleason
 */
LColorLookup* makeCalipsoColorMap() {
	QMap<float, uint> cm;
	int numRanges = 33;

	double r[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.274509804, 0.392156863, 0.509803922, 0.607843137, 0.705882353, 0.784313725, 0.882352941, 0.921568627, 0.941176471, 0.949019608, 0.960784314, 0.976470588, 0.992156863, 1};
	double g[] = {0.164705882, 0.164705882, 0.498039216, 0.666666667, 0.831372549, 1, 1, 1, 0.498039216, 0.666666667, 1, 1, 0.831372549, 0.666666667, 0.498039216, 0.333333333, 0, 0.164705882, 0.333333333, 0.498039216, 0.274509804, 0.392156863, 0.509803922, 0.607843137, 0.705882353, 0.784313725, 0.882352941, 0.921568627, 0.941176471, 0.949019608, 0.960784314, 0.976470588, 0.992156863, 1};
	double b[] = {0.666666667, 0.666666667, 1, 1, 1, 1, 0.831372549, 0.666666667, 0.498039216, 0.333333333, 0, 0, 0, 0, 0, 0, 0, 0.333333333, 0.498039216, 0.666666667, 0.274509804, 0.392156863, 0.509803922, 0.607843137, 0.705882353, 0.784313725, 0.882352941, 0.921568627, 0.941176471, 0.949019608, 0.960784314, 0.976470588, 0.992156863, 1};
	double a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	double dataRange[] = {0.0001, 0.0002, 0.0003, 0.0004, 0.0005, 0.0006, 0.0007, 0.0008, 0.0009, 0.001, 0.0015, 0.002, 0.0025, 0.003, 0.0035, 0.004, 0.0045, 0.005, 0.0055, 0.006, 0.0065, 0.007, 0.0075, 0.008, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1};


	int numColors = 33;
	
	int i,j;
	double dataValue;
	int *rangeIndex = new int[numColors];
	int *rangeIndexRunningSum = new int[numColors];
	int *rangeIndexSum = new int[numRanges];
	int indexPtr = 0;

	for(i = 0; i < numRanges; i++)
		rangeIndexSum[i] = 0;

	for(i = 0; i < numColors; i++)
	{
		dataValue = dataRange[0] + ((double)i)/((double)(numColors-1))*(dataRange[numRanges] - dataRange[0]);
		while (dataValue > dataRange[indexPtr+1])
			indexPtr++;
		rangeIndex[i] = indexPtr;
		rangeIndexSum[indexPtr] += 1; 
		rangeIndexRunningSum[i] = rangeIndexSum[indexPtr];
	}
	
	
	double red, green, blue, alpha, range;
	double f;	
	for(i = 0; i < numColors; i++)	
	{
		f = (double)rangeIndexRunningSum[i] / ((double)rangeIndexSum[rangeIndex[i]]);
		range = dataRange[rangeIndex[i]]*(1-f) + dataRange[rangeIndex[i]+1]*f;
		red   = r[rangeIndex[i]]*(1-f) + r[rangeIndex[i]+1]*f;
		green = g[rangeIndex[i]]*(1-f) + g[rangeIndex[i]+1]*f;
		blue  = b[rangeIndex[i]]*(1-f) + b[rangeIndex[i]+1]*f;
		alpha = a[rangeIndex[i]]*(1-f) + a[rangeIndex[i]+1]*f;
		cm[range] = qRgba(red*255, green*255, blue*255, alpha*255);
		qDebug() << "<color_range>";
		qDebug() << "  <base_value>" << range << "</base_value>";
		qDebug() << "  <color>"<< QString::number(cm[range], 16) << "</color>";
		qDebug() << "</color_range>";
	}

	LColorLookup* lut = new LColorLookup;

	return lut;
}
