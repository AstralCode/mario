#include "GameObjectState.hpp"

#include "GameObject.hpp"

void GameObjectState::destroy() noexcept
{
    mRemoved = true;
}

void GameObjectState::onTileTopCollision(GameObject&, const Tile&) noexcept
{

}

void GameObjectState::onTileBottomCollision(GameObject&, const Tile&) noexcept
{

}

void GameObjectState::onTileLeftCollision(GameObject&, const Tile&) noexcept
{

}

void GameObjectState::onTileRightCollision(GameObject&, const Tile&) noexcept
{

}

void GameObjectState::onObjectCollision(GameObject&, GameObject&) noexcept
{

}

void GameObjectState::onFalling(GameObject&) noexcept
{

}

void GameObjectState::onKeyPressed(GameObject&, const sf::Event::KeyEvent&) noexcept
{

}

void GameObjectState::onKeyReleased(GameObject&, const sf::Event::KeyEvent&) noexcept
{

}

void GameObjectState::onMouseClick(GameObject& object, const sf::Event::MouseButtonEvent& event) noexcept
{
    if (event.button == sf::Mouse::Button::Left)
    {
        object.setAreaBoundsColor(sf::Color::Red);
    }
    else if (event.button == sf::Mouse::Button::Right)
    {
        object.setAreaBoundsColor(sf::Color::Yellow);
    }

    object.setAreaBoundsVisible(!object.isAreaBoundsVisible());
}

void GameObjectState::onMouseEnter(GameObject&, const sf::Event::MouseMoveEvent&) noexcept
{

}

void GameObjectState::onMouseLeave(GameObject&, const sf::Event::MouseMoveEvent&) noexcept
{

}

void GameObjectState::onMouseOver(GameObject&, const sf::Event::MouseMoveEvent&) noexcept
{

}

bool GameObjectState::isDestroyed() const noexcept
{
    return mRemoved;
}
