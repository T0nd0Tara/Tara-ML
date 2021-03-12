#pragma once

#include "Headers.h"

struct Neuron;
class Layer
{
protected:
	std::vector<Neuron*> vecNeurons;
	std::vector<float> *vecInputs;
	int nNeurons;
	bool _ok = true;
public:
	Layer(std::vector<float>*, std::vector<float>*, float*, int, int);
	bool ok() const;
	std::string to_string();
	Neuron* operator[](int);

	void get_outs(float*);
};

