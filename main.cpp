
#include <iostream>
#include <cstdlib>
#include <thread>  
#include <chrono>  
#include "help.h"  
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;


const int MAX_SIZE_mode3 = 1000;
int foodX_mode3 = -1, foodY_mode3 = -1;
vector<pair<int, int>> barriers_mode3;

void myRectspecific(int x1, int y1, int x2, int y2, int R, int G, int B)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);


    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    SelectObject(device_context, pen);
    HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B));
    SelectObject(device_context, brush);

    Rectangle(device_context, x1, y1, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}
void spawnFood_mode3() {
    bool validPosition_mode3 = false;

    while (!validPosition_mode3) {

        foodX_mode3 = 410 + rand() % (750 - 405 - 10);
        foodY_mode3 = 130 + rand() % (360 - 125 - 10);


        bool overlapsBarrier_mode3 = false;
        for (size_t i = 0; i < barriers_mode3.size(); i += 2) {
            int bx1_mode3 = barriers_mode3[i].first;
            int by1_mode3 = barriers_mode3[i].second;
            int bx2_mode3 = barriers_mode3[i + 1].first;
            int by2_mode3 = barriers_mode3[i + 1].second;

            double dx_mode3 = bx2_mode3 - bx1_mode3;
            double dy_mode3 = by2_mode3 - by1_mode3;


            if (dx_mode3 == 0 && dy_mode3 == 0) {
                if (abs(foodX_mode3 - bx1_mode3) <= 10 && abs(foodY_mode3 - by1_mode3) <= 10) {
                    overlapsBarrier_mode3 = true;
                    break;
                }
                continue;
            }


            double t_mode3 = ((foodX_mode3 - bx1_mode3) * dx_mode3 + (foodY_mode3 - by1_mode3) * dy_mode3) / (dx_mode3 * dx_mode3 + dy_mode3 * dy_mode3);
            t_mode3 = max(0.0, min(1.0, t_mode3));


            double closestX_mode3 = bx1_mode3 + t_mode3 * dx_mode3;
            double closestY_mode3 = by1_mode3 + t_mode3 * dy_mode3;


            double distance_mode3 = sqrt(pow(foodX_mode3 - closestX_mode3, 2) + pow(foodY_mode3 - closestY_mode3, 2));

            if (distance_mode3 <= 10) {
                overlapsBarrier_mode3 = true;
                break;
            }
        }


        if (!overlapsBarrier_mode3) {
            validPosition_mode3 = true;
        }
    }
}

bool checkWallCollision_mode3(int x_mode3, int y_mode3) {
    int rectLeft_mode3 = 400, rectTop_mode3 = 120, rectRight_mode3 = 750, rectBottom_mode3 = 360;
    return (x_mode3 < rectLeft_mode3 + 2 || x_mode3 > rectRight_mode3 - 2 || y_mode3 < rectTop_mode3 + 2 || y_mode3 > rectBottom_mode3 - 11);
}

bool checkFoodCollision_mode3(int x_mode3, int y_mode3) {
    return (x_mode3 >= foodX_mode3 && x_mode3 <= foodX_mode3 + 17 && y_mode3 >= foodY_mode3 && y_mode3 <= foodY_mode3 + 17);
}

const int MAX_SNAKE_SIZE_mode3 = 1000;
int snakeBody_mode3[MAX_SNAKE_SIZE_mode3][2] = { 0 };
int snakeLength_mode3 = 1;

void updateSnake_mode3(int& x_mode3, int& y_mode3, int W_mode3) {
    for (int i = snakeLength_mode3 - 1; i > 0; --i) {
        snakeBody_mode3[i][0] = snakeBody_mode3[i - 1][0];
        snakeBody_mode3[i][1] = snakeBody_mode3[i - 1][1];
    }


    if (W_mode3 == 1)
        snakeBody_mode3[0][0] -= 5;
    else if (W_mode3 == 2)
        snakeBody_mode3[0][0] += 5;
    else if (W_mode3 == 3)
        snakeBody_mode3[0][1] -= 5;
    else if (W_mode3 == 4)
        snakeBody_mode3[0][1] += 5;

    x_mode3 = snakeBody_mode3[0][0];
    y_mode3 = snakeBody_mode3[0][1];
}

void renderSnake_mode3(int R, int G, int B) {
    for (int i = 0; i < snakeLength_mode3; ++i) {
        myRect(snakeBody_mode3[i][0], snakeBody_mode3[i][1], snakeBody_mode3[i][0] + 7, snakeBody_mode3[i][1] + 7, R, G, B);
    }
}

bool checkSelfCollision_mode3() {
    for (int i = 1; i < snakeLength_mode3; ++i) {
        if (snakeBody_mode3[0][0] == snakeBody_mode3[i][0] && snakeBody_mode3[0][1] == snakeBody_mode3[i][1]) {
            return true;
        }
    }
    return false;
}

void customSpawnBarrier_mode3() {
    int x1_mode3, y1_mode3, x2_mode3, y2_mode3;
    int rectLeft_mode3 = 400, rectTop_mode3 = 120, rectRight_mode3 = 750, rectBottom_mode3 = 360;
    int barrierCount_mode3;

    cout << "Enter the number of barriers to create: ";
    cin >> barrierCount_mode3;

    for (int i = 0; i < barrierCount_mode3; ++i) {
        bool validPosition_mode3 = false;

        while (!validPosition_mode3) {
            cout << "Enter barrier " << i + 1 << " start x1 (400 to 750): ";
            cin >> x1_mode3;
            cout << "Enter barrier " << i + 1 << " start y1 (120 to 360): ";
            cin >> y1_mode3;
            cout << "Enter barrier " << i + 1 << " end x2 (400 to 750): ";
            cin >> x2_mode3;
            cout << "Enter barrier " << i + 1 << " end y2 (120 to 360): ";
            cin >> y2_mode3;


            if (x1_mode3 >= rectLeft_mode3 && x1_mode3 <= rectRight_mode3 && y1_mode3 >= rectTop_mode3 && y1_mode3 <= rectBottom_mode3 &&
                x2_mode3 >= rectLeft_mode3 && x2_mode3 <= rectRight_mode3 && y2_mode3 >= rectTop_mode3 && y2_mode3 <= rectBottom_mode3) {
                barriers_mode3.push_back({ x1_mode3, y1_mode3 });
                barriers_mode3.push_back({ x2_mode3, y2_mode3 });
                validPosition_mode3 = true;
            }
            else {
                cout << "Barrier must be inside the rectangle (400, 120) to (750, 360). Please try again." << endl;
            }
        }
    }
}

void renderBarriers_mode3() {
    for (size_t i = 0; i < barriers_mode3.size(); i += 2) {
        int x1_mode3 = barriers_mode3[i].first;
        int y1_mode3 = barriers_mode3[i].second;
        int x2_mode3 = barriers_mode3[i + 1].first;
        int y2_mode3 = barriers_mode3[i + 1].second;

        myLine3(x1_mode3, y1_mode3, x2_mode3, y2_mode3, 0, 0, 0);
    }
}

bool checkBarrierCollision_mode3(int x_mode3, int y_mode3) {
    for (size_t i = 0; i < barriers_mode3.size(); i += 2) {
        int x1_mode3 = barriers_mode3[i].first;
        int y1_mode3 = barriers_mode3[i].second;
        int x2_mode3 = barriers_mode3[i + 1].first;
        int y2_mode3 = barriers_mode3[i + 1].second;


        double dx_mode3 = x2_mode3 - x1_mode3;
        double dy_mode3 = y2_mode3 - y1_mode3;


        if (dx_mode3 == 0 && dy_mode3 == 0) {
            if (abs(x_mode3 - x1_mode3) <= 5 && abs(y_mode3 - y1_mode3) <= 5) {
                return true;
            }
            continue;
        }


        double t_mode3 = ((x_mode3 - x1_mode3) * dx_mode3 + (y_mode3 - y1_mode3) * dy_mode3) / (dx_mode3 * dx_mode3 + dy_mode3 * dy_mode3);
        t_mode3 = max(0.0, min(1.0, t_mode3));


        double closestX_mode3 = x1_mode3 + t_mode3 * dx_mode3;
        double closestY_mode3 = y1_mode3 + t_mode3 * dy_mode3;


        double distance_mode3 = sqrt(pow(x_mode3 - closestX_mode3, 2) + pow(y_mode3 - closestY_mode3, 2));


        if (distance_mode3 <= 5) {
            return true;
        }
    }
    return false;
}








const int MAX_SIZE_mode2levelInfinite = 1000;
const int GRID_SIZE_mode2levelInfinite = 10;
int highScore_mode2levelInfinite = 0;
int foodX_mode2levelInfinite = -1, foodY_mode2levelInfinite = -1;
vector<pair<int, int>> barriers_mode2levelInfinite;

int level_mode2levelInfinite = 1;
int score_mode2levelInfinite = 0;
bool gamePaused_mode2levelInfinite = true;
bool gameOver_mode2levelInfinite = false;

