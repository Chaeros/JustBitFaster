#pragma once
#include <chrono>
#include <functional>
#include "Types.h"
#include "InputQueue.h"

class InputManager
{
public:
    InputManager();

    void update(InputQueue<CommandType>& q1,
        InputQueue<CommandType>& q2,
        bool& running);

private:
    struct KeyInfo {
        bool prev = false;
        bool curr = false;
        std::chrono::steady_clock::time_point lastRepeat;
    };

    KeyInfo keyState[256];

    const int repeatRate = 100;

    void processKey(int keyCode, const std::function<void()>& callback);
};
