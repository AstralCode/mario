#include "MarioJumpState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"
#include "MarioFallState.hpp"

MarioJumpState::MarioJumpState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset}
{

}

void MarioJumpState::onSet(GameObject& object) noexcept
{
    object.setSpriteArea(mSpriteset.getRegion(MarioSpritesetRegions::Jump).getSpriteArea(0));
    object.setVelocityY(-Constants::World::Mario::MaxVelocityY);
}

void MarioJumpState::update(GameObject& object, const sf::Time&) noexcept
{
    if (object.getVelocity().getX() > 0.0f)
    {
        object.setState<MarioFallState>(mSpriteset);
    }
}

void MarioJumpState::onTileTopCollision(GameObject& object, const Tile&) noexcept
{
    if (std::fabs(object.getVelocity().getX()) > Constants::World::Mario::StopVelocityX)
    {
        object.setState<MarioMoveState>(mSpriteset);
    }
    else
    {
        object.setState<MarioStandState>(mSpriteset);
    }
}

void MarioJumpState::onTileBottomCollision(GameObject& object, const Tile&) noexcept
{
    object.setVelocityY(object.getVelocity().getY() + Constants::World::Mario::MaxVelocityY * 0.2f);
}

void MarioJumpState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
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

bool MarioJumpState::isJumping() const noexcept
{
    return true;
}

bool MarioJumpState::isFalling() const noexcept
{
    return false;
}
