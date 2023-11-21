#include <iostream>

class Rocket {
    int startX;
    int startY;
};

class Ball {
public:
    int startX;
    int startY;
    int speedX;
    int speedY;
};

class Game {
public:
    bool game_over;
    int height;
    int width;
    int score1;
    int score2;
    Ball ball;
    Rocket R1;
    Rocket R2;

public:
    Game(int height, int width) : height(height), width(width) {};

    Game() : height(0), width(0) {};

    void printField() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == ball.startY && j == ball.startX)
                    std::cout << "*";
                else if (i == 0 || i == height - 1)
                    std::cout << "#";
                else if (j == 0 || j == width)
                    std::cout << "#";
                else std::cout << " ";
            }
            std::cout << "#\n";
        }
    }

    void stepGame(){

    }
};

int main() {
    Ball ball;
    Game game(11, 31);
    ball.startX = game.width / 2;
    ball.startY = game.height / 2;
    game.ball = ball;
    game.printField();
    return 0;
}