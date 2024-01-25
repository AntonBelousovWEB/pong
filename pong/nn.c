#include "global.h"

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

void initNeuralNetwork(NeuralNetwork* nn) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < INPUT_SIZE; ++i)
        for (int j = 0; j < HIDDEN_SIZE; ++j)
            nn->weights_ih[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

    for (int i = 0; i < HIDDEN_SIZE; ++i)
        nn->bias_h[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

    for (int i = 0; i < HIDDEN_SIZE; ++i)
        for (int j = 0; j < OUTPUT_SIZE; ++j)
            nn->weights_ho[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;

    for (int i = 0; i < OUTPUT_SIZE; ++i)
        nn->bias_o[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
}

double feedforward(NeuralNetwork* nn, double inputs[INPUT_SIZE]) {
    double hidden[HIDDEN_SIZE];
    for (int i = 0; i < HIDDEN_SIZE; ++i) {
        hidden[i] = 0.0;
        for (int j = 0; j < INPUT_SIZE; ++j)
            hidden[i] += inputs[j] * nn->weights_ih[j][i];
        hidden[i] += nn->bias_h[i];
        hidden[i] = sigmoid(hidden[i]);
    }

    double output = 0.0;
    for (int i = 0; i < OUTPUT_SIZE; ++i) {
        output += hidden[i] * nn->weights_ho[i][0];
    }
    output += nn->bias_o[0];
    output = sigmoid(output);

    return output;
}

void train(NeuralNetwork* nn, double inputs[INPUT_SIZE], double target) {
    double learningRate = 0.1;

    double hidden[HIDDEN_SIZE];
    double output;
    for (int i = 0; i < HIDDEN_SIZE; ++i) {
        hidden[i] = 0.0;
        for (int j = 0; j < INPUT_SIZE; ++j)
            hidden[i] += inputs[j] * nn->weights_ih[j][i];
        hidden[i] += nn->bias_h[i];
        hidden[i] = sigmoid(hidden[i]);
    }

    output = 0.0;
    for (int i = 0; i < OUTPUT_SIZE; ++i) {
        output += hidden[i] * nn->weights_ho[i][0];
    }
    output += nn->bias_o[0];
    output = sigmoid(output);

    double outputError = target - output;
    double outputDelta = outputError * output * (1.0 - output);

    for (int i = 0; i < HIDDEN_SIZE; ++i) {
        nn->weights_ho[i][0] += learningRate * outputDelta * hidden[i];
    }
    nn->bias_o[0] += learningRate * outputDelta;

    double hiddenErrors[HIDDEN_SIZE];
    for (int i = 0; i < HIDDEN_SIZE; ++i) {
        hiddenErrors[i] = outputDelta * nn->weights_ho[i][0];
    }

    for (int i = 0; i < HIDDEN_SIZE; ++i) {
        double hiddenDelta = hiddenErrors[i] * hidden[i] * (1.0 - hidden[i]);
        for (int j = 0; j < INPUT_SIZE; ++j) {
            nn->weights_ih[j][i] += learningRate * hiddenDelta * inputs[j];
        }
        nn->bias_h[i] += learningRate * hiddenDelta;
    }
}