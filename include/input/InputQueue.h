#pragma once
#include <queue>
#include <mutex>

template <typename T>
class InputQueue {
private:
    std::queue<T> q;
    std::mutex mtx;

public:
    void push(const T& val) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(val);
    }

    bool pop(T& out) {
        std::lock_guard<std::mutex> lock(mtx);
        if (q.empty()) return false;
        out = q.front();
        q.pop();
        return true;
    }
};