#include "GameObjectState.hpp"

#include "GameObject.hpp"

GameObjectState::GameObjectState() :
    mDestroyed{false}
{

}

void GameObjectState::onSet(GameObject&)
{

}

void GameObjectState::onUnset(GameObject&)
{

}

void GameObjectState::setAnimation(std::unique_ptr<Animation> animation)
{
    mAnimation = std::move(animation);
}

void GameObjectState::destroy()
{
    mDestroyed = true;
}

void GameObjectState::update(GameObject& object, const sf::Time& frameTime)
{
    if (mAnimation)
    {
        mAnimation->update(frameTime);

        object.setTextureArea(mAnimation->getCurrentSprite());
    }
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
    return mDestroyed && isWreck();
}
