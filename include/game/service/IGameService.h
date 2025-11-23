#pragma once

class IGameService {
public:
    virtual void init() = 0;
    virtual ~IGameService() = default;
};