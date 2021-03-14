#include "Headers.h"
#include "Classes/Matrixf.h"
#include "Classes/LayerDense.h"
#include "Classes/Neuron.h"
#include "Classes/Layer.h"
#include "ActivationFuncs.h"

int main() {
	const int neurons = 5;
	const int BatchSize = 1;
	std::vector<float> inputs     = {   1.0f,    2.0f,   3.0f,   2.5f,
									    2.0f,    5.0f,  -1.0f,   2.0f,
									   -1.5f,    2.7f,   3.3f,  -0.8f};
	Matrixf matInputs = {&inputs , (int)4 };

	LayerDense layer1(4, neurons, af::ReLU);

	LayerDense layer2(neurons, 2, af::sigmoid);



	std::cout << *layer2.forward(layer1.forward(&matInputs)) << "\n\n";

	return 0;
}