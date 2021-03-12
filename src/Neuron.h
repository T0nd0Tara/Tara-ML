#pragma once

#include "Headers.h"
struct Neuron
{
protected:
	

public:
	float bias;
	int BatchSize;
	std::vector<float>* inputs;
	std::vector<float>  weights;
	Neuron(std::vector<float>*, std::vector<float>, float, int);

	int maxBatchSize();
	bool ok(std::string*);

	float get_value_by_input(std::vector<float>*);
	void get_values(float*);


	std::string to_string(int, bool);

};

