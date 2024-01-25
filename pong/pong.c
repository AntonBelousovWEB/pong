#include "global.h"

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