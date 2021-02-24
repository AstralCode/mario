#include "GameObjectState.hpp"

#include "GameObject.hpp"
#include "Spriteset.hpp"

GameObjectState::GameObjectState(const Spriteset& spriteset) :
    mSpriteset{spriteset},
    mRemoved{false}
{

}

void GameObjectState::setAnimation(std::unique_ptr<Animation> animation)
{
    mAnimation = std::move(animation);
    mAnimation->stop();
    mAnimation->play();
}

void GameObjectState::onSet(GameObject& object)
{
    object.setMaxAcceleration({});
    object.setMaxVelocity({});
    object.setAcceleration({});
    object.setTextureArea(mAnimation->getCurrentSpriteArea());
}

void GameObjectState::onUnset(GameObject&)
{

}

void GameObjectState::destroy()
{
    mRemoved = true;
}

void GameObjectState::onCollision(GameObject&)
{

}

void GameObjectState::update(GameObject& object, const sf::Time& frameTime)
{
    if (mAnimation)
    {
        mAnimation->update(frameTime);

        object.setTextureArea(mAnimation->getCurrentSpriteArea());
    }

    updateSelf(object, frameTime);
}

void GameObjectState::onKeyPressed(GameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onKeyReleased(GameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onMouseClick(GameObject& object, const sf::Event::MouseButtonEvent& event)
{
    if (event.button == sf::Mouse::Button::Left)
    {
        object.setBoundsColor(sf::Color::Red);
    }
    else if (event.button == sf::Mouse::Button::Right)
    {
        object.setBoundsColor(sf::Color::Yellow);
    }

    object.setBoundsVisible(!object.isBoundsVisible());
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

const SpriteArea& GameObjectState::getSpriteArea(const std::string& spritesetRegionidentifier) const
{
    return mSpriteset.getRegion(spritesetRegionidentifier).getSpriteArea(0);
}

bool GameObjectState::isDestroyed() const
{
    return mRemoved;
}

std::unique_ptr<Animation> GameObjectState::createAnimation(const std::string& spritesetRegionIdentifier) const
{
    return std::make_unique<Animation>(mSpriteset.getRegion(spritesetRegionIdentifier));
}

void GameObjectState::updateSelf(GameObject&, const sf::Time&)
{

}
