#pragma once
#include "Headers.h"

namespace af {

inline float linear(float in) {
	return in;
}
inline float ReLU(float in) {
	if (in <= 0.0f)
		return 0.0f;

	return in;
}

inline float sigmoid(float in) {
	return 1.0f /(1.0f + exp(-in));
}


inline Matrixf softmax(Matrixf in) {
	if (in.get_height() != 1) {
		throw std::invalid_argument("The softmax activaition function, cannot get more than 1 value per neuron\n");
		return in;
	}

	Matrixf normVals(0.0f, in.get_size(), 1);
	
	std::vector<long double> expVals;

	expVals.resize(in.get_size());

	long double sumExp = 0.0f;

	for (int i = 0; i < in.get_size(); i++) {
		// the std::min makes sure that the resulting value could be represented by float type
		long double tempExp  = expl(std::min((long double)in[i], (long double)11355.0));
		if (tempExp > 1e+300)
			tempExp = 1e+300;
		expVals[i] = tempExp;
		sumExp += tempExp;
	}

	for (int i = 0; i < in.get_size(); i++) {
		normVals.set_cell(i, expVals[i] / sumExp);
	}

	// deleting unused memory 
	expVals.clear();
	expVals.shrink_to_fit();

	return normVals;
}
}