void spawnFood_mode2levelInfinite() {
    bool validPosition_mode2levelInfinite = false;
    int bufferzone_mode2levelInfinite = 50;
    int barrierThickness_mode2levelInfinite = 30;
    int playingAreaLeft = 400;
    int playingAreaTop = 120;
    int playingAreaRight = 1290;
    int playingAreaBottom = 735;

    while (!validPosition_mode2levelInfinite) {

        foodX_mode2levelInfinite = playingAreaLeft + (rand() % ((playingAreaRight - playingAreaLeft) / GRID_SIZE_mode2levelInfinite)) * GRID_SIZE_mode2levelInfinite;
        foodY_mode2levelInfinite = playingAreaTop + (rand() % ((playingAreaBottom - playingAreaTop) / GRID_SIZE_mode2levelInfinite)) * GRID_SIZE_mode2levelInfinite;


        bool overlapsBarrier_mode2levelInfinite = false;
        for (const auto& barrier_mode2levelInfinite : barriers_mode2levelInfinite) {
            int bx_mode2levelInfinite = barrier_mode2levelInfinite.first;
            int by_mode2levelInfinite = barrier_mode2levelInfinite.second;

            bool withinXBounds_mode2levelInfinite = (foodX_mode2levelInfinite + 10 >= bx_mode2levelInfinite - bufferzone_mode2levelInfinite &&
                foodX_mode2levelInfinite <= bx_mode2levelInfinite + barrierThickness_mode2levelInfinite + bufferzone_mode2levelInfinite);
            bool withinYBounds_mode2levelInfinite = (foodY_mode2levelInfinite + 10 >= by_mode2levelInfinite - bufferzone_mode2levelInfinite &&
                foodY_mode2levelInfinite <= by_mode2levelInfinite + barrierThickness_mode2levelInfinite + bufferzone_mode2levelInfinite);

            if (withinXBounds_mode2levelInfinite && withinYBounds_mode2levelInfinite) {
                overlapsBarrier_mode2levelInfinite = true;
                break;
            }
        }


        if (!overlapsBarrier_mode2levelInfinite) {
            validPosition_mode2levelInfinite = true;
        }
    }
}
bool checkWallCollision_mode2levelInfinite(int x_mode2levelInfinite, int y_mode2levelInfinite) {

    int rect1_left_mode2levelInfinite = 400;
    int rect1_top_mode2levelInfinite = 120;
    int rect1_right_mode2levelInfinite = 1290;
    int rect1_bottom_mode2levelInfinite = 735;
    int snakeThickness_mode2levelInfinite = 7;


    if (x_mode2levelInfinite < rect1_left_mode2levelInfinite ||
        x_mode2levelInfinite + snakeThickness_mode2levelInfinite > rect1_right_mode2levelInfinite ||
        y_mode2levelInfinite < rect1_top_mode2levelInfinite ||
        y_mode2levelInfinite + snakeThickness_mode2levelInfinite > rect1_bottom_mode2levelInfinite) {
        return true;
    }
    return false;
}

bool checkFoodCollision_mode2levelInfinite(int x_mode2levelInfinite, int y_mode2levelInfinite) {
    return (x_mode2levelInfinite >= foodX_mode2levelInfinite && x_mode2levelInfinite <= foodX_mode2levelInfinite + 10 && y_mode2levelInfinite >= foodY_mode2levelInfinite && y_mode2levelInfinite <= foodY_mode2levelInfinite + 10);
}

const int MAX_SNAKE_SIZE_mode2levelInfinite = 1000;
int snakeBody_mode2levelInfinite[MAX_SNAKE_SIZE_mode2levelInfinite][2] = { 0 };
int snakeLength_mode2levelInfinite = 1;

void updateSnake_mode2levelInfinite(int& x_mode2levelInfinite, int& y_mode2levelInfinite, int W_mode2levelInfinite) {
    for (int i = snakeLength_mode2levelInfinite - 1; i > 0; --i) {
        snakeBody_mode2levelInfinite[i][0] = snakeBody_mode2levelInfinite[i - 1][0];
        snakeBody_mode2levelInfinite[i][1] = snakeBody_mode2levelInfinite[i - 1][1];
    }


    if (W_mode2levelInfinite == 1)
        snakeBody_mode2levelInfinite[0][0] -= 5;
    else if (W_mode2levelInfinite == 2)
        snakeBody_mode2levelInfinite[0][0] += 5;
    else if (W_mode2levelInfinite == 3)
        snakeBody_mode2levelInfinite[0][1] -= 5;
    else if (W_mode2levelInfinite == 4)
        snakeBody_mode2levelInfinite[0][1] += 5;

    x_mode2levelInfinite = snakeBody_mode2levelInfinite[0][0];
    y_mode2levelInfinite = snakeBody_mode2levelInfinite[0][1];
}

void renderSnake_mode2levelInfinite(int R, int G, int B) {
    for (int i = 0; i < snakeLength_mode2levelInfinite; ++i) {
        myRect(snakeBody_mode2levelInfinite[i][0], snakeBody_mode2levelInfinite[i][1], snakeBody_mode2levelInfinite[i][0] + 7, snakeBody_mode2levelInfinite[i][1] + 7, R, G, B);
    }
}

bool checkSelfCollision_mode2levelInfinite() {
    for (int i = 1; i < snakeLength_mode2levelInfinite; ++i) {
        if (snakeBody_mode2levelInfinite[0][0] == snakeBody_mode2levelInfinite[i][0] && snakeBody_mode2levelInfinite[0][1] == snakeBody_mode2levelInfinite[i][1]) {
            return true;
        }
    }
    return false;
}

void spawnBarrier_mode2levelInfinite() {
    bool validPosition_mode2levelInfinite = false;
    int x1_mode2levelInfinite, y1_mode2levelInfinite, x2_mode2levelInfinite, y2_mode2levelInfinite;
    int gapSize_mode2levelInfinite = 150 * 1.25;
    int barrierMinDistance_mode2levelInfinite = 10;
    int maxAttempts_mode2levelInfinite = 100;

    int attempts_mode2levelInfinite = 0;


    int playingAreaLeft = 400;
    int playingAreaTop = 120;
    int playingAreaRight = 1290;
    int playingAreaBottom = 735;

    while (!validPosition_mode2levelInfinite && attempts_mode2levelInfinite < maxAttempts_mode2levelInfinite) {
        attempts_mode2levelInfinite++;

        if (rand() % 2 == 0) {

            x1_mode2levelInfinite = playingAreaLeft + rand() % (playingAreaRight - playingAreaLeft - 20);
            y1_mode2levelInfinite = playingAreaTop + gapSize_mode2levelInfinite;
            x2_mode2levelInfinite = x1_mode2levelInfinite;
            y2_mode2levelInfinite = playingAreaBottom - gapSize_mode2levelInfinite;
        }
        else {

            x1_mode2levelInfinite = playingAreaLeft + gapSize_mode2levelInfinite;
            y1_mode2levelInfinite = playingAreaTop + rand() % (playingAreaBottom - playingAreaTop - 20);
            x2_mode2levelInfinite = playingAreaRight - gapSize_mode2levelInfinite;
            y2_mode2levelInfinite = y1_mode2levelInfinite;
        }


        validPosition_mode2levelInfinite = true;
        for (int i = 0; i < snakeLength_mode2levelInfinite; i++) {
            if ((snakeBody_mode2levelInfinite[i][0] >= x1_mode2levelInfinite && snakeBody_mode2levelInfinite[i][0] <= x2_mode2levelInfinite) &&
                (snakeBody_mode2levelInfinite[i][1] >= y1_mode2levelInfinite && snakeBody_mode2levelInfinite[i][1] <= y2_mode2levelInfinite)) {
                validPosition_mode2levelInfinite = false;
                break;
            }
        }


        for (const auto& barrier_mode2levelInfinite : barriers_mode2levelInfinite) {
            if (abs(barrier_mode2levelInfinite.first - x1_mode2levelInfinite) < 30 && abs(barrier_mode2levelInfinite.second - y1_mode2levelInfinite) < 30) {
                validPosition_mode2levelInfinite = false;
                break;
            }
        }


        bool sufficientDistance_mode2levelInfinite = true;
        for (size_t i = 0; i < barriers_mode2levelInfinite.size(); i += 2) {
            int prevX1_mode2levelInfinite = barriers_mode2levelInfinite[i].first;
            int prevY1_mode2levelInfinite = barriers_mode2levelInfinite[i].second;
            int prevX2_mode2levelInfinite = barriers_mode2levelInfinite[i + 1].first;
            int prevY2_mode2levelInfinite = barriers_mode2levelInfinite[i + 1].second;

            double dist1_mode2levelInfinite = sqrt(pow(x1_mode2levelInfinite - prevX1_mode2levelInfinite, 2) +
                pow(y1_mode2levelInfinite - prevY1_mode2levelInfinite, 2));
            double dist2_mode2levelInfinite = sqrt(pow(x2_mode2levelInfinite - prevX2_mode2levelInfinite, 2) +
                pow(y2_mode2levelInfinite - prevY2_mode2levelInfinite, 2));

            if (dist1_mode2levelInfinite < barrierMinDistance_mode2levelInfinite ||
                dist2_mode2levelInfinite < barrierMinDistance_mode2levelInfinite) {
                sufficientDistance_mode2levelInfinite = false;
                break;
            }
        }

        if (validPosition_mode2levelInfinite && sufficientDistance_mode2levelInfinite) {

            barriers_mode2levelInfinite.push_back({ x1_mode2levelInfinite, y1_mode2levelInfinite });
            barriers_mode2levelInfinite.push_back({ x2_mode2levelInfinite, y2_mode2levelInfinite });
        }
    }

    if (attempts_mode2levelInfinite >= maxAttempts_mode2levelInfinite) {
        cout << "Couldn't spawn more barriers. Max attempts reached!" << endl;
    }
}

