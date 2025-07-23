#pragma once
#ifndef HELP_H
#define HELP_H

#include <windows.h>
#include <iostream>
#include <conio.h>

// Function to move cursor to specific position in console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to draw filled rectangle
void myRect(int x1, int y1, int x2, int y2, int R, int G, int B) {
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    HPEN pen = CreatePen(PS_SOLID, 1, RGB(R, G, B));
    HBRUSH brush = CreateSolidBrush(RGB(R, G, B));

    SelectObject(device_context, pen);
    SelectObject(device_context, brush);

    Rectangle(device_context, x1, y1, x2, y2);

    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}

// Function to draw ellipse/circle
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B) {
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    HPEN pen = CreatePen(PS_SOLID, 1, RGB(R, G, B));
    HBRUSH brush = CreateSolidBrush(RGB(R, G, B));

    SelectObject(device_context, pen);
    SelectObject(device_context, brush);

    Ellipse(device_context, x1, y1, x2, y2);

    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}

// Function to draw line
void myLine3(int x1, int y1, int x2, int y2, int R, int G, int B) {
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    HPEN pen = CreatePen(PS_SOLID, 3, RGB(R, G, B)); // Thicker line for barriers
    SelectObject(device_context, pen);

    MoveToEx(device_context, x1, y1, NULL);
    LineTo(device_context, x2, y2);

    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
}

// Function to check for cursor key input
bool isCursorKeyPressed(int& whichKey) {
    whichKey = 0;

    if (_kbhit()) {
        int key = _getch();

        if (key == 224) { // Extended key prefix
            key = _getch();
            switch (key) {
            case 75: // Left arrow
                whichKey = 1;
                return true;
            case 77: // Right arrow
                whichKey = 2;
                return true;
            case 72: // Up arrow
                whichKey = 3;
                return true;
            case 80: // Down arrow
                whichKey = 4;
                return true;
            }
        }
        else if (key == 13) { // Enter key
            whichKey = 5;
            return true;
        }
        else if (key == 27) { // Escape key
            whichKey = 6;
            return true;
        }
        else if (key == 32) { // Space key
            whichKey = 7;
            return true;
        }
        // Handle WASD keys for movement
        else if (key == 'a' || key == 'A') {
            whichKey = 1; // Left
            return true;
        }
        else if (key == 'd' || key == 'D') {
            whichKey = 2; // Right
            return true;
        }
        else if (key == 'w' || key == 'W') {
            whichKey = 3; // Up
            return true;
        }
        else if (key == 's' || key == 'S') {
            whichKey = 4; // Down
            return true;
        }
    }

    return false;
}

// Function to hide console cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Function to maximize console window
void maximizeWindow() {
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);
}

// Function to set console window size
void setConsoleSize(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
}

// Initialize console settings
void initConsole() {
    maximizeWindow();
    hideCursor();

    // Set console title
    SetConsoleTitle(L"Snake Game");

    // Set console screen buffer size
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 120, 40 };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Set console window size
    SMALL_RECT windowSize = { 0, 0, 119, 39 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

#endif // HELP_H
