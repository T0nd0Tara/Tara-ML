#include "Headers.h"


int main() {
	const int neurons = 3;
	const int BatchSize = 1;
	std::vector<float> inputs     = {   1.0f,    2.0f,   3.0f,   2.5f,
									    2.0f,    5.0f,  -1.0f,   2.0f,
									   -1.5f,    2.7f,   3.3f,  -0.8f};

	std::vector<float> weights[neurons] = { { 0.2f,    0.8f,  -0.5f,   1.0f  },
											{ 0.5f,   -0.91f,  0.26f, -0.5   },
											{-0.26f, -0.27f,  0.17f,  0.87f } };

	const int length = inputs.size() / (weights[0].size() * BatchSize); // The length of values each nueron send

	
	float bias[3] = {2.0f, 3.0f, 0.5f};
	Layer layer(&inputs, weights, bias, neurons, BatchSize);

	

	if (layer.ok())
		std::cout << layer.to_string();
	else
		std::cout << "Layer not ok\n";


	float *outs = new float[length * neurons];

	layer.get_outs(outs);

	std::cout << arrToString(outs, length * neurons, length) << "\n\n";

	Transpose(outs, length * neurons, length);

	std::cout << arrToString(outs, length * neurons, length) << "\n\n\n";
	



	return 0;
}