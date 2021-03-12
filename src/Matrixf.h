#pragma once
#include "Headers.h"


class Matrixf
{
private:
	int width, height, size;
	float* arr;
	bool _ok;
public:
	Matrixf(float*, int , int);
	Matrixf(std::vector<float>*, int);
	std::string to_string();
	std::vector<float>* to_vec();

	Matrixf T();
	Matrixf Transpose();

	int get_width()  const {return width;}
	int get_height() const {return height;}
	int get_size() const {return size;}
	
	Matrixf get_row(int);
	Matrixf get_col(int);

	std::vector<float>* get_rowVec(int);
	std::vector<float>* get_colVec(int);


	float* operator[](int index) {
		return &arr[index];
	}

	friend Matrixf operator*(Matrixf a, Matrixf b);
	friend std::ostream& operator<<(std::ostream& out, Matrixf a) {
		out << a.to_string();
		return out;
	}
};


