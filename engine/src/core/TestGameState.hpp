#pragma once

#include "IGameState.hpp"

class TestGameState : private IGameState
{
public:
    static TestGameState &Instance();

    TestGameState(TestGameState const &gameState) = delete;

    void operator=(TestGameState const &gameState) = delete;

    void pause() override;

    void resume() override;

    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void draw(Game &game) override;

protected:
    ~TestGameState() override;

private:
    TestGameState()
    { }
};