void renderBarriers_mode2levelInfinite() {
    for (size_t i = 0; i < barriers_mode2levelInfinite.size(); i += 2) {
        int x1_mode2levelInfinite = barriers_mode2levelInfinite[i].first;
        int y1_mode2levelInfinite = barriers_mode2levelInfinite[i].second;
        int x2_mode2levelInfinite = barriers_mode2levelInfinite[i + 1].first;
        int y2_mode2levelInfinite = barriers_mode2levelInfinite[i + 1].second;

        myLine3(x1_mode2levelInfinite, y1_mode2levelInfinite, x2_mode2levelInfinite, y2_mode2levelInfinite, 0, 0, 0);
    }
}

bool checkBarrierCollision_mode2levelInfinite(int x_mode2levelInfinite, int y_mode2levelInfinite) {
    for (size_t i = 0; i < barriers_mode2levelInfinite.size(); i += 2) {
        int x1_mode2levelInfinite = barriers_mode2levelInfinite[i].first;
        int y1_mode2levelInfinite = barriers_mode2levelInfinite[i].second;
        int x2_mode2levelInfinite = barriers_mode2levelInfinite[i + 1].first;
        int y2_mode2levelInfinite = barriers_mode2levelInfinite[i + 1].second;


        if (x1_mode2levelInfinite == x2_mode2levelInfinite) {
            if (x_mode2levelInfinite >= x1_mode2levelInfinite - 3 && x_mode2levelInfinite <= x1_mode2levelInfinite + 3 && y_mode2levelInfinite >= y1_mode2levelInfinite && y_mode2levelInfinite <= y2_mode2levelInfinite) {
                return true;
            }
        }

        else if (y1_mode2levelInfinite == y2_mode2levelInfinite) {
            if (y_mode2levelInfinite >= y1_mode2levelInfinite - 3 && y_mode2levelInfinite <= y1_mode2levelInfinite + 3 && x_mode2levelInfinite >= x1_mode2levelInfinite && x_mode2levelInfinite <= x2_mode2levelInfinite) {
                return true;
            }
        }
    }
    return false;
}
void levelUp_mode2levelInfinite() {
    level_mode2levelInfinite++;

    spawnBarrier_mode2levelInfinite();

    cout << "\nLevel " << level_mode2levelInfinite << "!" << endl;

    gamePaused_mode2levelInfinite = true;

    Sleep(500);
}















const int GRID_SIZE_mode2level3 = 10;
int foodX_mode2level3 = -1, foodY_mode2level3 = -1;
vector<pair<int, int>> barriers_mode2level3;

int level_mode2level3 = 3;
int score_mode2level3 = 0;
bool gamePaused_mode2level3 = true;
bool gameOver_mode2level3 = false;

void spawnFood_mode2level3() {
    bool validPosition_mode2level3 = false;
    int bufferzone_mode2level3 = 70;

    while (!validPosition_mode2level3) {

        foodX_mode2level3 = 410 + (rand() % ((750 - 410 - 10) / GRID_SIZE_mode2level3)) * GRID_SIZE_mode2level3;
        foodY_mode2level3 = 125 + (rand() % ((360 - 125 - 10) / GRID_SIZE_mode2level3)) * GRID_SIZE_mode2level3;


        bool overlapsBarrier_mode2level3 = false;
        for (const auto& barrier_mode2level3 : barriers_mode2level3) {
            int bx_mode2level3 = barrier_mode2level3.first;
            int by_mode2level3 = barrier_mode2level3.second;
            int barrierThickness_mode2level3 = 30;


            if (foodX_mode2level3 >= bx_mode2level3 - bufferzone_mode2level3 && foodX_mode2level3 <= bx_mode2level3 + barrierThickness_mode2level3 + bufferzone_mode2level3 &&
                foodY_mode2level3 >= by_mode2level3 && foodY_mode2level3 <= by_mode2level3 + barrierThickness_mode2level3) {
                overlapsBarrier_mode2level3 = true;
                break;
            }
        }


        if (!overlapsBarrier_mode2level3) {
            validPosition_mode2level3 = true;
        }
    }
}

bool checkWallCollision_mode2level3(int x_mode2level3, int y_mode2level3) {
    int rect1_left_mode2level3 = 400, rect1_top_mode2level3 = 120, rect1_right_mode2level3 = 750, rect1_bottom_mode2level3 = 360;
    return (x_mode2level3 < rect1_left_mode2level3 + 2 || x_mode2level3 > rect1_right_mode2level3 - 2 || y_mode2level3 < rect1_top_mode2level3 + 2 || y_mode2level3 > rect1_bottom_mode2level3 - 2);
}

bool checkFoodCollision_mode2level3(int x_mode2level3, int y_mode2level3) {
    return (x_mode2level3 >= foodX_mode2level3 && x_mode2level3 <= foodX_mode2level3 + 10 && y_mode2level3 >= foodY_mode2level3 && y_mode2level3 <= foodY_mode2level3 + 10);
}

const int MAX_SNAKE_SIZE_mode2level3 = 1000;
int snakeBody_mode2level3[MAX_SNAKE_SIZE_mode2level3][2] = { {475, 240} };
int snakeLength_mode2level3 = 1;

void updateSnake_mode2level3(int& x_mode2level3, int& y_mode2level3, int W_mode2level3) {
    for (int i = snakeLength_mode2level3 - 1; i > 0; --i) {
        snakeBody_mode2level3[i][0] = snakeBody_mode2level3[i - 1][0];
        snakeBody_mode2level3[i][1] = snakeBody_mode2level3[i - 1][1];
    }


    if (W_mode2level3 == 1)
        snakeBody_mode2level3[0][0] -= 5;
    else if (W_mode2level3 == 2)
        snakeBody_mode2level3[0][0] += 5;
    else if (W_mode2level3 == 3)
        snakeBody_mode2level3[0][1] -= 5;
    else if (W_mode2level3 == 4)
        snakeBody_mode2level3[0][1] += 5;

    x_mode2level3 = snakeBody_mode2level3[0][0];
    y_mode2level3 = snakeBody_mode2level3[0][1];
}

void renderSnake_mode2level3(int R, int G, int B) {
    for (int i = 0; i < snakeLength_mode2level3; ++i) {
        myRect(snakeBody_mode2level3[i][0], snakeBody_mode2level3[i][1], snakeBody_mode2level3[i][0] + 7, snakeBody_mode2level3[i][1] + 7, R, G, B);
    }
}

bool checkSelfCollision_mode2level3() {
    for (int i = 1; i < snakeLength_mode2level3; ++i) {
        if (snakeBody_mode2level3[0][0] == snakeBody_mode2level3[i][0] && snakeBody_mode2level3[0][1] == snakeBody_mode2level3[i][1]) {
            return true;
        }
    }
    return false;
}

void spawnFixedBarriers_mode2level3() {

    int barrierHeight_mode2level3 = 170;
    int leftMargin_mode2level3 = 470;
    int spacing_mode2level3 = 40;


    barriers_mode2level3.push_back({ leftMargin_mode2level3, 160 });
    barriers_mode2level3.push_back({ leftMargin_mode2level3, 160 + barrierHeight_mode2level3 });

    barriers_mode2level3.push_back({ leftMargin_mode2level3 + spacing_mode2level3 + 30, 160 });
    barriers_mode2level3.push_back({ leftMargin_mode2level3 + spacing_mode2level3 + 30, 160 + barrierHeight_mode2level3 });

    barriers_mode2level3.push_back({ leftMargin_mode2level3 + 2 * (spacing_mode2level3 + 30), 160 });
    barriers_mode2level3.push_back({ leftMargin_mode2level3 + 2 * (spacing_mode2level3 + 30), 160 + barrierHeight_mode2level3 });

    barriers_mode2level3.push_back({ leftMargin_mode2level3 + 3 * (spacing_mode2level3 + 30), 160 });
    barriers_mode2level3.push_back({ leftMargin_mode2level3 + 3 * (spacing_mode2level3 + 30), 160 + barrierHeight_mode2level3 });


    barriers_mode2level3.push_back({ 470, 240 });
    barriers_mode2level3.push_back({ 680, 240 });

}

void renderBarriers_mode2level3() {
    for (size_t i = 0; i < barriers_mode2level3.size(); i += 2) {
        int x1_mode2level3 = barriers_mode2level3[i].first;
        int y1_mode2level3 = barriers_mode2level3[i].second;
        int x2_mode2level3 = barriers_mode2level3[i + 1].first;
        int y2_mode2level3 = barriers_mode2level3[i + 1].second;

        myLine3(x1_mode2level3, y1_mode2level3, x2_mode2level3, y2_mode2level3, 0, 0, 0);
    }
}




