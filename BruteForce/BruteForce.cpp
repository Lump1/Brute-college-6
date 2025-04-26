#include "Brute.h"
#include "Globals.h"
#include <windows.h>
#include <thread>


void listenForKeys() {
    while (true) {
        if (GetAsyncKeyState(VK_F1) & 0x8000) {
            start = true;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            stop = true;
            break;
        }
        Sleep(100);
    }
}

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    std::thread keyListener(listenForKeys);

    Brute brute;
    brute.addPoint(true, 1181, 667);

    brute.addPoint(false, 1180, 880);
    brute.addPoint(false, 1400, 765);


    while (!stop) {
        if (start) {
            brute.bruteForce(1, 4, "tes");
            start = false;
        }
        Sleep(100);
    }

    keyListener.join();
    return 0;
}