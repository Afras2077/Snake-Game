#pragma once
#include <windows.h>
#include<iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
const int MAX_SNAKE_SIZE = 1000;
int snakeBody[MAX_SNAKE_SIZE][2] = { 0 };
int snakeLength = 1;
const int MAX_SIZE = 400;
int foodX = -1, foodY = -1;



void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void setConsoleColor(int red, int green, int blue) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        return;
    }

    // Convert RGB to a 4-bit color approximation (console supports limited colors)
    int colorCode = 0;
    if (red > 128) colorCode |= FOREGROUND_RED;
    if (green > 128) colorCode |= FOREGROUND_GREEN;
    if (blue > 128) colorCode |= FOREGROUND_BLUE;

    // Add intensity for brighter colors
    if (red > 200 || green > 200 || blue > 200) {
        colorCode |= FOREGROUND_INTENSITY;
    }

    // Set the console text attribute
    SetConsoleTextAttribute(hConsole, colorCode);
}


void myRect(int x1, int y1, int x2, int y2, int X, int Y, int Z) {
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(X, Y, Z));
    SelectObject(device_context, pen);
    HBRUSH brush = ::CreateSolidBrush(RGB(X, Y, Z));
    SelectObject(device_context, brush);
    Rectangle(device_context, x1, y1, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}

void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B) {
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(device_context, pen);
    HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B));
    SelectObject(device_context, brush);
    Ellipse(device_context, x1, y1, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}



void myLine3(int x1, int y1, int x2, int y2, int R, int G, int B)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
    HPEN pen = CreatePen(PS_SOLID, 3, RGB(R, G, B));
    SelectObject(device_context, pen);
    MoveToEx(device_context, x1, y1, NULL);
    LineTo(device_context, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
}
void myRect1(int x1, int y1, int x2, int y2, int R, int G, int B)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    SelectObject(device_context, pen);
    HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0)); //Fill color can also be passed as parameter to the function!!!

    SelectObject(device_context, brush);

    Rectangle(device_context, x1, y1, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}


bool isCursorKeyPressed(int& whichKey) {
    char key;
    key = GetAsyncKeyState(37);
    if (key == 1) { whichKey = 1; return true; }
    key = GetAsyncKeyState(38);
    if (key == 1) { whichKey = 3; return true; }
    key = GetAsyncKeyState(39);
    if (key == 1) { whichKey = 2; return true; }
    key = GetAsyncKeyState(40);
    if (key == 1) { whichKey = 4; return true; }
    key = GetAsyncKeyState('A');
    if (key == 1)
    {
        whichKey = 6;   // 6 to Swap the the candies left A key is pressed
        return true;
    }
    key = GetAsyncKeyState('W');
    if (key == 1)
    {
        whichKey = 7;   // 7 to Swap the the candies up W key is pressed
        return true;
    }
    key = GetAsyncKeyState('D');
    if (key == 1)
    {
        whichKey = 8;   // 8 to Swap the the candies right D key is pressed
        return true;
    }
    key = GetAsyncKeyState('S');
    if (key == 1)
    {
        whichKey = 9;   // 9 to Swap the the candies Down s key is pressed
        return true;
    }
    return false;
    return false;
}


int R[11] = { 255, 0, 0, 160, 255, 135, 152, 139, 222, 128, 255 };
int G[11] = { 0, 255, 0, 32, 182, 206, 251, 69, 184, 120, 255 };
int B[11] = { 0, 0, 255, 240, 193, 235, 152, 19, 135, 0, 255 };
string colorNames[] = { "Red", "Green", "Blue", "Purple", "Light Pink", "Sky Blue",
                       "Pale Green", "Saddle Brown", "BurlyWood", "Olive", "White" };


bool isCursorKeyPressed1(int& whichKey) {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) { whichKey = 1; return true; }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { whichKey = 2; return true; }
    return false;
}

