#include <windows.h>
#include <thread>
#include <atomic>

std::atomic<bool> stop(false);

void listenForStop() {
    while (!stop) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { 
            stop = true;
        }
        Sleep(100); 
    }
}
