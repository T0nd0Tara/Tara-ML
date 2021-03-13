#include "Neuron.h"

Neuron::Neuron(std::vector<float>* setInp, std::vector<float> setWei, float setBias = 0.0f, int setBatchSize = 1) {
	inputs = setInp;
	weights = setWei;
	bias = setBias;

	BatchSize = setBatchSize;
}
int Neuron::maxBatchSize() {
	return inputs->size() / weights.size();
}
bool Neuron::ok(std::string* Error) {
	if (inputs->size() % weights.size() != 0) {
		*Error = "inputs size (" + std::to_string(inputs->size())
			+ ") is incompaible with weights size (" + std::to_string(weights.size())
			+ ").\n (inputs->size() % weights.size() != 0)";

		throw std::invalid_argument(*Error);
		return false;
	}

	if (maxBatchSize() % BatchSize != 0) {
		*Error = "BatchSize (" + std::to_string(BatchSize)
			+ ") is incompaible with weights and inputs sizes (" + std::to_string(weights.size())
			+ ", "+ std::to_string(inputs->size())
			+ ").\n ((inputs->size() / weights.size()) % BatchSize != 0)";

		throw std::invalid_argument(*Error);
		return false;
	}

	if (BatchSize * weights.size() > inputs->size()) {
		*Error = "BatchSize too big, max Batch size = "
			+ std::to_string(maxBatchSize())
			+ "; Current BatchSize = " + std::to_string(BatchSize);

		throw std::invalid_argument(*Error);
		return false;
	}

	if (inputs->size() % (BatchSize * weights.size()) != 0) {
		*Error = "inputs->size() % (BatchSize * weights.size()) != 0";

		throw std::invalid_argument(*Error);
		return false;
	}

	return true;
}

float Neuron::get_value_by_input(std::vector<float>* input) {
	float out = bias;
	std::vector<float>* newVec = new std::vector<float>();
	for (int i = 0; i < BatchSize; i++) {
		newVec = new std::vector<float>(input->begin() + ( i      * weights.size()),
			 							input->begin() + ((i + 1) * weights.size()));

		out += dotProd(newVec, &weights);

	}

	delete newVec;
	return out;
}

void Neuron::get_values(float* outArr){

	std::vector<float>* newVec = new std::vector<float>();
	for (int i = 0; i < inputs->size() / (weights.size() * BatchSize); i++) {
		newVec = new std::vector<float>(inputs->begin() +  i      * weights.size() * BatchSize,
										inputs->begin() + (i + 1) * weights.size() * BatchSize);
		*outArr = get_value_by_input(newVec);

		outArr++;
		
	}

	delete newVec;
}

std::string Neuron::to_string(int tabs = 0, bool send_inputs = false) {
	std::string out;
	out += addTabs(tabs);

	if (send_inputs) {
		out += "Inputs: ";
		out += vecToString(inputs);
		out += '\n';

		out += addTabs(tabs);
	}

	out += "Weights: ";

	out += vecToString(&weights);
	
	out += "\n";
	out += addTabs(tabs);

	out += "bias: " + std::to_string(bias);

	out += '\n';
	out += addTabs(tabs);

	float* valOuts = new float[inputs->size() / (BatchSize * weights.size())];
	get_values(valOuts);

	out += "values: ";

	out += arrToString(valOuts, inputs->size() / (BatchSize * weights.size()));

	out += "\n";

	return out;
}