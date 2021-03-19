#include "MarioFallState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"

MarioFallState::MarioFallState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset}
{

}

void MarioFallState::onSet(GameObject& object) noexcept
{
    object.setSpriteArea(mSpriteset.getRegion(MarioSpritesetRegions::Jump).getSpriteArea(0));
}

void MarioFallState::update(GameObject&, const sf::Time&) noexcept
{

}

void MarioFallState::onTileTopCollision(GameObject& object, const Tile& tile) noexcept
{
    if (std::fabs(object.getVelocity().getX()) > Constants::World::Mario::MinVelocityX)
    {
        object.setState<MarioMoveState>(mSpriteset);
    }
    else
    {
        object.setState<MarioStandState>(mSpriteset);
    }
}

void MarioFallState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left)
    {
        object.setAccelerationX(Constants::World::Mario::AccelerationX);
        object.setDirection(GameObjectDirections::Left);
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        object.setAccelerationX(Constants::World::Mario::AccelerationX);
        object.setDirection(GameObjectDirections::Right);
    }
}

bool MarioFallState::isFalling() const noexcept
{
    return true;
}

bool MarioFallState::isJumping() const noexcept
{
    return false;
}