// Draw rectangle with specified color
void myRect2(int x1, int y1, int x2, int y2, int R, int G, int B) {
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(device_context, pen);
    HBRUSH brush = CreateSolidBrush(RGB(R, G, B));

    SelectObject(device_context, brush);
    Rectangle(device_context, x1, y1, x2, y2);

    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}

void printCentered(string text, int y) {
    int width = 115; //
    int x = (width - text.length()) / 2;
    COORD pos = { (SHORT)x, (SHORT)y };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    cout << text;
}
void drawChooseSnake() {
    int colorR = 250, colorG = 0, colorB = 0;

    // Letter C
    myRect(250, 100, 280, 105, colorR, colorG, colorB); // Top
    myRect(250, 100, 255, 150, colorR, colorG, colorB); // Left
    myRect(250, 145, 280, 150, colorR, colorG, colorB); // Bottom

    myLine3(250, 250, 225, 270, 100, 100, 100);
    myLine3(225, 270, 250, 290, 100, 100, 100);

    // Letter H
    myRect(290, 100, 295, 150, colorR, colorG, colorB); // Left vertical
    myRect(310, 100, 315, 150, colorR, colorG, colorB); // Right vertical
    myRect(290, 120, 315, 125, colorR, colorG, colorB); // Middle horizontal

    // Letter O
    myRect(330, 100, 335, 150, colorR, colorG, colorB); // Left vertical
    myRect(350, 100, 355, 150, colorR, colorG, colorB); // Right vertical
    myRect(335, 100, 350, 105, colorR, colorG, colorB); // Top
    myRect(335, 145, 350, 150, colorR, colorG, colorB); // Bottom

    // Letter O 
    myRect(370, 100, 375, 150, colorR, colorG, colorB); // Left vertical
    myRect(390, 100, 395, 150, colorR, colorG, colorB); // Right vertical
    myRect(375, 100, 390, 105, colorR, colorG, colorB); // Top
    myRect(375, 145, 390, 150, colorR, colorG, colorB); // Bottom

    // Letter S
    myRect(410, 100, 440, 105, colorR, colorG, colorB); // Top
    myRect(410, 100, 415, 125, colorR, colorG, colorB); // Left top
    myRect(410, 120, 440, 125, colorR, colorG, colorB); // Middle
    myRect(435, 125, 440, 150, colorR, colorG, colorB); // Right bottom
    myRect(410, 145, 440, 150, colorR, colorG, colorB); // Bottom

    // Letter E
    myRect(460, 100, 465, 150, colorR, colorG, colorB); // Left vertical
    myRect(460, 100, 485, 105, colorR, colorG, colorB); // Top
    myRect(460, 120, 480, 125, colorR, colorG, colorB); // Middle
    myRect(460, 145, 485, 150, colorR, colorG, colorB); // Bottom



    // Letter S
    myRect(520, 100, 550, 105, colorR, colorG, colorB); // Top
    myRect(520, 100, 525, 125, colorR, colorG, colorB); // Left top
    myRect(520, 120, 550, 125, colorR, colorG, colorB); // Middle
    myRect(545, 125, 550, 150, colorR, colorG, colorB); // Right bottom
    myRect(520, 145, 550, 150, colorR, colorG, colorB); // Bottom

    // Letter N
    myRect(570, 100, 575, 150, colorR, colorG, colorB); // Left vertical
    myLine3(572, 100, 595, 147, colorR, colorG, colorB); // Diagonal
    myRect(595, 100, 600, 150, colorR, colorG, colorB); // Right vertical

    // Letter A
    myRect(620, 100, 625, 150, colorR, colorG, colorB); // Left vertical
    myRect(640, 100, 645, 150, colorR, colorG, colorB); // Right vertical
    myRect(625, 100, 640, 105, colorR, colorG, colorB); // Top
    myRect(625, 120, 640, 125, colorR, colorG, colorB); // Middle
    // Left vertical of K
    myRect(660, 100, 665, 150, colorR, colorG, colorB);

    myLine3(665, 125, 690, 100, colorR, colorG, colorB);  // First upper diagonal line
    myLine3(690, 100, 691, 102, colorR, colorG, colorB);  // Second line to make it thiccc
    myLine3(665, 128, 690, 103, colorR, colorG, colorB);

    // Lower diagonal (thiccc)
    myLine3(665, 125, 690, 145, colorR, colorG, colorB);
    myLine3(690, 145, 691, 146, colorR, colorG, colorB);
    myLine3(665, 128, 690, 148, colorR, colorG, colorB);


    // Letter E
    myRect(710, 100, 715, 150, colorR, colorG, colorB);
    myRect(710, 100, 735, 105, colorR, colorG, colorB);
    myRect(710, 120, 730, 125, colorR, colorG, colorB);
    myRect(710, 145, 735, 150, colorR, colorG, colorB);



    myLine3(735, 250, 760, 270, 100, 100, 100);
    myLine3(760, 270, 735, 290, 100, 100, 100);
}

