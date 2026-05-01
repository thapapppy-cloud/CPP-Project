#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 15;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    srand(time(NULL));
    int playerX = WIDTH / 2;
    int alienX = 5, alienY = 0;
    int bulletX = -1, bulletY = -1;
    int score = 0;
    bool running = true;

    while (running) {
        COORD coord = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == playerX && y == HEIGHT - 1) {
                    setColor(2);
                    cout << "A";
                }
                else if (x == alienX && y == alienY) {
                    setColor(4);
                    cout << "W";
                }
                else if (x == bulletX && y == bulletY) {
                    setColor(6);
                    cout << "|";
                }
                else if (y == HEIGHT - 1) {
                    setColor(7);
                    cout << "-";
                }
                else {
                    setColor(0);
                    cout << " ";
                }
            }
            cout << endl;
        }
        setColor(7);
        cout << "Score: " << score << "  [A/D to Move, Space to Shoot, Q to Quit]" << endl;

        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && playerX > 0) playerX--;
            if (key == 'd' && playerX < WIDTH - 1) playerX++;
            if (key == ' ' && bulletY == -1) {
                bulletX = playerX;
                bulletY = HEIGHT - 2;
            }
            if (key == 'q') running = false;
        }

        if (bulletY != -1) {
            bulletY--;
            if (bulletY < 0) bulletY = -1;
        }

        static int timer = 0;
        if (timer++ % 5 == 0) {
            alienY++;
            if (alienY >= HEIGHT) {
                alienY = 0;
                alienX = rand() % WIDTH;
            }
        }

        if (bulletX == alienX && bulletY == alienY) {
            score += 10;
            bulletY = -1;
            alienY = 0;
            alienX = rand() % WIDTH;
        }

        if (alienX == playerX && alienY == HEIGHT - 1) {
            cout << "\n--- GAME OVER! ---" << endl;
            running = false;
        }

        Sleep(150);
    }

    return 0;
}
