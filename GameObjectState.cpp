#include "GameObjectState.hpp"

GameObjectState::GameObjectState() :
    mRemoved{false}
{

}

void GameObjectState::onSet(GameObject&)
{

}

void GameObjectState::onUnset(GameObject&)
{

}

void GameObjectState::destroy()
{
    mRemoved = true;
}

void GameObjectState::update(GameObject&, const sf::Time&)
{

}

void GameObjectState::onKeyPressed(GameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onKeyReleased(GameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onMouseClick(GameObject&, const sf::Event::MouseButtonEvent&)
{

}

void GameObjectState::onMouseEnter(GameObject&, const sf::Event::MouseMoveEvent&)
{

}

void GameObjectState::onMouseLeave(GameObject&, const sf::Event::MouseMoveEvent&)
{

}

void GameObjectState::onMouseOver(GameObject&, const sf::Event::MouseMoveEvent&)
{

}

bool GameObjectState::isWreck() const
{
    return true;
}

bool GameObjectState::isDestroyed() const
{
    return mRemoved && isWreck();
}