bool checkFoodCollision(int x, int y) {
    return (x >= foodX - 10 && x <= foodX + 10 && y >= foodY && y - 10 <= foodY + 10);
}


void updateSnake(int& x, int& y, int& W) {
    static int currentDirection = 0;

    // Prevent 180-degree turns
    if ((currentDirection == 1 && W == 2) || (currentDirection == 2 && W == 1) ||
        (currentDirection == 3 && W == 4) || (currentDirection == 4 && W == 3)) {
        W = currentDirection;
    }
    else {
        currentDirection = W; // Update to the new direction
    }


    for (int i = snakeLength - 1; i > 0; --i) {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
    }


    if (currentDirection == 1 || currentDirection == 6)
        snakeBody[0][0] -= 5;
    else if (currentDirection == 2 || currentDirection == 8)
        snakeBody[0][0] += 5;
    else if (currentDirection == 3 || currentDirection == 7)
        snakeBody[0][1] -= 5;
    else if (currentDirection == 4 || currentDirection == 9)
        snakeBody[0][1] += 5;


    x = snakeBody[0][0];
    y = snakeBody[0][1];
}


void renderSnake(int X, int Y, int Z) {
    for (int i = 0; i < snakeLength; ++i) {
        myRect(snakeBody[i][0], snakeBody[i][1], snakeBody[i][0] + 7, snakeBody[i][1] + 7, X, Y, Z);
    }
}



bool checkSelfCollision() {
    for (int i = 1; i < snakeLength; ++i) {
        if (snakeBody[0][0] == snakeBody[i][0] && snakeBody[0][1] == snakeBody[i][1]) {
            return true;
        }
    }
    return false;
}

bool checkCollision(int x, int y) {
    int rect1_left = 300, rect1_top = 120, rect1_right = 650, rect1_bottom = 360;
    int line1_x1 = 360, line1_y1 = 120, line1_x2 = 360, line1_y2 = 200;
    int line2_x1 = 590, line2_y1 = 280, line2_x2 = 590, line2_y2 = 358;
    int line3_x1 = 300, line3_y1 = 280, line3_x2 = 360, line3_y2 = 280;
    int line4_x1 = 590, line4_y1 = 200, line4_x2 = 648, line4_y2 = 200;


    if (x < rect1_left + 4 || x > rect1_right - 4 || y < rect1_top + 4 || y > rect1_bottom - 4) {
        return true;
    }

    if ((x >= line1_x1 - 4 && x <= line1_x1 + 4 && y >= line1_y1 && y <= line1_y2) ||
        (x >= line2_x1 - 4 && x <= line2_x1 + 4 && y >= line2_y1 && y <= line2_y2)) {
        return true;
    }


    if ((y >= line3_y1 - 4 && y <= line3_y1 + 4 && x >= line3_x1 && x <= line3_x2) ||
        (y >= line4_y1 - 4 && y <= line4_y1 + 4 && x >= line4_x1 && x <= line4_x2)) {
        return true;
    }

    return false;
}