bool checkBarrierCollision_mode2level3(int x_mode2level3, int y_mode2level3) {
    for (size_t i = 0; i < barriers_mode2level3.size(); i += 2) {
        int x1_mode2level3 = barriers_mode2level3[i].first;
        int y1_mode2level3 = barriers_mode2level3[i].second;
        int x2_mode2level3 = barriers_mode2level3[i + 1].first;
        int y2_mode2level3 = barriers_mode2level3[i + 1].second;


        if (x1_mode2level3 == x2_mode2level3) {
            if (x_mode2level3 == x1_mode2level3 && y_mode2level3 >= min(y1_mode2level3, y2_mode2level3) && y_mode2level3 <= max(y1_mode2level3, y2_mode2level3)) {
                return true;
            }
        }

        else if (y1_mode2level3 == y2_mode2level3) {
            if (abs(y_mode2level3 - y1_mode2level3) <= 3 &&
                x_mode2level3 >= min(x1_mode2level3, x2_mode2level3) &&
                x_mode2level3 <= max(x1_mode2level3, x2_mode2level3)) {
                return true;
            }
        }
    }
    return false;
}















const int MAX_SIZE_mode1 = 1000;
int foodX_mode1 = -1, foodY_mode1 = -1;
const int LEFT_BOUND_mode1 = 395;
const int RIGHT_BOUND_mode1 = 755;
const int TOP_BOUND_mode1 = 115;
const int BOTTOM_BOUND_mode1 = 365;

void spawnFoodmode1() {
    bool validPosition_mode1 = false;

    while (!validPosition_mode1) {
        foodX_mode1 = LEFT_BOUND_mode1 + rand() % (RIGHT_BOUND_mode1 - LEFT_BOUND_mode1 - 10);
        foodY_mode1 = TOP_BOUND_mode1 + rand() % (BOTTOM_BOUND_mode1 - TOP_BOUND_mode1 - 10);
        validPosition_mode1 = (foodX_mode1 >= LEFT_BOUND_mode1 && foodX_mode1 <= RIGHT_BOUND_mode1) &&
            (foodY_mode1 >= TOP_BOUND_mode1 && foodY_mode1 <= BOTTOM_BOUND_mode1);
    }
}

bool checkFoodCollisionmode1(int x_mode1, int y_mode1) {
    return (x_mode1 >= foodX_mode1 && x_mode1 <= foodX_mode1 + 14 && y_mode1 >= foodY_mode1 && y_mode1 <= foodY_mode1 + 14);
}

const int MAX_SNAKE_SIZE_mode1 = 1000;
int snakeBody_mode1[MAX_SNAKE_SIZE_mode1][2] = { 0 };
int snakeLength_mode1 = 1;

void updateSnakemode1(int& x_mode1, int& y_mode1, int W_mode1) {

    int prevX_mode1 = snakeBody_mode1[0][0];
    int prevY_mode1 = snakeBody_mode1[0][1];


    for (int i = snakeLength_mode1 - 1; i > 0; --i) {
        snakeBody_mode1[i][0] = snakeBody_mode1[i - 1][0];
        snakeBody_mode1[i][1] = snakeBody_mode1[i - 1][1];
    }


    if (W_mode1 == 1)
        snakeBody_mode1[0][0] -= 5;
    else if (W_mode1 == 2)
        snakeBody_mode1[0][0] += 5;
    else if (W_mode1 == 3)
        snakeBody_mode1[0][1] -= 5;
    else if (W_mode1 == 4)
        snakeBody_mode1[0][1] += 5;


    int newX_mode1 = snakeBody_mode1[0][0];
    int newY_mode1 = snakeBody_mode1[0][1];


    if (newX_mode1 < LEFT_BOUND_mode1) {
        myRect(RIGHT_BOUND_mode1 - 7, prevY_mode1, RIGHT_BOUND_mode1, prevY_mode1 + 7, 0, 0, 0);
        newX_mode1 = RIGHT_BOUND_mode1 - 7;
    }
    else if (newX_mode1 > RIGHT_BOUND_mode1 - 7) {
        myRect(LEFT_BOUND_mode1, prevY_mode1, LEFT_BOUND_mode1 + 7, prevY_mode1 + 7, 0, 0, 0);
        newX_mode1 = LEFT_BOUND_mode1;
    }

    if (newY_mode1 < TOP_BOUND_mode1) {
        myRect(prevX_mode1, BOTTOM_BOUND_mode1 - 7, prevX_mode1 + 7, BOTTOM_BOUND_mode1, 0, 0, 0);
        newY_mode1 = BOTTOM_BOUND_mode1 - 7;
    }
    else if (newY_mode1 > BOTTOM_BOUND_mode1 - 7) {
        myRect(prevX_mode1, TOP_BOUND_mode1, prevX_mode1 + 7, TOP_BOUND_mode1 + 7, 0, 0, 0);
        newY_mode1 = TOP_BOUND_mode1 + 7;
    }


    snakeBody_mode1[0][0] = newX_mode1;
    snakeBody_mode1[0][1] = newY_mode1;


    x_mode1 = snakeBody_mode1[0][0];
    y_mode1 = snakeBody_mode1[0][1];
}

void renderSnakemode1(int R, int G, int B) {
    for (int i = 0; i < snakeLength_mode1; ++i) {
        myRect(snakeBody_mode1[i][0], snakeBody_mode1[i][1], snakeBody_mode1[i][0] + 7, snakeBody_mode1[i][1] + 7, R, G, B);
    }
}

bool checkSelfCollisionmode1() {
    for (int i = 1; i < snakeLength_mode1; ++i) {
        if (snakeBody_mode1[0][0] == snakeBody_mode1[i][0] && snakeBody_mode1[0][1] == snakeBody_mode1[i][1]) {
            return true;
        }
    }
    return false;
}















void clearConsole() {
    system("cls");
}


void drawBackground() {
    int R = 197, G = 154, B = 3;
    myRect(0 + 360, 0 + 80, 320 + 360, 600 + 80, R, G, B);
}

void drawBackground2() {
    int R = 12, G = 12, B = 12;
    myRect(320, 0 + 80, 620, 600 + 80, R, G, B);
}


void drawSnake(int colorIndex, int startX, int startY) {
    const int blockSize = 30;
    const int numberOfBlocks = 5;


    const char* colorNames[] = {
        "Red", "Blue", "Yellow", "Orange", "Purple", "Pink"
    };


    gotoxy(4, 12);
    cout << " ";


    gotoxy(12, 12);
    cout << colorNames[colorIndex];


    int colors[][3] = {
        {255, 0, 0},
        {0, 0, 255},
        {255, 255, 0},
        {255, 165, 0},
        {128, 0, 128},
        {255, 192, 203}
    };


    for (int i = 0; i < numberOfBlocks; i++) {
        int R = colors[colorIndex][0];
        int G = colors[colorIndex][1];
        int B = colors[colorIndex][2];
        myRect(56 + i * blockSize, 300, 56 + i * blockSize + blockSize - 1, 300 + blockSize - 1, R, G, B);
    }
}


void displayMenu() {

    myRectspecific(3, 150, 300, 400, 0, 0, 0);


    gotoxy(5, 11);
    cout << " SNAKE GAME " << endl;
    gotoxy(5, 13);
    cout << " Press Enter " << endl;
}

void displayLevels(int levelIndex) {

    gotoxy(3, 10);
    cout << " LEVEL SELECT: ";


    const char* levels[] = {
        "Level 1", "Level 2", "Level 3", "Infinite"
    };


    for (int i = 0; i < 4; i++) {
        gotoxy(10, 12 + i);
        if (i == levelIndex) {
            cout << "> " << levels[i] << " <";
        }
        else {
            cout << " " << levels[i] << " ";
        }
    }
}


void displayModes(int modeIndex) {

    gotoxy(3, 10);
    cout << " MODE SELECT ";


    const char* modes[] = {
        "Endless Mode", "Levels Mode", "Custom Mode"
    };


    for (int i = 0; i < 3; i++) {
        gotoxy(8, 12 + i);
        if (i == modeIndex) {
            cout << "> " << modes[i] << " <";
        }
        else {
            cout << " " << modes[i] << " ";
        }
    }
}
const int GRID_SIZE_mode2level1 = 10;
int foodX_mode2level1 = -1, foodY_mode2level1 = -1;
vector<pair<int, int>> barriers_mode2level1;

int level_mode2level1 = 1;
int score_mode2level1 = 0;
bool gamePaused_mode2level1 = true;
bool gameOver_mode2level1 = false;

void spawnFood_mode2level1() {
    bool validPosition_mode2level1 = false;
    int bufferzone_mode2level1 = 70;

    while (!validPosition_mode2level1) {

        foodX_mode2level1 = 410 + (rand() % ((750 - 410 - 10) / GRID_SIZE_mode2level1)) * GRID_SIZE_mode2level1;
        foodY_mode2level1 = 125 + (rand() % ((360 - 125 - 10) / GRID_SIZE_mode2level1)) * GRID_SIZE_mode2level1;



        bool overlapsBarrier_mode2level1 = false;
        for (const auto& barrier_mode2level1 : barriers_mode2level1) {
            int bx_mode2level1 = barrier_mode2level1.first;
            int by_mode2level1 = barrier_mode2level1.second;
            int barrierThickness_mode2level1 = 30;



            if (foodX_mode2level1 >= bx_mode2level1 - bufferzone_mode2level1 && foodX_mode2level1 <= bx_mode2level1 + barrierThickness_mode2level1 + bufferzone_mode2level1 &&
                foodY_mode2level1 >= by_mode2level1 && foodY_mode2level1 <= by_mode2level1 + barrierThickness_mode2level1) {
                overlapsBarrier_mode2level1 = true;
                break;
            }
        }


        if (!overlapsBarrier_mode2level1) {
            validPosition_mode2level1 = true;
        }
    }
}

