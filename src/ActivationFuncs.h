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

	Matrixf expVals(0.0f, in.get_size(), 1), normVals(0.0f, in.get_size(), 1);
	

	float sumExp = 0.0f;

	for (int i = 0; i < in.get_size(); i++) {
		float tempExp = exp(in[i]);
		expVals.set_cell(i, tempExp);
		sumExp += tempExp;
	}

	for (int i = 0; i < in.get_size(); i++) {
		normVals.set_cell(i, expVals[i] / sumExp);
	}

	//delete& expVals, & sumExp;
	return normVals;
}
}