bool checkCollision2(int x, int y) {
    int rect1_left = 300, rect1_top = 120, rect1_right = 650, rect1_bottom = 360;
    int line1_x1 = 360, line1_y1 = 120, line1_x2 = 360, line1_y2 = 200;
    int line2_x1 = 590, line2_y1 = 280, line2_x2 = 590, line2_y2 = 358;
    int line3_x1 = 300, line3_y1 = 280, line3_x2 = 360, line3_y2 = 280;
    int line4_x1 = 590, line4_y1 = 200, line4_x2 = 648, line4_y2 = 200;
    int line5_x1 = 360, line5_y1 = 200, line5_x2 = 440, line5_y2 = 200;
    int line6_x1 = 512, line6_y1 = 280, line6_x2 = 590, line6_y2 = 280;
    int line7_x1 = 360, line7_y1 = 280, line7_x2 = 440, line7_y2 = 280;
    int line8_x1 = 590, line8_y1 = 200, line8_x2 = 510, line8_y2 = 200;


    if (x < rect1_left + 4 || x > rect1_right - 4 || y < rect1_top + 4 || y > rect1_bottom - 4) {
        return true;
    }



    if ((x >= line1_x1 - 4 && x <= line1_x1 + 4 && y >= line1_y1 && y <= line1_y2) ||
        (x >= line2_x1 - 4 && x <= line2_x1 + 4 && y >= line2_y1 && y <= line2_y2)) {
        return true;
    }


    if ((y >= line3_y1 - 4 && y <= line3_y1 + 4 && x >= line3_x1 && x <= line3_x2) ||
        (y >= line4_y1 - 4 && y <= line4_y1 + 4 && x >= line4_x1 && x <= line4_x2) ||
        (x >= line5_x1 && x <= line5_x2 && y >= line5_y1 - 4 && y <= line5_y1 + 4) ||
        (x >= line6_x1 && x <= line6_x2 && y >= line6_y1 - 4 && y <= line6_y1 + 4) ||
        (y >= line7_y1 - 4 && y <= line7_y1 + 4 && x >= line7_x1 && x <= line7_x2) ||
        (y >= line8_y1 - 4 && y <= line8_y1 + 4 && x >= line8_x2 && x <= line8_x1)) {
        return true;
    }


    return false;
}
bool checkCollision3(int x, int y) {
    int rect1_left = 300, rect1_top = 120, rect1_right = 650, rect1_bottom = 360;
    int line1_x1 = 360, line1_y1 = 120, line1_x2 = 360, line1_y2 = 200;
    int line2_x1 = 590, line2_y1 = 280, line2_x2 = 590, line2_y2 = 358;
    int line3_x1 = 300, line3_y1 = 280, line3_x2 = 360, line3_y2 = 280;
    int line4_x1 = 590, line4_y1 = 200, line4_x2 = 648, line4_y2 = 200;
    int line5_x1 = 360, line5_y1 = 200, line5_x2 = 440, line5_y2 = 200;
    int line6_x1 = 512, line6_y1 = 280, line6_x2 = 590, line6_y2 = 280;
    int line7_x1 = 360, line7_y1 = 280, line7_x2 = 440, line7_y2 = 280;
    int line8_x1 = 590, line8_y1 = 200, line8_x2 = 510, line8_y2 = 200;
    int line9_x1 = 360, line9_y1 = 225, line9_x2 = 590, line9_y2 = 225;
    int line10_x1 = 360, line10_y1 = 255, line10_x2 = 590, line10_y2 = 255;
    int line11_x1 = 512, line11_y1 = 280, line11_x2 = 512, line11_y2 = 255;
    int line12_x1 = 440, line12_y1 = 200, line12_x2 = 440, line12_y2 = 225;


    if (x < rect1_left + 4 || x > rect1_right - 4 || y < rect1_top + 4 || y > rect1_bottom - 4) {
        return true;
    }


    if ((x >= line1_x1 - 4 && x <= line1_x1 + 4 && y >= line1_y1 && y <= line1_y2) ||
        (x >= line2_x1 - 4 && x <= line2_x1 + 4 && y >= line2_y1 && y <= line2_y2) ||
        (x >= line11_x1 - 4 && x <= line11_x1 + 4 && y >= line11_y2 && y <= line11_y1) ||
        (x >= line12_x1 - 4 && x <= line12_x1 + 4 && y >= line12_y1 && y <= line12_y2)) {
        return true;
    }


    if ((y >= line3_y1 - 4 && y <= line3_y1 + 4 && x >= line3_x1 && x <= line3_x2) ||
        (y >= line4_y1 - 4 && y <= line4_y1 + 4 && x >= line4_x1 && x <= line4_x2) ||
        (x >= line5_x1 && x <= line5_x2 && y >= line5_y1 - 4 && y <= line5_y1 + 4) ||
        (x >= line6_x1 && x <= line6_x2 && y >= line6_y1 - 4 && y <= line6_y1 + 4) ||
        (y >= line7_y1 - 4 && y <= line7_y1 + 4 && x >= line7_x1 && x <= line7_x2) ||
        (y >= line8_y1 - 4 && y <= line8_y1 + 4 && x >= line8_x2 && x <= line8_x1) ||
        (x >= line9_x1 && x <= line9_x2 && y >= line9_y1 - 4 && y <= line9_y1 + 4) ||
        (x >= line10_x1 && x <= line10_x2 && y >= line10_y1 - 4 && y <= line10_y1 + 4)) {
        return true;
    }


    return false;
}

