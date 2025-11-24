#pragma once

#include <vector>
#include <mutex>
#include <atomic>
#include "Item.h"

class DisplayShelf {
public:
    DisplayShelf(int size);

    void generateItems();
    bool tryTakeItem(int index, Item& out);

    int getSize() const { return size; }
    const Item& peek(int index) const { return slots[index]; }

    bool tryGlobalLock(const std::string& who);
    void unlockGlobal();
    bool isGlobalLocked() const { return globalLockActive; }
    void startGlobalLockTimer(int seconds);
    const std::string& getLockOwner() const { return lockOwner; }

private:
    int size;
    std::vector<Item> slots;
    std::vector<std::mutex> slotMutex;

    std::mutex globalMutex;
    std::atomic<bool> globalLockActive = false;
    std::string lockOwner;
};