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

}