#include "MarioJumpState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"

MarioJumpState::MarioJumpState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept :
    mSpriteset{spriteset}
{

}

void MarioJumpState::onSet(GameObject& object) noexcept
{
    object.setTextureArea(mSpriteset.getRegion(MarioSpritesetRegions::Jump).getSpriteArea(0));
    object.setVelocityY(-Constants::GameObjects::Mario::MaxVelocityY);
}

void MarioJumpState::update(GameObject&, const sf::Time&) noexcept
{

}

void MarioJumpState::onTileTopCollision(GameObject& object, const Tile&) noexcept
{
    object.setState(std::make_unique<MarioStandState>(mSpriteset));
}

void MarioJumpState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::W)
    {
        object.setAccelerationY(0.0f);
    }
}

void MarioJumpState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
        object.setDirection(GameObjectDirections::Left);
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.setAccelerationX(Constants::GameObjects::Mario::AccelerationX);
        object.setDirection(GameObjectDirections::Right);
    }
}

bool MarioJumpState::isJumping() const noexcept
{
    return true;
}
