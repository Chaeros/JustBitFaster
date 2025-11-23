#pragma once
#include <string>

struct Item {
    int value = 0;
    std::string name;
    bool isGlobalLock = false;
    bool isDoubleScore = false;

    Item() {}
    Item(int v, const std::string& n) : value(v), name(n) {}
};