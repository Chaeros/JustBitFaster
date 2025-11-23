#include "InputManager.h"
#include <windows.h>

InputManager::InputManager()
{
}

void InputManager::processKey(int keyCode, const std::function<void()>& callback)
{
    KeyInfo& k = keyState[keyCode];

    k.curr = (GetAsyncKeyState(keyCode) & 0x8000) != 0;
    auto now = std::chrono::steady_clock::now();

    if (k.curr && !k.prev) {
        callback();
        k.lastRepeat = now;
    }

    else if (k.curr && k.prev) {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - k.lastRepeat).count();
        if (ms >= repeatRate) {
            callback();
            k.lastRepeat = now;
        }
    }

    k.prev = k.curr;
}

void InputManager::update(InputQueue<CommandType>& q1,
    InputQueue<CommandType>& q2,
    bool& running)
{
    // Player1
    processKey('W', [&]() { q1.push(CommandType::MOVE_UP); });
    processKey('S', [&]() { q1.push(CommandType::MOVE_DOWN); });
    processKey('D', [&]() { q1.push(CommandType::SELECT); });

    // Player2
    processKey('I', [&]() { q2.push(CommandType::MOVE_UP); });
    processKey('K', [&]() { q2.push(CommandType::MOVE_DOWN); });
    processKey('L', [&]() { q2.push(CommandType::SELECT); });
}