bool checkCollision4(int x, int y, int x1[], int y1[], int x2[], int y2[], int Walls, int i) {
    int rect1_left = 300, rect1_top = 120, rect1_right = 650, rect1_bottom = 360;
    int line1_x1 = 360, line1_y1 = 120, line1_x2 = 360, line1_y2 = 200;
    int line2_x1 = 590, line2_y1 = 280, line2_x2 = 590, line2_y2 = 358;
    int line3_x1 = 300, line3_y1 = 280, line3_x2 = 360, line3_y2 = 280;
    int line4_x1 = 590, line4_y1 = 200, line4_x2 = 648, line4_y2 = 200;



    if (x < rect1_left + 4 || x > rect1_right - 4 || y < rect1_top + 4 || y > rect1_bottom - 4) {
        return true;
    }
    for (int i = 0; i < Walls; i++)
    {
        if (x1[i] < x2[i] && y1[i] == y2[i])
        {
            if (x >= x1[i] && x <= x2[i] && y <= y1[i] + 4 && y >= y1[i] - 4)
                return true;
        }
        else if (x1[i] > x2[i] && y1[i] == y2[i])
        {
            if (x >= x2[i] && x <= x1[i] && y <= y1[i] + 4 && y >= y1[i] - 4)
                return true;
        }
        else if (x1[i] == x2[i] && y1[i] < y2[i])
        {
            if (x >= x1[i] - 4 && x <= x1[i] + 4 && y >= y1[i] && y <= y2[i])
                return true;
        }
        else if (x1[i] == x2[i] && y1[i] > y2[i])
        {
            if (x >= x1[i] - 4 && x <= x1[i] + 4 && y <= y1[i] && y >= y2[i])
                return true;
        }
        else if (x1[i] == x2[i] && y1[i] == y2[i])
        {
            if (x >= x1[i] - 4 && x <= x1[i] + 4 && y <= y1[i] + 4 && y >= y1[i] - 4)
                return true;
        }


    }
    return false;

}

