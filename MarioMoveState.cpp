#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"
#include "MarioJumpState.hpp"

MarioMoveState::MarioMoveState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset},
    mMoveAnimation{spriteset.getRegion(MarioSpritesetRegions::Move)}
{

}

void MarioMoveState::onSet(GameObject& object) noexcept
{
    object.setTextureArea(mMoveAnimation.getCurrentSpriteArea());
    object.setAccelerationX(0.0f);

    if (sf::Keyboard::isKeyPressed(Constants::GameObjects::Mario::Left) ||
        sf::Keyboard::isKeyPressed(Constants::GameObjects::Mario::Right))
    {
        object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
    }

    mMoveAnimation.setDuration(sf::seconds(Constants::GameObjects::Mario::MoveAnimationDuration));
    mMoveAnimation.setRepeating(true);
    mMoveAnimation.play();
}

void MarioMoveState::update(GameObject& object, const sf::Time& fixedFrameTime) noexcept
{
    mMoveAnimation.update(fixedFrameTime);
    object.setTextureArea(mMoveAnimation.getCurrentSpriteArea());

    if (object.getAcceleration().getX() == 0.0f && std::fabs(object.getVelocity().getX()) < 12.0f)
    {
        object.setState(std::make_unique<MarioStandState>(mSpriteset));
    }
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::GameObjects::Mario::Left)
    {
        object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
        object.setDirection(GameObjectDirections::Left);
    }
    else if (keyEvent.code == Constants::GameObjects::Mario::Right)
    {
        object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
        object.setDirection(GameObjectDirections::Right);
    }
    else if (keyEvent.code == sf::Keyboard::W)
    {
        object.setState(std::make_unique<MarioJumpState>(mSpriteset));
    }
}

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::GameObjects::Mario::Left ||
        keyEvent.code == Constants::GameObjects::Mario::Right)
    {
        object.setAccelerationX(0.0f);
    }

    if (keyEvent.code == Constants::GameObjects::Mario::Left)
    {
        if (sf::Keyboard::isKeyPressed(Constants::GameObjects::Mario::Right))
        {
            object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
            object.setDirection(GameObjectDirections::Right);
        }
    }
    else if (keyEvent.code == Constants::GameObjects::Mario::Right)
    {
        if (sf::Keyboard::isKeyPressed(Constants::GameObjects::Mario::Left))
        {
            object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
            object.setDirection(GameObjectDirections::Left);
        }
    }
}
