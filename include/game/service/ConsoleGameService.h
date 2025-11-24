#pragma once
#include "IGameService.h"
#include "DisplayShelf.h"
#include "Robot.h"

class ConsoleGameService : public IGameService {
public:
    void init() override;
    void resetGame(DisplayShelf& shelf, Robot& r1, Robot& r2) override;
    static void hideCursor();
    void clear();
};
