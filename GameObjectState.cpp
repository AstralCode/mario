#include "GameObjectState.hpp"

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

bool GameObjectState::isKeyPressed(const sf::Event::KeyEvent& keyEvent, const sf::Keyboard::Key keyCode) const
{
    return keyEvent.code == keyCode;
}
