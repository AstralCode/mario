#include "MarioStandState.hpp"

#include "GameObject.hpp"
#include "MarioMoveState.hpp"
#include "MarioJumpState.hpp"

MarioStandState::MarioStandState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset}
{

}

void MarioStandState::onSet(GameObject& object) noexcept
{
    object.setSpriteArea(mSpriteset.getRegion(MarioSpritesetRegions::Stand).getSpriteArea(0));
    object.setAccelerationX(0.0f);
}

void MarioStandState::update(GameObject&, const sf::Time&) noexcept
{

}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left)
    {
        object.setDirection(GameObjectDirections::Left);
        object.setState<MarioMoveState>(mSpriteset);
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        object.setDirection(GameObjectDirections::Right);
        object.setState<MarioMoveState>(mSpriteset);
    }
    else if (keyEvent.code == Constants::World::Mario::Up)
    {
        object.setState<MarioJumpState>(mSpriteset);
    }
}

bool MarioStandState::isJumping() const noexcept
{
    return false;
}

bool MarioStandState::isFalling() const noexcept
{
    return false;
}
