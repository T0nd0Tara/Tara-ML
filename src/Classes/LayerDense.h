#pragma once
#include "Matrixf.h"
#include "..\Headers.h"
#include "..\ActivationFuncs.h"

class LayerDense{
protected:
	Matrixf* output = new Matrixf();

	// width = nNuerons; hight = nInputs
	Matrixf* weights = new Matrixf();

	Matrixf* biases = new Matrixf();

	float (*af)(float);
	
public:
	LayerDense(int nInputs, int nNeurons, float (*setAF)(float) = af::linear) {

		af = setAF;


		float* setArrWeights = new float[nInputs * nNeurons];

		randArr(setArrWeights, nInputs * nNeurons);

		weights = new Matrixf(setArrWeights, nNeurons, nInputs);
		biases  = new Matrixf(0.0f, nNeurons, 1);

	}

	Matrixf* forward(Matrixf* inputs) {
		//std::cout << "inputs dim: " + inputs->get_dim() << '\n';
		//std::cout << "weights dim: " + weights->get_dim() << "\n\n";
		
		*output = ((*inputs) * (*weights)) + *biases;
		float* tempOutArr = new float[output->get_size()];
		for (int i = 0; i < (output->get_size()); i++) {
			tempOutArr[i] = (*af)(output->get_cell(i));
		}

		output = new Matrixf(tempOutArr, output->get_width(), output->get_height());

		return output;
	}

	friend std::ostream& operator<<(std::ostream& out, LayerDense in) {
		out << "weights:\n";
		out << *in.weights;

		out << "\nbiases:\n";
		out << *in.biases << "\n\n";
		return out;
	}
};

