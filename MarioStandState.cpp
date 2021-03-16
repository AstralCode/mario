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
    object.setTextureArea(mSpriteset.getRegion(MarioSpritesetRegions::Stand).getSpriteArea(0));
    object.setAcceleration({});
    object.setVelocity({});
}

void MarioStandState::update(GameObject&, const sf::Time&) noexcept
{

}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.setDirection(GameObject::Directions::Left);
        object.setState(std::make_unique<MarioMoveState>(mSpriteset));
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.setDirection(GameObject::Directions::Right);
        object.setState(std::make_unique<MarioMoveState>(mSpriteset));
    }
    else if (keyEvent.code == sf::Keyboard::W)
    {
        object.setState(std::make_unique<MarioJumpState>(mSpriteset));
    }
}
