#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <iostream>
#include <atomic>

class Model
{
public:
    Model(int width, int height);
    void update();
    bool isAlive(int x, int y);
    void setCell(int x, int y, bool isAlive);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int countAliveNeighbors(int y, int x);
    void updateSection(std::vector<std::vector<bool>> newGrid);
    void setCancelFlag(bool value);
    bool getCancelFlag();
    void measureExecuteTime(std::vector<std::thread> &threads);

private:
    int width;
    int height;

    std::vector<std::vector<bool>> grid;
    std::atomic<bool> cancelFlag;
};

#endif // MODEL_H
