#include "TestGameState.hpp"

void TestGameState::pause()
{

}

void TestGameState::resume()
{

}

void TestGameState::handleEvents(Game &game)
{

}

void TestGameState::update(Game &game)
{

}

void TestGameState::draw(Game &game)
{

}

TestGameState::~TestGameState()
{

}

TestGameState &TestGameState::Instance()
{
    static TestGameState instance;
    return instance;
}
