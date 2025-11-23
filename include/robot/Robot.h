#pragma once

#include <thread>
#include <atomic>
#include "InputQueue.h"
#include "DisplayShelf.h"
#include "Types.h"

class Robot {
public:
    Robot(const std::string& name, DisplayShelf& shelf, InputQueue<CommandType>& queue);

    void start();
    void stop();

    int getScore() const { return score; }
    int getPosition() const { return position; }

private:
    void run();

    std::string name;
    DisplayShelf& shelf;
    InputQueue<CommandType>& input;

    int position = 0;
    int score = 0;

    bool doubleScoreMode = false;
    std::chrono::steady_clock::time_point doubleScoreEnd;

    std::atomic<bool> running = false;
    std::thread worker;
};