bool checkWallCollision_mode2level1(int x_mode2level1, int y_mode2level1) {
    int rect1_left_mode2level1 = 400, rect1_top_mode2level1 = 120, rect1_right_mode2level1 = 750, rect1_bottom_mode2level1 = 360;
    return (x_mode2level1 < rect1_left_mode2level1 + 2 || x_mode2level1 > rect1_right_mode2level1 - 2 || y_mode2level1 < rect1_top_mode2level1 + 2 || y_mode2level1 > rect1_bottom_mode2level1 - 2);
}

bool checkFoodCollision_mode2level1(int x_mode2level1, int y_mode2level1) {
    return (x_mode2level1 >= foodX_mode2level1 && x_mode2level1 <= foodX_mode2level1 + 10 && y_mode2level1 >= foodY_mode2level1 && y_mode2level1 <= foodY_mode2level1 + 10);
}

const int MAX_SNAKE_SIZE_mode2level1 = 1000;
int snakeBody_mode2level1[MAX_SNAKE_SIZE_mode2level1][2] = { 0 };
int snakeLength_mode2level1 = 1;

void updateSnake_mode2level1(int& x_mode2level1, int& y_mode2level1, int W_mode2level1) {
    for (int i = snakeLength_mode2level1 - 1; i > 0; --i) {
        snakeBody_mode2level1[i][0] = snakeBody_mode2level1[i - 1][0];
        snakeBody_mode2level1[i][1] = snakeBody_mode2level1[i - 1][1];
    }


    if (W_mode2level1 == 1)
        snakeBody_mode2level1[0][0] -= 5;
    else if (W_mode2level1 == 2)
        snakeBody_mode2level1[0][0] += 5;
    else if (W_mode2level1 == 3)
        snakeBody_mode2level1[0][1] -= 5;
    else if (W_mode2level1 == 4)
        snakeBody_mode2level1[0][1] += 5;

    x_mode2level1 = snakeBody_mode2level1[0][0];
    y_mode2level1 = snakeBody_mode2level1[0][1];
}

void renderSnake_mode2level1(int R, int G, int B) {
    for (int i = 0; i < snakeLength_mode2level1; ++i) {
        myRect(snakeBody_mode2level1[i][0], snakeBody_mode2level1[i][1], snakeBody_mode2level1[i][0] + 7, snakeBody_mode2level1[i][1] + 7, R, G, B);
    }
}

bool checkSelfCollision_mode2level1() {
    for (int i = 1; i < snakeLength_mode2level1; ++i) {
        if (snakeBody_mode2level1[0][0] == snakeBody_mode2level1[i][0] && snakeBody_mode2level1[0][1] == snakeBody_mode2level1[i][1]) {
            return true;
        }
    }
    return false;
}

void spawnFixedBarriers_mode2level1() {

    int barrierHeight_mode2level1 = 170;
    int leftMargin_mode2level1 = 490;
    int spacing_mode2level1 = 60;


    barriers_mode2level1.push_back({ leftMargin_mode2level1, 160 });
    barriers_mode2level1.push_back({ leftMargin_mode2level1, 160 + barrierHeight_mode2level1 });

    barriers_mode2level1.push_back({ leftMargin_mode2level1 + spacing_mode2level1 + 30, 160 });
    barriers_mode2level1.push_back({ leftMargin_mode2level1 + spacing_mode2level1 + 30, 160 + barrierHeight_mode2level1 });
}


void renderBarriers_mode2level1() {
    for (size_t i = 0; i < barriers_mode2level1.size(); i += 2) {
        int x1_mode2level1 = barriers_mode2level1[i].first;
        int y1_mode2level1 = barriers_mode2level1[i].second;
        int x2_mode2level1 = barriers_mode2level1[i + 1].first;
        int y2_mode2level1 = barriers_mode2level1[i + 1].second;

        myLine3(x1_mode2level1, y1_mode2level1, x2_mode2level1, y2_mode2level1, 0, 0, 0);
    }
}

bool checkBarrierCollision_mode2level1(int x_mode2level1, int y_mode2level1) {
    for (size_t i = 0; i < barriers_mode2level1.size(); i += 2) {
        int x1_mode2level1 = barriers_mode2level1[i].first;
        int y1_mode2level1 = barriers_mode2level1[i].second;
        int x2_mode2level1 = barriers_mode2level1[i + 1].first;
        int y2_mode2level1 = barriers_mode2level1[i + 1].second;


        if (x1_mode2level1 == x2_mode2level1) {
            if (x_mode2level1 >= x1_mode2level1 - 3 && x_mode2level1 <= x1_mode2level1 + 3 && y_mode2level1 >= y1_mode2level1 && y_mode2level1 <= y2_mode2level1) {
                return true;
            }
        }

        else if (y1_mode2level1 == y2_mode2level1) {
            if (y_mode2level1 >= y1_mode2level1 - 3 && y_mode2level1 <= y1_mode2level1 + 3 && x_mode2level1 >= x1_mode2level1 && x_mode2level1 <= x2_mode2level1) {
                return true;
            }
        }
    }
    return false;
}




const int GRID_SIZE_mode2level2 = 10;
int foodX_mode2level2 = -1, foodY_mode2level2 = -1;
vector<pair<int, int>> barriers_mode2level2;

int level_mode2level2 = 2;
int score_mode2level2 = 0;
bool gamePaused_mode2level2 = true;
bool gameOver_mode2level2 = false;

void spawnFood_mode2level2() {
    bool validPosition_mode2level2 = false;
    int bufferzone_mode2level2 = 70;

    while (!validPosition_mode2level2) {

        foodX_mode2level2 = 410 + (rand() % ((750 - 410 - 10) / GRID_SIZE_mode2level2)) * GRID_SIZE_mode2level2;
        foodY_mode2level2 = 125 + (rand() % ((360 - 125 - 10) / GRID_SIZE_mode2level2)) * GRID_SIZE_mode2level2;


        bool overlapsBarrier_mode2level2 = false;
        for (const auto& barrier_mode2level2 : barriers_mode2level2) {
            int bx_mode2level2 = barrier_mode2level2.first;
            int by_mode2level2 = barrier_mode2level2.second;
            int barrierThickness_mode2level2 = 30;


            if (foodX_mode2level2 >= bx_mode2level2 - bufferzone_mode2level2 && foodX_mode2level2 <= bx_mode2level2 + barrierThickness_mode2level2 + bufferzone_mode2level2 &&
                foodY_mode2level2 >= by_mode2level2 && foodY_mode2level2 <= by_mode2level2 + barrierThickness_mode2level2) {
                overlapsBarrier_mode2level2 = true;
                break;
            }
        }


        if (!overlapsBarrier_mode2level2) {
            validPosition_mode2level2 = true;
        }
    }
}

bool checkWallCollision_mode2level2(int x_mode2level2, int y_mode2level2) {
    int rect1_left_mode2level2 = 400, rect1_top_mode2level2 = 120, rect1_right_mode2level2 = 750, rect1_bottom_mode2level2 = 360;
    return (x_mode2level2 < rect1_left_mode2level2 + 2 || x_mode2level2 > rect1_right_mode2level2 - 2 || y_mode2level2 < rect1_top_mode2level2 + 2 || y_mode2level2 > rect1_bottom_mode2level2 - 2);
}

bool checkFoodCollision_mode2level2(int x_mode2level2, int y_mode2level2) {
    return (x_mode2level2 >= foodX_mode2level2 && x_mode2level2 <= foodX_mode2level2 + 10 && y_mode2level2 >= foodY_mode2level2 && y_mode2level2 <= foodY_mode2level2 + 10);
}

const int MAX_SNAKE_SIZE_mode2level2 = 1000;
int snakeBody_mode2level2[MAX_SNAKE_SIZE_mode2level2][2] = { 0 };
int snakeLength_mode2level2 = 1;

void updateSnake_mode2level2(int& x_mode2level2, int& y_mode2level2, int W_mode2level2) {
    for (int i = snakeLength_mode2level2 - 1; i > 0; --i) {
        snakeBody_mode2level2[i][0] = snakeBody_mode2level2[i - 1][0];
        snakeBody_mode2level2[i][1] = snakeBody_mode2level2[i - 1][1];
    }


    if (W_mode2level2 == 1)
        snakeBody_mode2level2[0][0] -= 5;
    else if (W_mode2level2 == 2)
        snakeBody_mode2level2[0][0] += 5;
    else if (W_mode2level2 == 3)
        snakeBody_mode2level2[0][1] -= 5;
    else if (W_mode2level2 == 4)
        snakeBody_mode2level2[0][1] += 5;

    x_mode2level2 = snakeBody_mode2level2[0][0];
    y_mode2level2 = snakeBody_mode2level2[0][1];
}

void renderSnake_mode2level2(int R, int G, int B) {
    for (int i = 0; i < snakeLength_mode2level2; ++i) {
        myRect(snakeBody_mode2level2[i][0], snakeBody_mode2level2[i][1], snakeBody_mode2level2[i][0] + 7, snakeBody_mode2level2[i][1] + 7, R, G, B);
    }
}

