#pragma once

#include "Game.hpp"

// Implementations of this interface should be sinlgerones
class IGameState
{
  protected:
    IGameState(){};

    virtual ~IGameState() = 0;

  public:
    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void handleEvents(Game &game) = 0;

    virtual void update(Game &game) = 0;

    virtual void draw(Game &game) = 0;

    inline void changeState(Game &game, IGameState &state) { game.changeState(state); }
};

IGameState::~IGameState() = default;
