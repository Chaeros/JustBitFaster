#include <windows.h>
#include "GameController.h"
#include "ConsoleGameService.h"
#include "EndGameOutputView.h"
#include "RetryInputView.h"
#include "UI.h"

GameController::GameController(IGameService& service)
    : service(service),
    shelf(10),
    r1("Player1", shelf, q1),
    r2("Player2", shelf, q2)
{
}

void GameController::run()
{
    service.init();

    do {
        service.clear();
        service.resetGame(shelf, r1, r2);
        gameLoop();
        EndGameOutputView::printResult(r1.getScore(), r2.getScore());

#ifdef _WIN32
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
#endif
    } while (RetryInputView::askRetry());
}

void GameController::gameLoop()
{
    r1.start();
    r2.start();

    auto gameStart = std::chrono::steady_clock::now();
    auto lastRender = std::chrono::steady_clock::now();

    running = true;

    while (running)
    {
        input.update(q1, q2, running);

        auto now = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - gameStart).count();
        int timeLeft = GAME_DURATION - elapsed;

        if (now - lastRender > std::chrono::milliseconds(120))
        {
            renderUI(
                shelf,
                r1.getPosition(),
                r2.getPosition(),
                r1.getScore(),
                r2.getScore(),
                timeLeft
            );
            lastRender = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if (timeLeft < 0)
            running = false;
    }
    r1.stop();
    r2.stop();
}