bool checkSelfCollision_mode2level2() {
    for (int i = 1; i < snakeLength_mode2level2; ++i) {
        if (snakeBody_mode2level2[0][0] == snakeBody_mode2level2[i][0] && snakeBody_mode2level2[0][1] == snakeBody_mode2level2[i][1]) {
            return true;
        }
    }
    return false;
}

void spawnFixedBarriers_mode2level2() {

    int barrierHeight_mode2level2 = 170;
    int leftMargin_mode2level2 = 490;
    int spacing_mode2level2 = 60;


    barriers_mode2level2.push_back({ leftMargin_mode2level2, 160 });
    barriers_mode2level2.push_back({ leftMargin_mode2level2, 160 + barrierHeight_mode2level2 });

    barriers_mode2level2.push_back({ leftMargin_mode2level2 + spacing_mode2level2 + 30, 160 });
    barriers_mode2level2.push_back({ leftMargin_mode2level2 + spacing_mode2level2 + 30, 160 + barrierHeight_mode2level2 });

    barriers_mode2level2.push_back({ leftMargin_mode2level2 + 2 * (spacing_mode2level2 + 30), 160 });
    barriers_mode2level2.push_back({ leftMargin_mode2level2 + 2 * (spacing_mode2level2 + 30), 160 + barrierHeight_mode2level2 });
}


void renderBarriers_mode2level2() {
    for (size_t i = 0; i < barriers_mode2level2.size(); i += 2) {
        int x1_mode2level2 = barriers_mode2level2[i].first;
        int y1_mode2level2 = barriers_mode2level2[i].second;
        int x2_mode2level2 = barriers_mode2level2[i + 1].first;
        int y2_mode2level2 = barriers_mode2level2[i + 1].second;

        myLine3(x1_mode2level2, y1_mode2level2, x2_mode2level2, y2_mode2level2, 0, 0, 0);
    }
}

bool checkBarrierCollision_mode2level2(int x_mode2level2, int y_mode2level2) {
    for (size_t i = 0; i < barriers_mode2level2.size(); i += 2) {
        int x1_mode2level2 = barriers_mode2level2[i].first;
        int y1_mode2level2 = barriers_mode2level2[i].second;
        int x2_mode2level2 = barriers_mode2level2[i + 1].first;
        int y2_mode2level2 = barriers_mode2level2[i + 1].second;


        if (x1_mode2level2 == x2_mode2level2) {
            if (x_mode2level2 >= x1_mode2level2 - 3 && x_mode2level2 <= x1_mode2level2 + 3 && y_mode2level2 >= y1_mode2level2 && y_mode2level2 <= y2_mode2level2) {
                return true;
            }
        }

        else if (y1_mode2level2 == y2_mode2level2) {
            if (y_mode2level2 >= y1_mode2level2 - 3 && y_mode2level2 <= y1_mode2level2 + 3 && x_mode2level2 >= x1_mode2level2 && x_mode2level2 <= x2_mode2level2) {
                return true;
            }
        }
    }
    return false;
}
void Restartlevel(int level) {


    if (level == 0) {
        myRect(395, 115, 755, 365, 123, 158, 2);

        int x_mode1 = 475;
        int y_mode1 = 240;
        int w_mode1 = 0;
        int W_mode1 = 0;
        int score_mode1 = 0;
        snakeLength_mode1 = 1;
        foodX_mode1 = -1;
        foodY_mode1 = -1;

        snakeBody_mode1[0][0] = x_mode1;
        snakeBody_mode1[0][1] = y_mode1;
        system("cls");
        cout << "Restarted Infinte Mode ! Good luck!\n";
    }
    else if (level == 1) {
        myRect(395, 115, 755, 365, 123, 158, 2);
        int x_mode2level1 = 475;
        int y_mode2level1 = 240;
        int W_mode2level1 = 0;
        score_mode2level1 = 0;
        snakeLength_mode2level1 = 1;
        foodX_mode2level1 = -1;
        foodY_mode2level1 = -1;
        gamePaused_mode2level1 = true;
        gameOver_mode2level1 = false;

        snakeBody_mode2level1[0][0] = x_mode2level1;
        snakeBody_mode2level1[0][1] = y_mode2level1;

        spawnFixedBarriers_mode2level1();
        system("cls");
        cout << "Restarting Mode 2 Level 1! Good luck!\n";
    }
    else if (level == 2) {
        myRect(395, 115, 755, 365, 123, 158, 2);
        int x_mode2level2 = 475;
        int y_mode2level2 = 240;
        int W_mode2level2 = 0;
        score_mode2level2 = 0;
        snakeLength_mode2level2 = 1;
        foodX_mode2level2 = -1;
        foodY_mode2level2 = -1;
        gamePaused_mode2level2 = true;
        gameOver_mode2level2 = false;

        snakeBody_mode2level2[0][0] = x_mode2level2;
        snakeBody_mode2level2[0][1] = y_mode2level2;

        spawnFixedBarriers_mode2level2();
        system("cls");
        cout << "Restarting Level 2! Good luck!\n";
    }
    else if (level == 3) {
        myRect(395, 115, 755, 365, 123, 158, 2);
        int x_mode2level3 = 475;
        int y_mode2level3 = 260;
        int W_mode2level3 = 0;
        score_mode2level3 = 0;
        snakeLength_mode2level3 = 1;
        foodX_mode2level3 = -1;
        foodY_mode2level3 = -1;
        gamePaused_mode2level3 = true;
        gameOver_mode2level3 = false;

        snakeBody_mode2level3[0][0] = x_mode2level3;
        snakeBody_mode2level3[0][1] = y_mode2level3;

        spawnFixedBarriers_mode2level3();

        renderBarriers_mode2level3();
        system("cls");
        cout << "Restarting Level 3! Good luck!\n";
    }
    else if (level == 4) {
        myRect(395, 115, 755, 365, 123, 158, 2);
        int x_mode2levelInfinite = 475;
        int y_mode2levelInfinite = 240;
        int W_mode2levelInfinite = 0;
        score_mode2levelInfinite = 0;
        snakeLength_mode2levelInfinite = 1;
        foodX_mode2levelInfinite = -1;
        foodY_mode2levelInfinite = -1;
        gamePaused_mode2levelInfinite = true;
        gameOver_mode2levelInfinite = false;

        snakeBody_mode2levelInfinite[0][0] = x_mode2levelInfinite;
        snakeBody_mode2levelInfinite[0][1] = y_mode2levelInfinite;


        barriers_mode2levelInfinite.clear();
        spawnBarrier_mode2levelInfinite();
        spawnBarrier_mode2levelInfinite();


        foodX_mode2levelInfinite = -1;
        foodY_mode2levelInfinite = -1;

        system("cls");
        cout << "Restarting Infinite Mode! Good luck!\n";
    }
    else if (level == 5) {
        int x_mode3 = 475, y_mode3 = 240;
        int w_mode3, W_mode3 = 0;
        int score_mode3 = 0;
        int snakeSpeed_mode3;


        cout << "Enter the snake speed (e.g., 35 for medium, lower for faster, higher for slower): ";
        cin >> snakeSpeed_mode3;

        snakeBody_mode3[0][0] = x_mode3;
        snakeBody_mode3[0][1] = y_mode3;

        customSpawnBarrier_mode3();


        score_mode3 = 0;
        snakeLength_mode3 = 1;

        system("cls");
        cout << "Restarting Mode 3 with Custom Speed! Good luck!\n";
    }


}

int readHighscore(int mode) {
    string filename = "highscore_mode" + to_string(mode) + ".txt";
    ifstream inFile(filename);
    int highscore = 0;

    if (inFile.is_open()) {
        inFile >> highscore;
        inFile.close();
    }

    return highscore;
}


void writeHighscore(int mode, int newHighscore) {
    string filename = "highscore_mode" + to_string(mode) + ".txt";
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << newHighscore;
        outFile.close();
    }
}

void checkAndUpdateHighscore(int mode, int currentScore) {
    int highscore = readHighscore(mode);

    if (currentScore > highscore) {
        cout << "New highscore : " << currentScore << "!" << endl;
        writeHighscore(mode, currentScore);
    }
    else {
        cout << "Current highscore : " << highscore << endl;
    }
}

