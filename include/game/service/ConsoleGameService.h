#pragma once
#include "IGameService.h"

class ConsoleGameService : public IGameService {
public:
    void init() override;
    static void hideCursor();
};