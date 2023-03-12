#include <stdio.h>

#include "neural_network.h"

static NeuralNetworkParameters neuralNetworkParameters;

static double neural_network_calculate_connected_neurons(Neuron *neuron)
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

static void neural_network_update_weights(Neuron *neuron, float learningRate, double error)
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

static double neural_network_feedforward(NeuralNetworkParameters neuralNetworkParameters, Neuron *sensorNeurons[], Neuron *outNeuron)
{
    double error = .0f;

    int numberFeatures = neuralNetworkParameters.numberFeatures;



    for (int samplesIndex = 0; samplesIndex < neuralNetworkParameters.numberSamples; samplesIndex++)
    {
        for (int sensorIndex = 0; sensorIndex < numberFeatures; sensorIndex++)
        {
            sensorNeurons[sensorIndex]->axonValue = neuralNetworkParameters.trainX[samplesIndex * numberFeatures + sensorIndex];
        }

        double prediction = neural_network_calculate_connected_neurons(outNeuron);
        error += (prediction - neuralNetworkParameters.trainY[samplesIndex]) * (prediction - neuralNetworkParameters.trainY[samplesIndex]);
    }

    return error / neuralNetworkParameters.numberSamples;
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
        printf("Epoch: %d ", epochIndex);
        double error = neural_network_feedforward(neuralNetworkParameters, sensorNeurons, outNeuron);
        printf("error: %.20Lf \n", error);
        neural_network_update_weights(outNeuron, neuralNetworkParameters.learningRate, error);
    }
    printf("===END TRAIN===\n");
}

double neural_network_predict(Neuron *sensorNeurons[], Neuron *outNeuron, float *features)
{
    for (unsigned int indexFeature = 0; indexFeature < neuralNetworkParameters.numberFeatures; indexFeature++)
    {
        sensorNeurons[indexFeature]->axonValue = features[indexFeature];
    }
    
    return neural_network_calculate_connected_neurons(outNeuron);
}