#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#define INPUT_SIZE 4
#define HIDDEN_SIZE 6
#define OUTPUT_SIZE 1

typedef struct {
    double weights_ih[INPUT_SIZE][HIDDEN_SIZE];
    double bias_h[HIDDEN_SIZE];
    double weights_ho[HIDDEN_SIZE][OUTPUT_SIZE];
    double bias_o[OUTPUT_SIZE];
} NeuralNetwork;

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

void drawBoard(int paddle2Y, int ballX, int ballY) {
    system("cls");

    for (int i = 0; i < 24; i++) {
        gotoxy(0, i);
        printf("|");
    }

    gotoxy(78, paddle2Y);
    printf("|");

    gotoxy(ballX, ballY);
    printf("O");

    for (int i = 0; i < 80; i++) {
        gotoxy(i, 0);
        printf("-");
        gotoxy(i, 24);
        printf("-");
    }
}

int main() {
    int paddle2Y = 10;
    int ballX = 40, ballY = 12;
    int ballSpeedX = -1, ballSpeedY = 1;

    NeuralNetwork nn;
    initNeuralNetwork(&nn);

    while (1) {
        double inputs[INPUT_SIZE] = { (double)paddle2Y, (double)ballX, (double)ballY };
        double output = feedforward(&nn, inputs);

        int action = (output > 0.5) ? 1 : -1;

        if (ballY < paddle2Y && paddle2Y > 1) {
            paddle2Y--;
        }
        if (ballY > paddle2Y + 2 && paddle2Y < 23) {
            paddle2Y++;
        }

        ballX += ballSpeedX;
        ballY += ballSpeedY;

        if (ballY == 0 || ballY == 24) {
            ballSpeedY = -ballSpeedY;
        }
        if (ballX == 1) {
            ballSpeedX = -ballSpeedX;
        }
        if (ballX == 78 && (ballY >= paddle2Y && ballY <= paddle2Y + 3)) {
            ballSpeedX = -ballSpeedX;
        }

        if (ballX == 0 || ballX == 79) {
            ballX = 40;
            ballY = 12;
        }

        drawBoard(paddle2Y, ballX, ballY);
        Sleep(10);
    }

    return 0;
}