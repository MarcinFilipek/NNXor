#ifndef NEURON_H_
#define NEURON_H_

struct Neuron_struct
{
    struct Neuron_struct **dendryts;
    int numberDendryts;
    int debug_id;
    long double *weights;
    long double aksonValue;
    long double bias;
};

typedef struct Neuron_struct Neuron;

#define DEFAULT_WEIGHT 0.1

extern void neuron_connect_neurons(Neuron *firstNeuron, Neuron *secondNeuron);
extern void neuron_calculate_neuron(Neuron *neuron);
extern void neuron_update_weight(Neuron *neuron, float learningRate, long double error);

#endif // NEURON_H_