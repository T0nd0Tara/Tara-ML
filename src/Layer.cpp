#include "Layer.h"


Layer::Layer(std::vector<float>* inputs, std::vector<float>* weights, float* bias, int neurons, int BatchSize = -1) {
	vecInputs = inputs;
	nNeurons = neurons;
	
	if (BatchSize == -1)
		BatchSize = vecInputs->size() / weights->size();



	for (int i = 0; i < neurons; i++) {
		Neuron* Temp = new Neuron(inputs, *weights, *bias, BatchSize);
		std::string Error;
		if (Temp->ok(&Error))
			vecNeurons.push_back(Temp);
		else {
			std::cout << "Neuron not ok: " + Error + '\n';
			throw std::invalid_argument("Neuron not ok: " + Error);
			_ok = false;
			return;
		}
			
		weights++;
		bias++;
	}
}

bool Layer::ok() const{
	return _ok;
}

std::string Layer::to_string() {
	std::string out;
	out += "Inputs: ";
	out += vecToString(vecInputs);
	out += '\n';

	for (int indN = 0; indN < nNeurons; indN++) {
		out += "Neuron #" + std::to_string(indN) + ":\n";
		out += vecNeurons[indN]->to_string(1, false);
		out += '\n';
	}

	return out;
}

Neuron* Layer::operator[](int index) {
	return vecNeurons[index];
}

void Layer::get_outs(float* out) {
	
	for (int indN = 0; indN < vecNeurons.size(); indN++) {

		vecNeurons[indN]->get_values(out);
		out += vecInputs->size() / (vecNeurons[indN]->BatchSize * vecNeurons[indN]->weights.size());
	}
}