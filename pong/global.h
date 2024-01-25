#ifndef _GLOBAL
#define _GLOBAL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define INPUT_SIZE 4
#define HIDDEN_SIZE 6
#define OUTPUT_SIZE 1

typedef struct {
    double weights_ih[INPUT_SIZE][HIDDEN_SIZE];
    double bias_h[HIDDEN_SIZE];
    double weights_ho[HIDDEN_SIZE][OUTPUT_SIZE];
    double bias_o[OUTPUT_SIZE];
} NeuralNetwork;

void drawBoard(int paddle2Y, int ballX, int ballY);

void initNeuralNetwork(NeuralNetwork* nn);
double feedforward(NeuralNetwork* nn, double inputs[INPUT_SIZE]);
void train(NeuralNetwork* nn, double inputs[INPUT_SIZE], double target);

#endif // _GLOBAL
