#ifndef COMMON_H
#define COMMON_H
//Defines common includes as well as shared structures

#include <cmath>
#include <iostream>
#include <QObject>
#include <QVector>
#include <QString>
#include <QPair>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QtDebug>

using namespace std;

/** 
 * radius of the earth in meters
 */
#define RADIUS 6378100.0

/**
 * Delicious Pi
 */
#define PI 3.14159265358979

double fuzzy_round(double x, int y);


#endif
