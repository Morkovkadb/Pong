#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
//#include <time.h>

class Rocket {
public:
    int startXR1;
    int startYR1;
    int startXR2;
    int startYR2;
    int nextXR1;
    int nextYR1;
    int nextXR2;
    int nextYR2;
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
    int score1 = 0;
    int score2 = 0;
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
        std::cout << "First player: " << score1 << "\tSecond player: " << score2 << "\n";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == R1.nextXR1 && i == R1.nextYR1) {
                    std::cout << "=";
                } else if (j == R1.nextXR1 + 1 && i == R1.nextYR1) {
                    std::cout << "=";
                } else if (j == R1.nextXR1 - 1 && i == R1.nextYR1) {
                    std::cout << "=";
                } else if (j == R2.nextXR2 && i == R2.nextYR2) {
                    std::cout << "=";
                } else if (j == R2.nextXR2 + 1 && i == R2.nextYR2) {
                    std::cout << "=";
                } else if (j == R2.nextXR2 - 1 && i == R2.nextYR2) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
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

    int gameplay(Rocket &R1, Rocket &R2) {
        if (kbhit()) {
            char input1 = getch();
            switch (input1) {
                case ('a'):
                    if (R1.nextXR1 > 3)
                        R1.nextXR1 -= 2;
                    else
                        R1.nextXR1 += 0;
                    break;
                case ('d'):
                    if (R1.nextXR1 < width - 3)
                        R1.nextXR1 += 2;
                    else
                        R1.nextXR1 -= 0;
                    break;
                case ('j'):
                    if (R2.nextXR2 > 3)
                        R2.nextXR2 -= 2;
                    else
                        R2.nextXR2 += 0;
                    break;
                case ('l'):
                    if (R2.nextXR2 < width - 3)
                        R2.nextXR2 += 2;
                    else
                        R2.nextXR2 -= 0;
                    break;
            }
        }
        return 0;
    }

    int logic(Rocket &R1, Rocket &R2, Ball &ball) {
        if (R1.nextYR1 == ball.nextY && R1.nextXR1 == ball.nextX) {
            ball.nextY += 1;
            ball.nextX -= 1;
            ball.speedY *= -1;
            if (ball.nextX == 0) {
                ball.nextX += 1;
            }
        }
        if (R2.nextYR2 == ball.nextY && R2.nextXR2 == ball.nextX) {
            ball.nextY -= 1;
            ball.nextX += 1;
            ball.speedY *= -1;
            if (ball.nextX == 0) {
                ball.nextX -= 1;
            }
        }
        return 0;
    }

    void score(Ball &ball) {
        if (ball.nextY == 1) {
            score2 += 1;
        } else if (ball.nextY == height - 2) {
            score1 += 1;
        } else if (score1 == 11) {
            game_over = true;
            std::cout << "First player wins\n";
        } else if (score2 == 11) {
            game_over = true;
            std::cout << "Second player wins\n";
        }
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
    //R1
    R1.startXR1 = game.width / 2;
    R1.startYR1 = 1;
    R1.nextXR1 = R1.startXR1;
    R1.nextYR1 = R1.startYR1;
    //R2
    R2.startXR2 = game.width / 2;
    R2.startYR2 = game.height - 2;
    R2.nextXR2 = R2.startXR2;
    R2.nextYR2 = R2.startYR2;
    while (!game.game_over) {
        game.printField(ball, R1, R2);
        game.stepGame(ball);
        game.gameplay(R1, R2);
        game.logic(R1, R2, ball);
        game.score(ball);
    }
    return 0;
}
