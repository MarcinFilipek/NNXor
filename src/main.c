#include <stdlib.h>
#include <stdio.h>

#include "neuron.h"
#include "neural_network.h"

#define NUMBER_FEATURES 2
#define EPOCHS 10
#define LEARNING_RATE 0.1

int main()
{
    Neuron sensorNeuron1 = {.debug_id = 1, .bias = 1};
    Neuron sensorNeuron2 = {.debug_id = 2, .bias = 1};

    Neuron n1l0 = {.debug_id = 3, .bias = 1};
    Neuron n2l0 = {.debug_id = 4, .bias = 1};

    Neuron n1l1 = {.debug_id = 5, .bias = 1};

    neuron_connect_neurons(&sensorNeuron1, &n1l0);
    neuron_connect_neurons(&sensorNeuron2, &n1l0);

    neuron_connect_neurons(&sensorNeuron1, &n2l0);
    neuron_connect_neurons(&sensorNeuron2, &n2l0);

    neuron_connect_neurons(&n1l0, &n1l1);
    neuron_connect_neurons(&n2l0, &n1l1);

    float trainX[][NUMBER_FEATURES] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
    float trainY[] = {0, 1, 0, 1};

    Neuron *sensorNeurons[] = {&sensorNeuron1, &sensorNeuron2};

    neural_network_fit(NUMBER_FEATURES, 4, sensorNeurons, &n1l1, (float *)trainX, trainY, EPOCHS, LEARNING_RATE);

    float testX[NUMBER_FEATURES] = {0, 1};
    double pred = neural_network_predict(sensorNeurons, &n1l1, testX);
    printf("Predict: %.20Lf\n", pred);
    return 0;
}