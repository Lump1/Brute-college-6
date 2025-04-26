#pragma once
#include "Point.h"
#include <vector>
#include <windows.h>
#include <cstring>

class Brute
{
private:
    std::vector<Point> pointsBeforeInput;
    std::vector<Point> pointsAfterInput;

    void executePointClick(int x, int y);
    void executePointsArray(const std::vector<Point>& points);

public:
    Brute();
    ~Brute();

    void addPoint(bool beforeInput, int x, int y);
    void generate(char* pass, int pos, int length, const char* lexicon);
    void bruteForce(int minLength, int maxLength, const char* lexicon);
    void bruteForce(const char* pathToPassdata);
};
