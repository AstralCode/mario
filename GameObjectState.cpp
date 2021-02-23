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

void GameObjectState::onMouseClick(GameObject&, const sf::Event::MouseButtonEvent&)
{

}

void GameObjectState::onMouseEnter(GameObject& object, const sf::Event::MouseMoveEvent&)
{
    object.setBoundsVisible(true);
}

void GameObjectState::onMouseLeave(GameObject& object, const sf::Event::MouseMoveEvent&)
{
    object.setBoundsVisible(false);
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
