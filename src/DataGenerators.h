#pragma once
#include "Headers.h"
#include "Classes/Matrixf.h"


// data generators
namespace dgs {

inline void spiralDots2d(int screenSize, int points, int classes, std::vector<std::pair<int,int>>* out, float  tErr = 1.0f, float xErr = 1.0f, float yErr = 1.0f, float rOffset = 0.0f) {
	// screenSize := determin the radius of the spirals so they wil fit in the screen
	//
	// points := the number of points per class
	//
	// out := an array of vectors of pairs.
	//		  each vector is a different class, and each pair is a different point in the class
	//
	// tErr := an error on the line of the spiral between -tErr to tErr
	//
	// xyErr := an error range of wich the point will go
	//
	// rOffset := offsetting the radius
	

	// radius
	float r = (float)screenSize;
	r *= 8.0f / (float)points;
	r += rOffset;

	auto rx = [](float x, float y, float a) {return x * cosf(a) - y * sinf(a); };
	auto ry = [](float x, float y, float a) {return y * cosf(a) + x * sinf(a); };

	for (int _class = 0; _class < classes; _class++) {
		// init
		out->resize(points);

		float dirSpiral = TWO_PI * rand0_1();

		for (int point = 0; point < points; point++) {
			float t = (float)point * 0.1f + rand_1_1() * tErr;

			t *= exp(-t / 100.0f);

			float tcost = t * cosf(t);
			float tsint = t * sinf(t);

			(*out)[point] = { round(r * (rx(tsint, tcost, dirSpiral) + rand_1_1() * xErr)),
							  round(r * (ry(tsint, tcost, dirSpiral) + rand_1_1() * yErr)) };
		

		}

		out++;
	}


}

}