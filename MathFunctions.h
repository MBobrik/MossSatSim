#pragma once
#include "Math3D.h"

// TODO: add all mathematical functions that can be (re)used in multiple components, but aren't strictly 3D Math here




// interpolates smoothly between 0, and 1 as t changes from 0 to 1 so that
// 
// X(0) = 0, dX/dt(0) = 0
// X(1) = 1, dX/dt(1) = 0

// interpolation polynomial 
//
// X = t^2*(3-2t)

inline double InterpolateSmooth01(double t) {
	if(t<=0) { return 0;}
	if(t>=1) { return 1; }
	return t * t * ( 3 - 2 * t); 
}


// interpolates smoothly between lo, and hi as t changes from 0 to 1 so that
// 
// X(0) = lo, dX/dt(0) = 0
// X(1) = hi, dX/dt(1) = 0

// interpolation polynomial 
//
// X = a*t^3 + b*t^2 + c*t + d
//
// a = -2*(hi-lo)
// b =  3*(hi-lo)
// c = 0
// d = lo
inline double InterpolateSmooth(double lo, double hi, double t) {
	if(t<=0) { return lo;}
	if(t>=1) { return hi; }
	return lo + (hi-lo) *InterpolateSmooth01(t); 
}

// interpolates smoothly between lo, mid, and hi as t changes from 0 to 1 so that
// 
// X(0) = lo, dX/dt(0) = 0
// x(0.5) = mid
// X(1) = hi, dX/dt(1) = 0

// interpolation polynomial 
//
// X = a*t^4 + b*t^3 + c*t^2 + d*t + e
//
// a = - 8*(hi-lo) + 16*(mid-lo) 
// b =  14*(hi-lo) - 32*(mid-lo)
// c = - 5*(hi-lo) + 16*(mid-lo)
// d = 0
// e = lo
inline double InterpolateSmooth(double lo, double mid, double hi, double t) {
	if(t<=0) { return lo;}
	if(t>=1) { return hi; }
	double m = mid - lo, h = hi - lo, t2 = t*t;
	return lo + t2 * (16*m-5*h) + t2*t *(14*h-32*m) + t2*t2 * (16*m-8*h); 
}

// interpolates smoothly between 0 and 1 , as t changes from 0 to 1 so that when t = t_half the value is 0.5
// 
// X(0) = 0, dX/dt(0) = 0
// x(t_half) = 1/2 
// X(1) = 0, dX/dt(1) = 0

// interpolation polynomial 
//
// X = a*t^4 + b*t^3 + c*t^2
//
// a = (0.5/t^2+2*t-3)/(t-1)^2 
// b = -2*(1+a)
// c = 3+a
inline double InterpolateSmoothTHalf( double t_half, double t) {
	if(t<=0) { return 0;}
	if(t>=1) { return 1; }

	double t_half2 = t_half*t_half;
	double t_halfm = 1 - t_half;
	double a = ( 0.5/t_half2 + 2*t_half - 3 )/( t_halfm*t_halfm );
	double b = -2 *( 1 + a );
	double c = 3 + a;
	double t2 = t*t;
	return a*t2*t2 + b*t2*t + c*t2;
}


