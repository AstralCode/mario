#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"
#include "MarioJumpState.hpp"
#include "MarioFallState.hpp"

MarioMoveState::MarioMoveState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset},
    mMoveAnimation{spriteset.getRegion(MarioSpritesetRegions::Move)}
{

}

void MarioMoveState::onSet(GameObject& object) noexcept
{
    object.setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
    object.setAccelerationX(0.0f);

    if (sf::Keyboard::isKeyPressed(Constants::World::Mario::Left) ||
        sf::Keyboard::isKeyPressed(Constants::World::Mario::Right))
    {
        object.setAccelerationX(Constants::World::Mario::AccelerationX);
    }

    mMoveAnimation.setDuration(sf::seconds(Constants::World::Mario::MoveAnimationDuration));
    mMoveAnimation.setRepeating(true);
    mMoveAnimation.play();
}

void MarioMoveState::update(GameObject& object, const sf::Time& dt) noexcept
{
    mMoveAnimation.update(dt);

    object.setSpriteArea(mMoveAnimation.getCurrentSpriteArea());

    if (object.getAcceleration().getX() > 0.0f)
    {
        if (object.getVelocity().getX() > Constants::World::Mario::StopVelocityX &&
            object.hasDirection(GameObjectDirections::Left))
        {
            object.setSpriteArea(mSpriteset.getRegion(MarioSpritesetRegions::Slide).getSpriteArea(0));
        }
        else if (object.getVelocity().getX() < Constants::World::Mario::StopVelocityX &&
                 object.hasDirection(GameObjectDirections::Right))
        {
            object.setSpriteArea(mSpriteset.getRegion(MarioSpritesetRegions::Slide).getSpriteArea(0));
        }
    }
    else if (std::fabs(object.getVelocity().getX()) < Constants::World::Mario::StopVelocityX)
    {
        object.setState<MarioStandState>(mSpriteset);
    }
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
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
    else if (keyEvent.code == Constants::World::Mario::Up)
    {
        object.setState<MarioJumpState>(mSpriteset);
    }
}

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left ||
        keyEvent.code == Constants::World::Mario::Right)
    {
        object.setAccelerationX(0.0f);
    }

    if (keyEvent.code == Constants::World::Mario::Left)
    {
        if (sf::Keyboard::isKeyPressed(Constants::World::Mario::Right))
        {
            object.setAccelerationX(Constants::World::Mario::AccelerationX);
            object.setDirection(GameObjectDirections::Right);
        }
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        if (sf::Keyboard::isKeyPressed(Constants::World::Mario::Left))
        {
            object.setAccelerationX(Constants::World::Mario::AccelerationX);
            object.setDirection(GameObjectDirections::Left);
        }
    }
}

void MarioMoveState::onFalling(GameObject& object) noexcept
{
    object.setState<MarioFallState>(mSpriteset);
}

bool MarioMoveState::isJumping() const noexcept
{
    return false;
}

bool MarioMoveState::isFalling() const noexcept
{
    return false;
}
