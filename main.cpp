#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
//#include <time.h>

class Rocket {
public:
    int startX;
    int startY;
    int nextXR1;
    int nextYR1;
};

class Ball {
public:
    int startX;
    int startY;
    int speedX = 1;
    int speedY = 1;
    int nextX;
    int nextY;
};

class Game {
public:
    bool game_over = false;
    int height;
    int width;
    int score1;
    int score2;
    Ball ball;
    Rocket R1;
    Rocket R2;

public:
    Game(int height, int width) : height(height), width(width) {
    };

    Game() : height(0), width(0) {
    };

    void printField(Ball &ball, Rocket &R1, Rocket &R2) {
        system("clear");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == R1.nextXR1 && j == R1.nextYR1) {
                    std::cout << "=";
                } else if (i == R1.nextXR1 && j == R1.nextYR1 + 1) {
                    std::cout << "=";
                } else if (i == R1.nextXR1 && j == R1.nextYR1 + 2) {
                    std::cout << "=";
                } else if (i == ball.nextY && j == ball.nextX)
                    std::cout << "*";
                else if (i == 0 || i == height - 1)
                    std::cout << "#";
                else if (j == 0 || j == width)
                    std::cout << "#";
                else std::cout << " ";
            }
            std::cout << "#\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void stepGame(Ball &ball) {
        if (ball.nextY == 1) {
            ball.speedY *= -1;
        }
        if (ball.nextY == height - 2) {
            ball.speedY *= -1;
        }
        if (ball.nextX == width - 1) {
            ball.speedX *= -1;
        }
        if (ball.nextX == 1) {
            ball.speedX *= -1;
        }
        ball.nextX += ball.speedX;
        ball.nextY += ball.speedY;
    }

    void RocketLeft1() {
        R1.startX = 1;
        R1.startY = 1;
    }

    int gameplay() {
        if (kbhit()) {
            char input1 = getch();
            switch (input1) {
                case ('a'):
                    std::cout << "LEFT";
                    break;
                case ('d'):
                    std::cout << "RIGHT";
                    break;
            }
        }

        return 0;
    }
};


int main() {
    Ball ball;
    Rocket R1;
    Rocket R2;
    Game game(11, 31);
    ball.startX = game.width / 2;
    ball.startY = game.height / 2;
    ball.nextX = ball.startX;
    ball.nextY = ball.startY;
    game.ball = ball;
    while (1) {
        game.printField(ball, R1, R2);
        game.stepGame(ball);
        game.gameplay();
    }
    return 0;
}
