#include "Brute.h"
#include "Globals.h"
#include <windows.h>
#include <thread>
#include <cstring>


Brute::Brute() {}

Brute::~Brute() {}

void Brute::executePointClick(int x, int y) {
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void Brute::executePointsArray(const std::vector<Point>& points) {
    for (const auto& point : points) {
        executePointClick(point.X, point.Y);
    }
    Sleep(100);
}

void Brute::addPoint(bool beforeInput, int x, int y) {
    Point p;
    p.X = x;
    p.Y = y;

    if (beforeInput) {
        pointsBeforeInput.push_back(p);
    }
    else {
        pointsAfterInput.push_back(p);
    }
}

void Brute::generate(char* pass, int pos, int length, const char* lexicon) {
    if (stop) return;

    if (pos == length) {
        pass[pos] = '\0';

        for (int i = 0; i < length; i++) {
            SHORT vk = VkKeyScan(pass[i]);
            if (vk != -1) {
                keybd_event((BYTE)vk, 0, 0, 0);
                keybd_event((BYTE)vk, 0, KEYEVENTF_KEYUP, 0);
            }
        }

        executePointsArray(pointsAfterInput);
        return;
    }

    for (int i = 0; i < strlen(lexicon); i++) {
        pass[pos] = lexicon[i];
        generate(pass, pos + 1, length, lexicon);
    }
}

void Brute::bruteForce(int minLength, int maxLength, const char* lexicon) {
    executePointsArray(pointsBeforeInput);

    for (int len = minLength; len <= maxLength; len++) {
        if (stop) return;

        char* pass = new char[len + 1];
        generate(pass, 0, len, lexicon);
        delete[] pass;
    }
}
