#include <stdio.h>

#include "neural_network.h"

static NeuralNetworkParameters neuralNetworkParameters;

static long double neural_network_calculate_connected_neurons(Neuron *neuron)
{
    if (neuron->numberDendrites)
    {
        for (int i = 0; i < neuron->numberDendrites; i++)
        {
            neural_network_calculate_connected_neurons(neuron->dendrites[i]);
        }
    }
    neuron_calculate_neuron(neuron);
    return neuron->axonValue;
}

static void neural_network_update_weights(Neuron *neuron, float learningRate, long double error)
{
    neuron_update_weight(neuron, learningRate, error);

    if (neuron->numberDendrites)
    {
        for (int i = 0; i < neuron->numberDendrites; i++)
        {
            neural_network_update_weights(neuron->dendrites[i], learningRate, error);
        }
    }
}

static long double neural_network_feedforward(NeuralNetworkParameters neuralNetworkParameters, Neuron *sensorNeurons[], Neuron *outNeuron)
{
    long double error = .0f;

    int numberFeatures = neuralNetworkParameters.numberFeatures;

    for (int samplesIndex = 0; samplesIndex < neuralNetworkParameters.numberSamples; samplesIndex++)
    {
        for (int sensorIndex = 0; sensorIndex < numberFeatures; sensorIndex++)
        {
            sensorNeurons[sensorIndex]->axonValue = neuralNetworkParameters.trainX[samplesIndex * numberFeatures + sensorIndex];
        }
        long double prediction = neural_network_calculate_connected_neurons(outNeuron);
        printf("Pred: %.20Lf, target: %.20f\n", prediction, neuralNetworkParameters.trainY[samplesIndex]);
        error += -2 * (prediction - neuralNetworkParameters.trainY[samplesIndex]);
    }
    return error;
}

void neural_network_fit(int numberFeatures, int numberSamples, Neuron *sensorNeurons[], Neuron *outNeuron, float *trainX, float *trainY, int numberEpochs, float learningRate)
{
    neuralNetworkParameters.learningRate = learningRate;
    neuralNetworkParameters.numberEpochs = numberEpochs;
    neuralNetworkParameters.numberSamples = numberSamples;
    neuralNetworkParameters.numberFeatures = numberFeatures;
    neuralNetworkParameters.trainX = trainX;
    neuralNetworkParameters.trainY = trainY;

    for (int epochIndex = 0; epochIndex < neuralNetworkParameters.numberEpochs; epochIndex++)
    {
        printf("Epoch: %d \n", epochIndex);
        long double error = neural_network_feedforward(neuralNetworkParameters, sensorNeurons, outNeuron);
        neural_network_update_weights(outNeuron, neuralNetworkParameters.learningRate, error);
        printf("Error: %.20Lf \n", error);
    }
    printf("===END TRAIN===\n");
}

long double neural_network_predict(Neuron *sensorNeurons[], Neuron *outNeuron, float *features)
{
    for (unsigned int indexFeature = 0; indexFeature < neuralNetworkParameters.numberFeatures; indexFeature++)
    {
        sensorNeurons[indexFeature]->axonValue = features[indexFeature];
    }
    return neural_network_calculate_connected_neurons(outNeuron);
}