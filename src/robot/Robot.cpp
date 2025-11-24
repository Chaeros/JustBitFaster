#include "Robot.h"
#include <iostream>
#include <chrono>

Robot::Robot(const std::string& name, DisplayShelf& shelf, InputQueue<CommandType>& queue)
    : name(name), shelf(shelf), input(queue)
{
}

void Robot::start() {
    running = true;
    worker = std::thread(&Robot::run, this);
}

void Robot::stop() {
    running = false;
    if (worker.joinable())
        worker.join();
}

void Robot::run() {
    while (running) {
        if (shelf.isGlobalLocked() && shelf.getLockOwner() != name) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        CommandType cmd;
        if (input.pop(cmd)) {
            switch (cmd) {
            case CommandType::MOVE_UP:
                position = (position - 1 + shelf.getSize()) % shelf.getSize();
                break;

            case CommandType::MOVE_DOWN:
                position = (position + 1) % shelf.getSize();
                break;

            case CommandType::SELECT:
            {
                Item item;
                if (shelf.tryTakeItem(position, item)) {

                    if (item.isGlobalLock) {
                        std::cout << name << " activated GLOBAL LOCK!\n";
                        if (shelf.tryGlobalLock(name)) {
                            shelf.startGlobalLockTimer(3);
                            //std::this_thread::sleep_for(std::chrono::seconds(3));
                            //shelf.unlockGlobal();
                        }
                    }
                    else if (item.isDoubleScore) {
                        doubleScoreMode = true;
                        doubleScoreEnd = std::chrono::steady_clock::now() + std::chrono::seconds(5);
                    }
                    else {
                        int gained = doubleScoreMode ? item.value * 2 : item.value;
                        score += gained;
                    }
                }
            }
            break;

            default:
                break;
            }
        }

        if (doubleScoreMode && std::chrono::steady_clock::now() > doubleScoreEnd) {
            doubleScoreMode = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}