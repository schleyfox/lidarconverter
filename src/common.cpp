#include "common.h"

/**
 * a simple solution for rounding
 *
 * @param x the floating point to fuzz round
 * @param y number of places to round
 */
double fuzzy_round(double x, int y) {
               int multiplier = pow(10.0,(double)y);
       double x1 = x*multiplier;
       return ceil(x1-0.5)/multiplier;
}
