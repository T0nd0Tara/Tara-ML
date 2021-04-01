#define OLC_PGE_APPLICATION

#include "Headers.h"
#include "Classes/Matrixf.h"
#include "Classes/LayerDense.h"
#include "Classes/Neuron.h"
#include "Classes/Layer.h"
#include "ActivationFuncs.h"
#include "DataGenerators.h"
#include "Visuelizer.h"


#include "olcPixelGameEngine.h"



int main() {

	srand(time(NULL));

	int classes = 3;
	std::vector<std::pair<int, int>>* vec = new std::vector<std::pair<int, int>>[classes];
	std::vector<std::pair<float, float>>* vecf = new std::vector<std::pair<float, float>>[classes];
	dgs::spiralDots2d(1000, 10, classes, vec, 1.0f, 0.5f, 0.5f);
	//drawPoints(1000, 1, classes, vec);

	convert<int, float>(vec, vecf, classes);
	Matrixf matInputs = Matrixf(vecf);
	//const int neurons = 5;
	//const int BatchSize = 1;
	/*std::vector<float> inputs     = {   1.0f,    2.0f,   3.0f,   2.5f,
										2.0f,    5.0f,  -1.0f,   2.0f,
									   -1.5f,    2.7f,   3.3f,  -0.8f};
	Matrixf matInputs = {&inputs , (int)4 };*/

	
	LayerDense layer1(2, 5, af::softmax);

	

	std::cout << layer1 << '\n';

	Matrixf out = *layer1.forward(&matInputs);
	std::cout << out << '\n';




	//LayerDense layer2(5, 2, af::sigmoid);
	//std::cout << *layer2.forward(layer1.forward(&matInputs)) << "\n\n";
	
	

	return 0;
}