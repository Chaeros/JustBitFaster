#pragma once

#include <chrono>
#include "DisplayShelf.h"
#include "InputQueue.h"
#include "InputManager.h"
#include "Robot.h"
#include "IGameService.h"

class GameController
{
public:
    GameController(IGameService& service);
    void run();

private:
    void gameLoop();

private:
    static const int GAME_DURATION = 30;

    IGameService& service;
    DisplayShelf shelf;
    InputQueue<CommandType> q1, q2;
    Robot r1, r2;
    InputManager input;

    bool running;
};
