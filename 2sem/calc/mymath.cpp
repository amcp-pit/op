#include "mymath.h"

double sign(double x) {
	return x==0 ? 0 : (x<0 ? -1.0 : 1.0);
}

double sqr(double x) {
	return x*x;
}
