#ifndef NEURAL_NETWORK_H_
#define NEURAL_NETWORK_H_

#include "neuron.h"

typedef struct
{
    float learningRate;
    int numberEpochs;
    int numberSamples;
    int numberFeatures;
    float *trainX;
    float *trainY;
} NeuralNetworkParameters;

extern void neural_network_fit(
    int numberFeatures,
    int numberSamples,
    Neuron *sensorNeurons[],
    Neuron *outNeuron,
    float *trainX,
    float *trainY,
    int numberEpochs,
    float learninRate);

extern long double neural_network_predict(Neuron *sensorNeurons[], Neuron *outNeuron, float *features);

#endif // NEURAL_NETWORK_H_