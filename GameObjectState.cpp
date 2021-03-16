#include "GameObjectState.hpp"

#include "GameObject.hpp"
#include "Spriteset.hpp"

GameObjectState::GameObjectState(const Spriteset& spriteset) noexcept :
    mSpriteset{spriteset},
    mRemoved{false}
{

}

void GameObjectState::setAnimation(std::unique_ptr<Animation> animation) noexcept
{
    mAnimation = std::move(animation);
    mAnimation->stop();
    mAnimation->play();
}

void GameObjectState::onSet(GameObject& object) noexcept
{
    object.setMaxAcceleration({});
    object.setMaxVelocity({});
    object.setAcceleration({});
    object.setTextureArea(mAnimation->getCurrentSpriteArea());
}

void GameObjectState::onUnset(GameObject&) noexcept
{

}

void GameObjectState::destroy() noexcept
{
    mRemoved = true;
}

void GameObjectState::onTileTopCollision(GameObject&, const TileIndex&) noexcept
{

}

void GameObjectState::onTileBottomCollision(GameObject&, const TileIndex&) noexcept
{

}

void GameObjectState::onTileLeftCollision(GameObject&, const TileIndex&) noexcept
{

}

void GameObjectState::onTileRightCollision(GameObject&, const TileIndex&) noexcept
{

}

void GameObjectState::onObjectCollision(GameObject&) noexcept
{

}

void GameObjectState::update(GameObject& object, const sf::Time& fixedFrameTime) noexcept
{
    if (mAnimation)
    {
        mAnimation->update(fixedFrameTime);
        object.setTextureArea(mAnimation->getCurrentSpriteArea());
    }

    updateSelf(object, fixedFrameTime);
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

const IntArea& GameObjectState::getSpriteArea(const std::string& spritesetRegionidentifier) const noexcept
{
    return mSpriteset.getRegion(spritesetRegionidentifier).getSpriteArea(0);
}

bool GameObjectState::isJumping() const noexcept
{
    return false;
}

bool GameObjectState::isDestroyed() const noexcept
{
    return mRemoved;
}

std::unique_ptr<Animation> GameObjectState::createAnimation(const std::string& spritesetRegionIdentifier) const noexcept
{
    return std::make_unique<Animation>(mSpriteset.getRegion(spritesetRegionIdentifier));
}

void GameObjectState::updateSelf(GameObject&, const sf::Time&) noexcept
{

}