void spawnFood() {
    int validPosition = 0;

    while (!validPosition) {
        foodX = 300 + rand() % (650 - 300 - 10);
        foodY = 120 + rand() % (360 - 120 - 10);

        int overlapsInnerLines =
            ((foodX >= 348 && foodX <= 372 && foodY >= 113 && foodY <= 207) ||
                (foodX >= 578 && foodX <= 602 && foodY >= 273 && foodY <= 365) ||
                (foodY >= 268 && foodY <= 292 && foodX >= 293 && foodX <= 367) ||
                (foodY >= 188 && foodY <= 212 && foodX >= 583 && foodX <= 655));

        if (!overlapsInnerLines) {
            validPosition = 1;
        }
    }
}
void spawnFood2() {
    int validPosition = 0; // Using int instead of bool as per your preference.

    while (!validPosition) {
        foodX = 300 + rand() % (650 - 300 - 10);
        foodY = 120 + rand() % (360 - 120 - 10);

        int overlapsInnerLines =
            ((foodX >= 343 && foodX <= 377 && foodY >= 103 && foodY <= 217) ||
                (foodX >= 573 && foodX <= 607 && foodY >= 263 && foodY <= 377) ||
                (foodY >= 263 && foodY <= 297 && foodX >= 283 && foodX <= 377) ||
                (foodY >= 183 && foodY <= 217 && foodX >= 573 && foodX <= 667) ||
                (foodX >= 343 && foodX <= 457 && foodY >= 183 && foodY <= 217) ||
                (foodX >= 493 && foodX <= 607 && foodY >= 263 && foodY <= 297));

        if (!overlapsInnerLines) {
            validPosition = 1;
        }
    }
}
void spawnFood3() {
    int validPosition = 0;

    while (!validPosition) {
        foodX = 300 + rand() % (650 - 300 - 10);
        foodY = 120 + rand() % (360 - 120 - 10);

        int overlapsInnerLines =
            ((foodX >= 343 && foodX <= 377 && foodY >= 103 && foodY <= 217) ||
                (foodX >= 573 && foodX <= 607 && foodY >= 263 && foodY <= 377) ||
                (foodY >= 263 && foodY <= 297 && foodX >= 283 && foodX <= 377) ||
                (foodY >= 183 && foodY <= 217 && foodX >= 573 && foodX <= 667) ||
                (foodX >= 343 && foodX <= 597 && foodY >= 213 && foodY <= 237) ||
                (foodX >= 343 && foodX <= 597 && foodY >= 243 && foodY <= 267) ||
                (foodX >= 493 && foodX <= 527 && foodY >= 243 && foodY <= 297) ||
                (foodX >= 423 && foodX <= 457 && foodY >= 183 && foodY <= 237));

        if (!overlapsInnerLines) {
            validPosition = 1;
        }
    }
}




int screenWidth = 650;
int screenHeight = 500;


void spawnFoodI() {
    foodX = rand() % (screenWidth - 10);
    foodY = rand() % (screenHeight - 10);
}

bool checkFoodCollisionI(int x, int y) {
    return (x >= foodX - 10 && x <= foodX + 10 && y >= foodY && y - 10 <= foodY + 10);
}

void updateSnakeInfinite(int& x, int& y, int W) {
    static int currentDirection = 0;

    // Prevent 180-degree turns
    if ((currentDirection == 1 && W == 2) || (currentDirection == 2 && W == 1) ||
        (currentDirection == 3 && W == 4) || (currentDirection == 4 && W == 3)) {
        W = currentDirection;
    }
    else {
        currentDirection = W; // Update to the new direction
    }


    for (int i = snakeLength - 1; i > 0; --i) {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
    }


    if (currentDirection == 1) { // Left
        snakeBody[0][0] -= 10;
    }
    else if (currentDirection == 2) { // Right
        snakeBody[0][0] += 10;
    }
    else if (currentDirection == 3) { // Up
        snakeBody[0][1] -= 10;
    }
    else if (currentDirection == 4) { // Down
        snakeBody[0][1] += 10;
    }


    x = snakeBody[0][0];
    y = snakeBody[0][1];


    if (x >= screenWidth) {
        x = 0;
    }
    else if (x < 0) {
        x = screenWidth - 10;
    }

    if (y >= screenHeight) {
        y = 0;
    }
    else if (y < 0) {
        y = screenHeight - 10;
    }


    for (int i = 0; i < snakeLength; ++i) {
        if (snakeBody[i][0] >= screenWidth) {
            snakeBody[i][0] = 0;
        }
        else if (snakeBody[i][0] < 0) {
            snakeBody[i][0] = screenWidth - 10;
        }

        if (snakeBody[i][1] >= screenHeight) {
            snakeBody[i][1] = 0;
        }
        else if (snakeBody[i][1] < 0) {
            snakeBody[i][1] = screenHeight - 10;
        }
    }
}




