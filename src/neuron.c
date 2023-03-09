#include <stddef.h>
#include <stdbool.h>

#include "memory.h"
#include "neuron.h"
#include "func.h"

void neuron_connect_neurons(Neuron *firstNeuron, Neuron *secondNeuron)
{
    int currentNumberDendrites = secondNeuron->numberDendrites;
    secondNeuron->numberDendrites++;
    if (secondNeuron->dendrites == NULL)
    {
        secondNeuron->dendrites = malloc(secondNeuron->numberDendrites * sizeof(Neuron *));
        secondNeuron->weights = malloc(secondNeuron->numberDendrites * sizeof(long double));
    }
    else
    {
        Neuron **currentDendrite = secondNeuron->dendrites;
        Neuron **newDendrites = malloc(secondNeuron->numberDendrites * sizeof(Neuron *));

        long double *currentWeights = secondNeuron->weights;
        long double *newWeights = malloc(secondNeuron->numberDendrites * sizeof(long double));

        for (int i = 0; i < currentNumberDendrites; i++)
        {
            newDendrites[i] = currentDendrite[i];
            newWeights[i] = currentWeights[i];
        }
        secondNeuron->dendrites = newDendrites;
        secondNeuron->weights = newWeights;
        free(currentDendrite);
        free(currentWeights);
    }
    secondNeuron->dendrites[currentNumberDendrites] = firstNeuron;
    secondNeuron->weights[currentNumberDendrites] = DEFAULT_WEIGHT;
}

static bool neuron_is_sensor_neuron(Neuron *neuron)
{
    return neuron->dendrites == NULL;
}

void neuron_calculate_neuron(Neuron *neuron)
{
    if (neuron_is_sensor_neuron(neuron))
        return;

    long double inputSum = 0;
    for (int i = 0; i < neuron->numberDendrites; i++)
    {
        inputSum += (*neuron->dendrites)[i].axonValue * neuron->weights[i] + neuron->bias;
    }
    neuron->axonValue = func_sigmoid(inputSum);
}

void neuron_update_weight(Neuron *neuron, float learningRate, long double error)
{
    long double out = neuron->axonValue;
    for (unsigned int i = 0; i < neuron->numberDendrites; i++)
    {
        neuron->weights[i] = neuron->weights[i] - learningRate * error * (*neuron->dendrites)[i].axonValue * out * (1 - out);
    }
    neuron->bias = neuron->bias - learningRate * error * out * (1 - out);
}