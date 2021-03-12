#include "Matrixf.h"

Matrixf::Matrixf(float* setArr, int setWidth, int setHeight) {
	width = setWidth;
	height = setHeight;

	size = width * height;

	arr = new float[size];

	_ok = true;
	
	for (int i = 0; i < size; i++) {
		arr[i] = *setArr;
		setArr++;
	}
}
Matrixf::Matrixf(std::vector<float>* setVec, int setWidth) {
	width = setWidth;
	height = setVec->size() / setWidth;

	size = setVec->size();

	arr = new float[size];

	_ok = true;

	for (float* i = arr; i < arr + size; i++) {
		*i = (*setVec)[i - arr];
	}

}

std::string Matrixf::to_string() {
	std::string out = "{ ";
	for (int i = 0; i < size; i++) {
		out += std::to_string(arr[i]);

		if (i + 1 != size) {
			out += ',' + addSpace(11 - len(arr[i+1]));

			if ((i + 1) % width == 0)
				out += "\n" + addSpace(10 - len(arr[i+1]));
		}
	}

	out += " }";
	return out;
}
std::vector<float>* Matrixf::to_vec() {
	std::vector<float>* out = new std::vector<float>();

	for (int i = 0; i < size; i++) {
		out->push_back(arr[i]);
	}

	return out;
}
Matrixf Matrixf::T() {
	float* out = new float[size];


	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			out[x + height * y] = arr[y + width * x];
		}
	}

	return Matrixf(out, height, width);
}

Matrixf Matrixf::Transpose() {
	return this->T();
}

Matrixf Matrixf::get_row(int ind) {
	float* data = new float[width];

	for (int x = 0; x < width; x++) {
		data[x] = arr[x + ind * width];
	}

	return Matrixf(data, width, 1);
}

Matrixf Matrixf::get_col(int ind) {
	float* data = new float[height];

	for (int y = 0; y < height; y++) {
		data[y] = arr[ind + y * width];
	}

	return Matrixf(data, 1, height);
}

std::vector<float>* Matrixf::get_rowVec(int ind) {
	return get_row(ind).to_vec();
}

std::vector<float>* Matrixf::get_colVec(int ind) {
	return get_col(ind).to_vec();
}

Matrixf operator*(Matrixf a, Matrixf b) {
	if (b.get_height() != a.get_width()) {
		// Error

		std::cout << "Matrix mult error: b.height != a.width";
		throw std::invalid_argument("Matrix mult error: b.height != a.width : b.height = "
			+ std::to_string(b.get_height()) + "; a.width = " + std::to_string(a.get_width()));
		
		return Matrixf(a.arr, a.get_width(), a.get_height());
	}

	if (a.get_height() != b.get_width()) {
		// Error

		std::cout << "Matrix mult error: a.height != b.width";
		throw std::invalid_argument("Matrix mult error: a.height != b.width : a.height = "
			+ std::to_string(a.get_height()) + "; b.width = " + std::to_string(b.get_width()));
		
		return Matrixf(a.arr, a.get_width(), a.get_height());
	}

	float* out = new float[a.get_height() * b.get_width()];

	for (int y = 0; y < a.get_height(); y++) {
		for (int x = 0; x < b.get_width(); x++) {
			out[x + y * b.get_width()] = dotProd(a.get_rowVec(y), b.get_colVec(x));
		}
	}
	return Matrixf(out, b.get_width(), a.get_height());

}

