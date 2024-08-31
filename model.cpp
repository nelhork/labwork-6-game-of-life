#include "model.h"

Model::Model(int width, int height) : width(width), height(height), grid(height, std::vector<bool>(width, false))
{
    srand(static_cast<unsigned int>(time(0)));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; ++x) {
            grid[y][x] = (rand() % 2) == 0;
        }
    }
    cancelFlag.store(false);
}

bool Model::isAlive(int x, int y) {
    return grid[y][x];
}

void Model::setCell(int x, int y, bool alive) {
    grid[y][x] = alive;
}

int Model::countAliveNeighbors(int y, int x)
{
    int aliveNeighbors = 0;

    // Check neighbors cells Oy
    for (int dy = -1; dy <= 1; dy++) {
        // Check neighbors cells Ox
        for (int dx = -1; dx <= 1; dx++) {
            // The current cell is not a neighbor
            if (dx == 0 && dy == 0) {
                continue;
            }
            int nx = x + dx; // Calculate X-coord
            int ny = y + dy; // Calculate Y-coord

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                aliveNeighbors += grid[ny][nx] ? 1 : 0; // If the neighbor is alive, then increase the counter
            }
        }
    }

    return aliveNeighbors;
}

void Model::setCancelFlag(bool value)
{
    cancelFlag.store(value);
}

bool Model::getCancelFlag()
{
    return cancelFlag.load();
}

void Model::measureExecuteTime(std::vector<std::thread> &threads)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& thread : threads) {
        thread.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << std::fixed<< "Time (parallel): " << duration.count() << " sec" << std::endl;
}

void Model::update() {

    std::vector<std::vector<bool>> newGrid = grid;
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    int sectionHeight = height / numThreads;

    for (int i = 0; i < numThreads; i++) {
        int startY = i * sectionHeight;
        int endY = (i == numThreads - 1) ? height : startY + sectionHeight;

        threads.emplace_back([this, startY, endY, &newGrid]() {
            for (int y = startY; y < endY && !cancelFlag.load(); y++) {
                for (int x = 0; x < width && !cancelFlag.load(); x++) {
                    int aliveNeighbors = countAliveNeighbors(y, x);

                    if (grid[y][x]) {
                        newGrid[y][x] = (aliveNeighbors == 2 || aliveNeighbors == 3);
                    } else {
                        newGrid[y][x] = (aliveNeighbors == 3);
                    }
                }
            }
        });
    }

    measureExecuteTime(threads);

    grid = newGrid;
}
