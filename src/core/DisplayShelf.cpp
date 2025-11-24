#include "DisplayShelf.h"
#include <random>
#include <chrono>
#include <thread>

DisplayShelf::DisplayShelf(int size)
    : size(size), slots(size), slotMutex(size)
{
    generateItems();
}

void DisplayShelf::generateItems() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> valDist(1, 100);
    std::uniform_int_distribution<> specialDist(0, 20);

    for (int i = 0; i < size; i++) {
        slots[i] = Item(valDist(gen), "Item" + std::to_string(i));

        int r = specialDist(gen);
        if (r == 0) {
            slots[i].isGlobalLock = true;
            slots[i].name = "GlobalLockItem";
        }
        else if (r == 1) {
            slots[i].isDoubleScore = true;
            slots[i].name = "DoubleScoreItem";
        }
    }
}

bool DisplayShelf::tryTakeItem(int index, Item& out, const std::string& who) {
    if (globalLockActive && lockOwner != who)
        return false;
    if (index < 0 || index >= size) return false;

    std::lock_guard<std::mutex> lock(slotMutex[index]);

    if (slots[index].name.empty()) return false;

    out = slots[index];
    slots[index] = Item();

    if (isEmpty()) {
        generateItems();
    }

    return true;
}

bool DisplayShelf::tryGlobalLock(const std::string& who) {
    if (globalMutex.try_lock()) {
        globalLockActive = true;
        lockOwner = who;
        return true;
    }
    return false;
}

void DisplayShelf::unlockGlobal() {
    globalLockActive = false;
    lockOwner.clear();
    globalMutex.unlock();
}

void DisplayShelf::startGlobalLockTimer(int seconds)
{
    std::thread([this, seconds]() {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        this->unlockGlobal();
        }).detach();
}

bool DisplayShelf::isEmpty() {
    for (auto& item : slots) {
        if (!item.name.empty())
            return false;
    }
    return true;
}

void DisplayShelf::reset() {
    for (auto& m : slotMutex) {
    }

    globalLockActive = false;
    lockOwner.clear();
    if (globalMutex.try_lock()) {
        globalMutex.unlock();
    }

    generateItems();
}