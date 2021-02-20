#include "GameObjectState.hpp"

#include "GraphicsGameObject.hpp"
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

void GameObjectState::onSet(GraphicsGameObject& object)
{
    object.setMaxAcceleration({});
    object.setMaxVelocity({});
    object.setAcceleration({});
}

void GameObjectState::onUnset(GraphicsGameObject&)
{

}

void GameObjectState::destroy()
{
    mRemoved = true;
}

void GameObjectState::update(GraphicsGameObject& object, const sf::Time& frameTime)
{
    if (!isDestroyed())
    {
        if (mAnimation)
        {
            mAnimation->update(frameTime);

            object.setTextureArea(mAnimation->getCurrentSpriteArea());
        }

        updateSelf(object, frameTime);
    }
}

void GameObjectState::onKeyPressed(GraphicsGameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onKeyReleased(GraphicsGameObject&, const sf::Event::KeyEvent&)
{

}

void GameObjectState::onMouseClick(GraphicsGameObject& object, const sf::Event::MouseButtonEvent&)
{
    object.setBoundsVisible(!object.isBoundsVisible());
}

void GameObjectState::onMouseEnter(GraphicsGameObject&, const sf::Event::MouseMoveEvent&)
{

}

void GameObjectState::onMouseLeave(GraphicsGameObject&, const sf::Event::MouseMoveEvent&)
{

}

void GameObjectState::onMouseOver(GraphicsGameObject&, const sf::Event::MouseMoveEvent&)
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

void GameObjectState::updateSelf(GraphicsGameObject&, const sf::Time&)
{

}