void renderSnakeI(int X, int Y, int Z) {
    for (int i = 0; i < snakeLength; ++i) {
        myRect(snakeBody[i][0], snakeBody[i][1], snakeBody[i][0] + 7, snakeBody[i][1] + 7, X, Y, Z);
    }
}

bool checkSelfCollisionI() {
    for (int i = 1; i < snakeLength; ++i) {
        if (snakeBody[0][0] == snakeBody[i][0] && snakeBody[0][1] == snakeBody[i][1]) {
            return true;
        }
    }
    return false;
}
void drawLevel(int level, int X, int Y, int Z) {
    myRect1(300, 120, 650, 360, X, Y, Z);


    if (level >= 1) {
        myLine3(360, 120, 360, 200, 134, 145, 134);
        myLine3(590, 280, 590, 358, 134, 145, 134);
        myLine3(300, 280, 360, 280, 134, 145, 134);
        myLine3(590, 200, 648, 200, 134, 145, 134);
    }
    if (level >= 2) {
        myLine3(360, 200, 440, 200, 134, 145, 134);
        myLine3(512, 280, 590, 280, 134, 145, 134);
        myLine3(360, 280, 440, 280, 134, 145, 134);
        myLine3(590, 200, 510, 200, 134, 145, 134);
    }
    if (level >= 3) {
        myLine3(360, 225, 590, 225, 134, 145, 134);
        myLine3(360, 255, 590, 255, 134, 145, 134);
        myLine3(512, 280, 512, 255, 134, 145, 134);
        myLine3(440, 200, 440, 225, 134, 145, 134);
    }

}


void updateSnakeC(int& x, int& y, int W, int speed) {


    static int currentDirection = 0;

    // Prevent 180-degree turns
    if ((currentDirection == 1 && W == 2) || (currentDirection == 2 && W == 1) ||
        (currentDirection == 3 && W == 4) || (currentDirection == 4 && W == 3) ||
        (currentDirection == 6 && W == 8) || (currentDirection == 8 && W == 6) ||
        (currentDirection == 9 && W == 7) || (currentDirection == 7 && W == 9)) {
        W = currentDirection;
    }
    else {
        currentDirection = W; // Update to the new direction
    }


    for (int i = snakeLength - 1; i > 0; --i) {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
    }


    if (currentDirection == 1 || currentDirection == 6)
        snakeBody[0][0] -= speed;
    else if (currentDirection == 2 || currentDirection == 8)
        snakeBody[0][0] += speed;
    else if (currentDirection == 3 || currentDirection == 7)
        snakeBody[0][1] -= speed;
    else if (currentDirection == 4 || currentDirection == 9)
        snakeBody[0][1] += speed;


    x = snakeBody[0][0];
    y = snakeBody[0][1];
}



