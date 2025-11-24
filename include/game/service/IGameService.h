#pragma once

class DisplayShelf;
class Robot;

class IGameService {
public:
    virtual void init() = 0;
    virtual void resetGame(DisplayShelf& shelf, Robot& r1, Robot& r2) = 0;
    virtual void clear() = 0;
    virtual ~IGameService() = default;
};