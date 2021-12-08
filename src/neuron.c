#include <stddef.h>
#include <stdbool.h>

#include "memory.h"
#include "neuron.h"
#include "func.h"

void neuron_connect_neurons(Neuron *firstNeuron, Neuron *secondNeuron)
{
    int currentNumberDendryts = secondNeuron->numberDendryts;
    secondNeuron->numberDendryts++;
    if (secondNeuron->dendryts == NULL)
    {
        secondNeuron->dendryts = malloc(secondNeuron->numberDendryts * sizeof(Neuron *));
        secondNeuron->weights = malloc(secondNeuron->numberDendryts * sizeof(long double));
    }
    else
    {
        Neuron **currentDendryts = secondNeuron->dendryts;
        Neuron **newDendryts = malloc(secondNeuron->numberDendryts * sizeof(Neuron *));

        long double *currentWeights = secondNeuron->weights;
        long double *newWeights = malloc(secondNeuron->numberDendryts * sizeof(long double));

        for (int i = 0; i < currentNumberDendryts; i++)
        {
            newDendryts[i] = currentDendryts[i];
            newWeights[i] = currentWeights[i];
        }
        secondNeuron->dendryts = newDendryts;
        secondNeuron->weights = newWeights;
        free(currentDendryts);
        free(currentWeights);
    }
    secondNeuron->dendryts[currentNumberDendryts] = firstNeuron;
    secondNeuron->weights[currentNumberDendryts] = DEFAULT_WEIGHT;
}

static bool neuron_is_sensor_neuron(Neuron *neuron)
{
    return neuron->dendryts == NULL;
}

void neuron_calculate_neuron(Neuron *neuron)
{
    if (neuron_is_sensor_neuron(neuron))
        return;

    long double inputSum = 0;
    for (int i = 0; i < neuron->numberDendryts; i++)
    {
        inputSum += (*neuron->dendryts)[i].aksonValue * neuron->weights[i] + neuron->bias;
    }
    neuron->aksonValue = func_sigmoid(inputSum);
}

void neuron_update_weight(Neuron *neuron, float learningRate, long double error)
{
    long double out = neuron->aksonValue;
    for (unsigned int i = 0; i < neuron->numberDendryts; i++)
    {
        neuron->weights[i] = neuron->weights[i] - learningRate * error * (*neuron->dendryts)[i].aksonValue * out * (1 - out);
    }
    neuron->bias = neuron->bias - learningRate * error * out * (1 - out);
}