void spawnFood4(int x1[], int y1[], int x2[], int y2[], int Walls) {
    bool validPosition = false;
    while (!validPosition) {

        foodX = 320 + rand() % (630 - 320);
        foodY = 140 + rand() % (340 - 140);

        validPosition = true;


        for (int i = 0; i < Walls; i++) {
            if (x1[i] < x2[i] && y1[i] == y2[i]) {

                if (foodX >= x1[i] - 15 && foodX <= x2[i] + 15 &&
                    foodY >= y1[i] - 10 && foodY <= y1[i] + 10) {
                    validPosition = false;
                    break;
                }
            }
            else if (x1[i] > x2[i] && y1[i] == y2[i]) {

                if (foodX >= x2[i] - 15 && foodX <= x1[i] + 15 &&
                    foodY >= y1[i] - 10 && foodY <= y1[i] + 10) {
                    validPosition = false;
                    break;
                }
            }
            else if (x1[i] == x2[i] && y1[i] < y2[i]) {

                if (foodX >= x1[i] - 10 && foodX <= x1[i] + 10 &&
                    foodY >= y1[i] - 15 && foodY <= y2[i] + 15) {
                    validPosition = false;
                    break;
                }
            }
            else if (x1[i] == x2[i] && y1[i] > y2[i]) {

                if (foodX >= x1[i] - 10 && foodX <= x1[i] + 10 &&
                    foodY >= y2[i] - 15 && foodY <= y1[i] + 15) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
}








void gameOver(int score) {
    system("CLS");

    printCentered("Game Over!", 7);
    printCentered("Final Score: " + to_string(score), 8);
    printCentered("Press enter to return to the menu.", 9);
    cin.ignore();
    cin.get();
    cin.ignore();
    cin.get();
}

#include <windows.h>






int mainMenu() {
    int m = 1;
    const int menuOptions = 5;
    int key;

    while (true) {
        system("CLS");


        setConsoleColor(255, 255, 0);
        cout << "\n\n\n\n\n                                ======================================================";

        printCentered("HUNGRY SNAKE", 6);
        cout << "\n                              =========================================================\n";
        printCentered("Use arrow keys for movement and enter to Select.", 8);
        setConsoleColor(255, 255, 255);


        for (int i = 1; i <= menuOptions; i++) {
            string optionText;
            if (i == 1) optionText = "1- Play Endless Mode";
            else if (i == 2) optionText = "2- Play Level Mode";
            else if (i == 3) optionText = "3- Play Custom Mode";
            else if (i == 4) optionText = "4- View High Scores";
            else if (i == 5) optionText = "5- Exit";

            if (i == m) {

                setConsoleColor(0, 255, 255);
                printCentered("> " + optionText + " <", 8 + i);
            }
            else {
                setConsoleColor(255, 255, 255);
                printCentered(optionText, 8 + i);
            }
        }


        if (isCursorKeyPressed(key)) {
            if (key == 3) { // Up Arrow
                m = (m - 1 + menuOptions - 1) % menuOptions + 1; // Wrap around 
            }
            else if (key == 4) {
                m = (m) % menuOptions + 1;
            }
        }

        // Check for Enter key to select
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            setConsoleColor(255, 255, 255);
            system("CLS");
            Sleep(100);
            return m;
        }


    }
}


void resetGame(int score) {
    snakeLength = 1;
    snakeBody[0][0] = 0;
    snakeBody[0][1] = 0;
    for (int i = 1; i < MAX_SIZE; i++) {
        snakeBody[i][0] = -1; // Reset body positions 
        snakeBody[i][1] = -1;
    }


    foodX = -1;
    foodY = -1;


    score = 0;
}

int Menu2() {
    int type = 1;
    const int menuOptions = 2;
    int key;

    while (true) {
        system("CLS");


        setConsoleColor(255, 255, 0);
        cout << "\n\n\n\n\n                                ======================================================";


        printCentered("SELECT MODE", 6);

        cout << "\n                              =========================================================\n";
        setConsoleColor(255, 255, 255);
        for (int i = 1; i <= menuOptions; i++) {
            string optionText;
            if (i == 1) optionText = "1 = Level Select";
            else if (i == 2) optionText = "2 = Infinite Survival (An infinite gamemode with new patterns every time you play!)";

            if (i == type) {
                setConsoleColor(0, 255, 255);
                cout << "  > " << optionText << " <\n";
            }
            else {
                setConsoleColor(255, 255, 255);
                cout << "    " << optionText << "\n";
            }
        }


        if (GetAsyncKeyState(VK_UP) & 0x8000) { // Up Arrow Key
            type = (type - 1 + menuOptions - 1) % menuOptions + 1; // Wrap
            Sleep(150);
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Down Arrow Key
            type = (type) % menuOptions + 1; // Wrap
            Sleep(150); // Small delay
        }


        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            setConsoleColor(255, 255, 255);
            system("CLS");
            return type;
        }
        Sleep(30);
    }
}