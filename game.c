#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

int main() {
    system("color 4F");
    srand(time(0));

    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);

    int x = 1;                  
    int step = 0;               
    int obstaclePos = rand() % 3;
    int score = 0;
    int chances = 3;
    int speed = 140;
    int levelTimer = 0;       

    while (1) {

        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)
                x--;

            if (ch == 77 && x < 2)
                x++;
        }

        clear_screen_fast();

        printf(" SCORE: %d   |   CHANCES LEFT: %d\n", score, chances);
        printf(" ---------------------------\n");

        for (int i = 0; i < 15; i++) {
            if (i == step) {

                if (obstaclePos == 0)
                    printf("|  @              |\n");
                else if (obstaclePos == 1)
                    printf("|        @        |\n");
                else
                    printf("|              @  |\n");

            } else {
                printf("|                 |\n");
            }
        }

        if (x == 0)
            printf("|  ^              |\n");
        else if (x == 1)
            printf("|        ^        |\n");
        else
            printf("|              ^  |\n");

        printf(" ---------------------------\n");

        if (step == 15 && x == obstaclePos) {
            chances--;
            PlaySound(NULL, NULL, 0);
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC);

            if (chances == 0) {
                printf("\n GAME OVER!\n FINAL SCORE: %d\n", score);
                break;
            }

            printf("\n HIT! %d CHANCES LEFT\n", chances);
            Sleep(1200);
        }

        Sleep(speed);

        step++;
        levelTimer++;

        if (levelTimer >= 20 && speed > 40) {
            speed -= 10;
            levelTimer = 0;
        }

        if (step > 15) {
            step = 0;
            obstaclePos = rand() % 3;
            score++;
        }
    }

    return 0;
}
