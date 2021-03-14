#include "Matrixf.h"

Matrixf::Matrixf(float* setArr, int setWidth, int setHeight) { // for array
	_ok = true;
	_Error = "";
	
	width = setWidth;
	height = setHeight;

	size = width * height;

	arr = new float[size];

	
	for (int i = 0; i < size; i++) {
		arr[i] = *setArr;
		setArr++;
	}
}
Matrixf::Matrixf(std::vector<float>* setVec, int setWidth) { // for vector
	_ok = true;
	_Error = "";


	width = setWidth;
	height = setVec->size() / setWidth;

	size = setVec->size();

	arr = new float[size];

	for (float* i = arr; i < arr + size; i++) {
		*i = (*setVec)[i - arr];
	}

}

Matrixf::Matrixf(std::vector<float>* setVec, int setHeight, bool ArrayOfVectors) { // for array of vectors
	_ok = true;
	_Error = "";


	if (!ArrayOfVectors) {
		_ok = false;
		_Error += "Can not define Matrixf type with {std::vector<float>*, int, false} - For array of vector, initialize list have to be {std::vector<float>*, int, true}\n";
		return;
	}

	// making a copy of setVec
	std::vector<float>* setVecDup = setVec;


	// checking if input is ok
	width = setVec->size();
	for (int i = 0; i < setHeight - 1; i++) {
		setVec++;
		if (width != setVec->size()) {
			// Error
			_ok = false;
			_Error += "Can not have different sized rows inside of Matrixf type.\n";
			return;
		}
	}


	height = setHeight;
	size = width * height;
	// initialize
	arr = new float[size];
	for (int i = 0; i < height; i++) {
		vecToArr(setVecDup, arr + i*width);
		setVecDup++;
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

bool Matrixf::ok(std::string* out) const {
	*out = _Error;
	return _ok;
}

Matrixf operator*(Matrixf a, float alpha) {
	float* newArr = new float[a.size];

	for (int i = 0; i < a.size; i++) {
		newArr[i] = alpha * a.arr[i];
	}
	return Matrixf(newArr, a.width, a.height);
}

Matrixf operator*(float alpha, Matrixf a) {
	return a * alpha;
}

Matrixf operator*(Matrixf a, Matrixf b) {
	if (b.get_height() != a.get_width()) {
		// Error

		std::cout << "Matrix mult error: b.height != a.width";
		throw std::invalid_argument("Matrix mult error: b.height != a.width : b.height = "
			+ std::to_string(b.get_height()) + "; a.width = " + std::to_string(a.get_width()));
		
		return a;
	}

	if (a.get_height() != b.get_width()) {
		// Error

		std::cout << "Matrix mult error: a.height != b.width";
		throw std::invalid_argument("Matrix mult error: a.height != b.width : a.height = "
			+ std::to_string(a.get_height()) + "; b.width = " + std::to_string(b.get_width()));
		
		return a;
	}

	float* out = new float[a.get_height() * b.get_width()];

	for (int y = 0; y < a.get_height(); y++) {
		for (int x = 0; x < b.get_width(); x++) {
			out[x + y * b.get_width()] = dotProd(a.get_rowVec(y), b.get_colVec(x));
		}
	}
	return Matrixf(out, b.get_width(), a.get_height());

}

Matrixf operator+(Matrixf a, float b) {
	float* out = new float[a.size];
	for (int i = 0; i < a.size; i++) {
		out[i] = a.arr[i] + b;
	}
	return Matrixf(out, a.width, a.height);
}

Matrixf operator+(float a, Matrixf b) {
	return b + a;
}

bool is1x1(Matrixf);
Matrixf operator+(Matrixf a, Matrixf b) {
	if (a.height != b.height && std::min(a.height, b.height) > 1) {
		throw std::invalid_argument("Can not add matrices if heights are different, and no height is 1.");
		return a;
	}

	if (a.width != b.width && std::min(a.width, b.width) > 1) {
		throw std::invalid_argument("Can not add matrices if widths are different, and no width is 1.");
		return a;
	}

	if (a.height == b.height && a.width == b.width) {
		float* newArr = new float[a.size];

		for (int i = 0; i < a.size; i++) {
			newArr[i] = a.arr[i] + b.arr[i];
		}
		return Matrixf(newArr, a.width, a.height);
	}


	// when a or b is 1x1
	if (is1x1(a)) {
		return b + a.arr[0];
	}
	if (is1x1(b)) {
		return a + b.arr[0];
	}


	// regular cases
	if (a.height == 1) {
		float* newArr = new float[b.size];

		for (int y = 0; y < b.height; y++)
			for (int x = 0; x < b.width; x++) {
				newArr[x + y * b.width] = b.arr[x + y * b.width] + a.arr[x];
			}
		return Matrixf(newArr, b.width, b.height);
	}
	if  (b.height == 1){
		float* newArr = new float[a.size];

		for (int y = 0; y < a.height; y++)
			for (int x = 0; x < a.width; x++) {
				newArr[x + y * a.width] = a.arr[x + y * a.width] + b.arr[x];
			}
		return Matrixf(newArr, a.width, a.height);
	}



	// copied code for widths

	if (a.width == 1) {
		float* newArr = new float[b.size];

		for(int y = 0; y < a.height; y++)
			for (int x = 0; x < b.width; x++) {
				newArr[x + y * b.width] = b.arr[x + y * b.width] + a.arr[y];
			}
		return Matrixf(newArr, b.width, b.height);
	}else { // b.width == 1
		float* newArr = new float[a.size];

		for (int y = 0; y < b.height; y++)
			for (int x = 0; x < a.width; x++) {
				newArr[x + y * a.width] = a.arr[x + y * a.width] + b.arr[y];
			}
		return Matrixf(newArr, a.width, a.height);
	}


}

bool is1x1(Matrixf a) {
	return (a.get_width() == 1 && a.get_height() == 1);
}