int main() {
    int selectedLevel = 4;
    int whichKey = 0;
    bool running = true;


    int selectedColor = 0;
    int selectedMode = 0;


    int selectedColorRGB[3] = { 0, 0, 0 };

    myRectspecific(3, 150, 300, 400, 0, 0, 0);


    displayMenu();


    while (true) {

        if (isCursorKeyPressed(whichKey)) {
            if (whichKey == 5) {
                myRectspecific(3, 150, 300, 400, 0, 0, 0);
                clearConsole();
                break;
            }
        }
    }


    while (running) {
        myRectspecific(3, 150, 300, 400, 0, 0, 0);
        gotoxy(8, 10);
        cout << "Select a colour: ";
        gotoxy(7, 12);
        cout << "<";
        gotoxy(21, 12);
        cout << ">";

        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        drawSnake(selectedColor, 20, 14);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));


        if (isCursorKeyPressed(whichKey)) {
            if (whichKey == 2) {
                selectedColor = (selectedColor + 1) % 6;
            }
            else if (whichKey == 1) {
                selectedColor = (selectedColor - 1 + 6) % 6;
            }
            else if (whichKey == 5) {

                int colors[][3] = {
                    {255, 0, 0},
                    {0, 0, 255},
                    {255, 255, 0},
                    {255, 165, 0},
                    {128, 0, 128},
                    {255, 192, 203}
                };
                selectedColorRGB[0] = colors[selectedColor][0];
                selectedColorRGB[1] = colors[selectedColor][1];
                selectedColorRGB[2] = colors[selectedColor][2];

                clearConsole();
                break;
            }
        }
    }
    clearConsole();


    while (running) {
        myRectspecific(3, 150, 300, 400, 0, 0, 0);
        displayModes(selectedMode);


        if (isCursorKeyPressed(whichKey)) {
            if (whichKey == 2) {
                selectedMode = (selectedMode + 1) % 3;
            }
            else if (whichKey == 1) {
                selectedMode = (selectedMode - 1 + 3) % 3;
            }
            else if (whichKey == 5) {
                clearConsole();
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }


    clearConsole();


    if (selectedMode == 1) {
        int levelIndex = 0;

        while (running) {

            myRectspecific(3, 150, 300, 400, 0, 0, 0);
            displayLevels(levelIndex);


            if (isCursorKeyPressed(whichKey)) {
                if (whichKey == 2) {
                    levelIndex = (levelIndex + 1) % 4;
                }
                else if (whichKey == 1) {
                    levelIndex = (levelIndex - 1 + 4) % 4;
                }
                else if (whichKey == 5) {
                    clearConsole();
                    selectedLevel = levelIndex;
                    break;
                }
            }


            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }


        clearConsole();
    }


    if (selectedMode == 0)
    {
        srand(static_cast<unsigned>(time(0)));

        int x_mode1 = 475, y_mode1 = 240;
        int w_mode1, W_mode1 = 0;
        int score_mode1 = 0;

        snakeBody_mode1[0][0] = x_mode1;
        snakeBody_mode1[0][1] = y_mode1;


        cout << "Infinte Mode!" << endl;
        checkAndUpdateHighscore(0, score_mode1);

        while (true) {

            myRect(395, 115, 755, 365, 123, 158, 2);
            myRect(400, 120, 750, 360, 154, 197, 3);

            if (foodX_mode1 == -1 && foodY_mode1 == -1) {
                spawnFoodmode1();
            }


            myEllipse(foodX_mode1, foodY_mode1, foodX_mode1 + 11, foodY_mode1 + 11, 0, 0, 0);
            myEllipse(foodX_mode1, foodY_mode1, foodX_mode1 + 9, foodY_mode1 + 9, 255, 0, 0);


            if (isCursorKeyPressed(w_mode1)) {
                W_mode1 = w_mode1;
            }


            updateSnakemode1(x_mode1, y_mode1, W_mode1);


            if (checkFoodCollisionmode1(x_mode1, y_mode1)) {
                score_mode1++;
                cout << "\rScore: " << score_mode1 << " ";
                snakeLength_mode1++;
                spawnFoodmode1();
            }

            renderSnakemode1(selectedColorRGB[0], selectedColorRGB[1], selectedColorRGB[2]);


            if (checkSelfCollisionmode1()) {
                system("cls");
                cout << "\nCollision detected! Game Over!" << endl;
                checkAndUpdateHighscore(0, score_mode1);
                cout << " Options\n";
                cout << " 1. Restart Level\n";
                cout << " 2. Exit\n";
                cout << " Select an option... : ";
                int choice;
                do {
                    cin >> choice;
                    if (choice != 1 && choice != 2) {
                        cout << "Please select one of the available options...\n";
                    }
                } while (choice != 1 && choice != 2);
                if (choice == 1) {
                    Restartlevel(0);
                    score_mode1 = 0;
                    checkAndUpdateHighscore(0, score_mode1);
                    continue;
                }
                else {
                    exit(0);
                }
            }

            Sleep(25);
        }
    }
    if (selectedLevel == 1)

    {

        srand(static_cast<unsigned>(time(0)));

        int x_mode2level2 = 475, y_mode2level2 = 240;
        int W_mode2level2 = 0;

        snakeBody_mode2level2[0][0] = x_mode2level2;
        snakeBody_mode2level2[0][1] = y_mode2level2;

        spawnFixedBarriers_mode2level2();

        cout << "Level 2!" << endl;
        checkAndUpdateHighscore(1, score_mode2level2);


        while (!gameOver_mode2level2) {



            myRect(395, 115, 755, 365, 123, 158, 2);
            myRect(400, 120, 750, 360, 154, 197, 3);

            renderBarriers_mode2level2();

            if (foodX_mode2level2 == -1 && foodY_mode2level2 == -1) {
                spawnFood_mode2level2();
            }
            myEllipse(foodX_mode2level2, foodY_mode2level2, foodX_mode2level2 + 11, foodY_mode2level2 + 11, 0, 0, 0);
            myEllipse(foodX_mode2level2, foodY_mode2level2, foodX_mode2level2 + 9, foodY_mode2level2 + 9, 255, 0, 0);

            renderSnake_mode2level2(selectedColorRGB[0], selectedColorRGB[1], selectedColorRGB[2]);


            if (isCursorKeyPressed(W_mode2level2)) {
                gamePaused_mode2level2 = false;
            }


            if (!gamePaused_mode2level2) {
                updateSnake_mode2level2(x_mode2level2, y_mode2level2, W_mode2level2);


                if (checkFoodCollision_mode2level2(x_mode2level2, y_mode2level2)) {
                    score_mode2level2++;
                    cout << "\rScore: " << score_mode2level2 << " ";
                    snakeLength_mode2level2++;
                    spawnFood_mode2level2();
                }
            }


            if (checkWallCollision_mode2level2(x_mode2level2, y_mode2level2) || checkSelfCollision_mode2level2() || checkBarrierCollision_mode2level2(x_mode2level2, y_mode2level2)) {
                system("cls");
                cout << "\nCollision detected! Game Over!" << endl;
                checkAndUpdateHighscore(1, score_mode2level2);


                cout << " Options\n";
                cout << " 1. Restart Level\n";
                cout << " 2. Exit\n";
                cout << " Select an option... : ";
                int choice;
                do {
                    cin >> choice;
                    if (choice != 1 && choice != 2) {
                        cout << "Please select one of the available options...\n";
                    }
                } while (choice != 1 && choice != 2);
                if (choice == 1) {
                    Restartlevel(2);
                    score_mode2level2 = 0;
                    checkAndUpdateHighscore(1, score_mode2level2);
                    continue;

                }
                else {
                    exit(0);
                }
            }


            Sleep(35);
        }



    }

    if (selectedLevel == 2) {
        {

            srand(static_cast<unsigned>(time(0)));

            int x_mode2level3 = 475, y_mode2level3 = 260;
            int W_mode2level3 = 0;


            snakeBody_mode1[0][0] = x_mode2level3;
            snakeBody_mode1[0][1] = y_mode2level3;

            spawnFixedBarriers_mode2level3();

            cout << "Level 3!" << endl;
            checkAndUpdateHighscore(2, score_mode2level3);
            while (!gameOver_mode2level3) {
                myRect(395, 115, 755, 365, 123, 158, 2);
                myRect(400, 120, 750, 360, 154, 197, 3);

                renderBarriers_mode2level3();


                if (foodX_mode2level3 == -1 && foodY_mode2level3 == -1) {
                    spawnFood_mode2level3();
                }
                myEllipse(foodX_mode2level3, foodY_mode2level3, foodX_mode2level3 + 11, foodY_mode2level3 + 11, 0, 0, 0);
                myEllipse(foodX_mode2level3, foodY_mode2level3, foodX_mode2level3 + 9, foodY_mode2level3 + 9, 255, 0, 0);

                renderSnake_mode2level3(selectedColorRGB[0], selectedColorRGB[1], selectedColorRGB[2]);


                if (isCursorKeyPressed(W_mode2level3)) {
                    gamePaused_mode2level3 = false;
                }


                if (!gamePaused_mode2level3) {
                    updateSnake_mode2level3(x_mode2level3, y_mode2level3, W_mode2level3);


                    if (checkFoodCollision_mode2level3(x_mode2level3, y_mode2level3)) {
                        score_mode2level3++;
                        cout << "\rScore: " << score_mode2level3 << " ";
                        snakeLength_mode2level3++;
                        spawnFood_mode2level3();
                    }
                }


                if (checkWallCollision_mode2level3(x_mode2level3, y_mode2level3) || checkSelfCollision_mode2level3() || checkBarrierCollision_mode2level3(x_mode2level3, y_mode2level3)) {
                    system("cls");
                    cout << "\nCollision detected! Game Over!" << endl;
                    checkAndUpdateHighscore(2, score_mode2level3);
                    cout << " Options\n";
                    cout << " 1. Restart Level\n";
                    cout << " 2. Exit\n";
                    cout << " Select an option... : ";
                    int choice;
                    do {
                        cin >> choice;
                        if (choice != 1 && choice != 2) {
                            cout << "Please select one of the available options...\n";
                        }
                    } while (choice != 1 && choice != 2);
                    if (choice == 1) {
                        Restartlevel(3);
                        score_mode2level3 = 0;
                        checkAndUpdateHighscore(2, score_mode2level3);
                        continue;
                    }
                    else {
                        exit(0);
                    }
                }


                Sleep(30);
            }
        }
    }
    if (selectedLevel == 0) {
        srand(static_cast<unsigned>(time(0)));

        int x_mode2level1 = 475, y_mode2level1 = 240;
        int W_mode2level1 = 0;

        snakeBody_mode2level1[0][0] = x_mode2level1;
        snakeBody_mode2level1[0][1] = y_mode2level1;

        spawnFixedBarriers_mode2level1();

        cout << "Level 1!" << endl;
        checkAndUpdateHighscore(3, score_mode2level1);

        while (!gameOver_mode2level1) {
            myRect(395, 115, 755, 365, 123, 158, 2);
            myRect(400, 120, 750, 360, 154, 197, 3);

            renderBarriers_mode2level1();

            if (foodX_mode2level1 == -1 && foodY_mode2level1 == -1) {
                spawnFood_mode2level1();
            }
            myEllipse(foodX_mode2level1, foodY_mode2level1, foodX_mode2level1 + 11, foodY_mode2level1 + 11, 0, 0, 0);
            myEllipse(foodX_mode2level1, foodY_mode2level1, foodX_mode2level1 + 9, foodY_mode2level1 + 9, 255, 0, 0);

            renderSnake_mode2level1(selectedColorRGB[0], selectedColorRGB[1], selectedColorRGB[2]);


            if (isCursorKeyPressed(W_mode2level1)) {
                gamePaused_mode2level1 = false;
            }


            if (!gamePaused_mode2level1) {
                updateSnake_mode2level1(x_mode2level1, y_mode2level1, W_mode2level1);


                if (checkFoodCollision_mode2level1(x_mode2level1, y_mode2level1)) {
                    score_mode2level1++;
                    cout << "\rScore: " << score_mode2level1 << " ";
                    snakeLength_mode2level1++;
                    spawnFood_mode2level1();
                }
            }


            if (checkWallCollision_mode2level1(x_mode2level1, y_mode2level1) || checkSelfCollision_mode2level1() || checkBarrierCollision_mode2level1(x_mode2level1, y_mode2level1)) {
                system("cls");
                cout << "\nCollision detected! Game Over!" << endl;
                checkAndUpdateHighscore(3, score_mode2level1);
                cout << " Options\n";
                cout << " 1. Restart Level\n";
                cout << " 2. Exit\n";
                cout << " Select an option... : ";
                int choice;
                do {
                    cin >> choice;
                    if (choice != 1 && choice != 2) {
                        cout << "Please select one of the available options...\n";
                    }
                } while (choice != 1 && choice != 2);
                if (choice == 1) {
                    Restartlevel(1);
                    score_mode2level1 = 0;
                    checkAndUpdateHighscore(3, score_mode2level1);
                    continue;
                }
                else {
                    exit(0);
                }
            }


            Sleep(35);
        }
    }

    if (selectedLevel == 3) {
        {
            srand(static_cast<unsigned>(time(0)));

            int x_mode2levelInfinite = 475, y_mode2levelInfinite = 240;
            int w_mode2levelInfinite, W_mode2levelInfinite = 0;

            snakeBody_mode2levelInfinite[0][0] = x_mode2levelInfinite;
            snakeBody_mode2levelInfinite[0][1] = y_mode2levelInfinite;

            spawnBarrier_mode2levelInfinite();
            spawnBarrier_mode2levelInfinite();
            cout << "Level 1!" << endl;
            checkAndUpdateHighscore(4, score_mode2levelInfinite);

            double gameSpeed_mode2levelInfinite = 25.0;

            while (!gameOver_mode2levelInfinite) {
                myRect(395, 115, 1295, 740, 123, 158, 2);


                myRect(400, 120, 1290, 735, 154, 197, 3);

                renderBarriers_mode2levelInfinite();

                if (foodX_mode2levelInfinite == -1 && foodY_mode2levelInfinite == -1) {
                    spawnFood_mode2levelInfinite();
                }
                myEllipse(foodX_mode2levelInfinite, foodY_mode2levelInfinite, foodX_mode2levelInfinite + 11, foodY_mode2levelInfinite + 11, 0, 0, 0);
                myEllipse(foodX_mode2levelInfinite, foodY_mode2levelInfinite, foodX_mode2levelInfinite + 9, foodY_mode2levelInfinite + 9, 255, 0, 0);

                renderSnake_mode2levelInfinite(selectedColorRGB[0], selectedColorRGB[1], selectedColorRGB[2]);

                if (isCursorKeyPressed(w_mode2levelInfinite)) {
                    W_mode2levelInfinite = w_mode2levelInfinite;
                    gamePaused_mode2levelInfinite = false;
                }

                if (!gamePaused_mode2levelInfinite) {
                    updateSnake_mode2levelInfinite(x_mode2levelInfinite, y_mode2levelInfinite, W_mode2levelInfinite);

                    if (checkFoodCollision_mode2levelInfinite(x_mode2levelInfinite, y_mode2levelInfinite)) {
                        score_mode2levelInfinite++;
                        cout << "\rScore: " << score_mode2levelInfinite << " ";
                        snakeLength_mode2levelInfinite++;
                        spawnFood_mode2levelInfinite();


                        if (gameSpeed_mode2levelInfinite > 1) {
                            gameSpeed_mode2levelInfinite -= 0.1;
                        }

                        if (score_mode2levelInfinite % 10 == 0) {
                            levelUp_mode2levelInfinite();
                        }
                    }
                }

                if (checkWallCollision_mode2levelInfinite(x_mode2levelInfinite, y_mode2levelInfinite) ||
                    checkSelfCollision_mode2levelInfinite() ||
                    checkBarrierCollision_mode2levelInfinite(x_mode2levelInfinite, y_mode2levelInfinite)) {
                    system("cls");
                    cout << "\nCollision detected! Game Over!" << endl;
                    checkAndUpdateHighscore(4, score_mode2levelInfinite);
                    cout << " Options\n";
                    cout << " 1. Restart Level\n";
                    cout << " 2. Exit\n";
                    cout << " Select an option... : ";
                    int choice;
                    do {
                        cin >> choice;
                        if (choice != 1 && choice != 2) {
                            cout << "Please select one of the available options...\n";
                        }
                    } while (choice != 1 && choice != 2);
                    if (choice == 1) {
                        level_mode2levelInfinite = 1;
                        Restartlevel(4);
                        score_mode2levelInfinite = 0;
                        gameSpeed_mode2levelInfinite = 25.0;
                        checkAndUpdateHighscore(4, score_mode2levelInfinite);
                        continue;
                    }
                    else {
                        exit(0);
                    }
                }


                Sleep(static_cast<int>(gameSpeed_mode2levelInfinite));
            }
        }
    }

    if (selectedMode == 2) {

        srand(static_cast<unsigned>(time(0)));

        int x_mode3 = 475, y_mode3 = 240;
        int w_mode3, W_mode3 = 0;
        int score_mode3 = 0;
        int snakeSpeed_mode3;

        cout << "Custom Mode!" << endl;

        cout << "Enter the snake speed (e.g., 35 for medium, lower for faster, higher for slower): ";
        cin >> snakeSpeed_mode3;

        snakeBody_mode3[0][0] = x_mode3;
        snakeBody_mode3[0][1] = y_mode3;



        customSpawnBarrier_mode3();
        checkAndUpdateHighscore(5, score_mode3);
        system("cls");

        while (true) {
            myRect(395, 115, 755, 365, 123, 158, 2);
            myRect(400, 120, 750, 360, 154, 197, 3);

            renderBarriers_mode3();

            if (foodX_mode3 == -1 && foodY_mode3 == -1) {
                spawnFood_mode3();
            }
            myEllipse(foodX_mode3, foodY_mode3, foodX_mode3 + 11, foodY_mode3 + 11, 0, 0, 0);
            myEllipse(foodX_mode3, foodY_mode3, foodX_mode3 + 9, foodY_mode3 + 9, 255, 0, 0);

            if (isCursorKeyPressed(w_mode3)) {
                W_mode3 = w_mode3;
            }

            updateSnake_mode3(x_mode3, y_mode3, W_mode3);

            if (checkFoodCollision_mode3(x_mode3, y_mode3)) {
                score_mode3++;
                cout << "\rScore: " << score_mode3 << " ";
                snakeLength_mode3++;
                spawnFood_mode3();
            }

            renderSnake_mode3(selectedColorRGB[0], selectedColorRGB[1], selectedColorRGB[2]);

            if (checkWallCollision_mode3(x_mode3, y_mode3) || checkSelfCollision_mode3() || checkBarrierCollision_mode3(x_mode3, y_mode3)) {
                system("cls");
                cout << "\nCollision detected! Game Over!" << endl;
                checkAndUpdateHighscore(5, score_mode3);
                cout << " Options\n";
                cout << " 1. Restart Mode\n";
                cout << " 2. Exit\n";
                cout << " Select an option... : ";
                int choice;
                do {
                    cin >> choice;
                    if (choice != 1 && choice != 2) {
                        cout << "Please select one of the available options...\n";
                    }
                } while (choice != 1 && choice != 2);
                if (choice == 1) {
                    Restartlevel(5);
                    score_mode3 = 0;
                    checkAndUpdateHighscore(5, score_mode3);
                    continue;
                }
                else {
                    exit(0);
                }
            }
            Sleep(snakeSpeed_mode3);
        }



    }

    system("pause");
    return 0;


}