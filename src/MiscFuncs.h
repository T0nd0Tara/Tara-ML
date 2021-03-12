#pragma once

#include "Headers.h"



inline float dotProd(std::vector<float>* a, std::vector<float>* b) {
	if (a->size() != b->size()) {
		throw std::invalid_argument("Cannot do dot product with to different sized arrays");
		std::cout << "An 'std::invalid_argument' error has occured in dotProd.\n";
		return 0.0f;
	}

	float sum = 0.0f;
	for (int i = 0; i < a->size(); i++)
		sum += (*a)[i] * (*b)[i];

	return sum;
}

inline void dotProd(std::vector<float>* a, std::vector<float>* b, int size, float* out) {
	for (int i = 0; i < size; i++) {
		*out = dotProd(a, b);
		out++;
		a++;
	}
}


inline void vecToArr(std::vector<float>* in, float* out) {
	for (int i = 0; i < in->size(); i++) {
		*out = (*in)[i];
		out++;
	}
}

inline int len(float);
inline std::string addSpace(int);

inline std::string arrToString(float* in, int size) { // don't drop
	std::string out = "{";
	for (int i = 0; i < size; i++) {
		out += std::to_string(*in);
		in++;
		if (i + 1 != size)
			out += ',' + addSpace(11 - len(in[i + 1]));
	}
	out += '}';
	return out;
}



inline std::string arrToString(float* in, int size, int drop) {
	std::string out = "{ ";
	for (int i = 0; i < size; i++) {
		out += std::to_string(in[i]);

		if (i + 1 != size) {
			out += ',' + addSpace(11 - len(in[i + 1]));

			if ((i + 1) % drop == 0)
				out += "\n" + addSpace(10 - len(in[i + 1]));
		}
	}

	out += " }";
	return out;
}
inline std::string vecToString(std::vector<float>* in) {
	std::string out = "{";
	
	for (int i = 0; i < in->size(); i++) {
		out += std::to_string((*in)[i]);
		if (i + 1 != in->size())
			out += ',' + addSpace(11 - len((*in)[i+1]));
	}
	out += '}';

	return out;
}

inline std::string addTabs(int n) {
	std::string out;
	for (int indT = 0; indT < n; indT++) out += '\t';
	return out;
}

inline std::string addSpace(int n) {
	std::string out;
	for (int indT = 0; indT < n; indT++) out += ' ';
	return out;
}

inline void Transpose(float* io, int size, int new_line) {
	if (size % new_line != 0) {
		std::cout << "An error has occured in Transpose.\n";
		return;
	}
	float* temp_out = new float[size];

	
	for (int y = 0; y < size / new_line; y++) {
		for (int x = 0; x < new_line; x++) {
			temp_out[x + new_line * y] = io[y + new_line * x];
		}
	}


	// puting back temp_out into io
	for (int y = 0; y < size / new_line; y++) {
		for (int x = 0; x < new_line; x++) {
			io[x + y * new_line] = temp_out[x + y * new_line];
		}
	}
	
}

inline int len(float in) {
	return std::to_string(in).length();
}
