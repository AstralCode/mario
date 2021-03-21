#include "MarioStandState.hpp"

void MarioStandState::onSet(Mario& entity) noexcept
{
    entity.setAccelerationX(0.0f);
    entity.setStandSprite();
}

void MarioStandState::update(Mario&, const sf::Time&) noexcept
{

}

void MarioStandState::tileCollision(Mario&, const Tile&, const Tile::Sides) noexcept
{

}

void MarioStandState::entityCollision(Mario&, Entity&) noexcept
{

}

void MarioStandState::falling(Mario&) noexcept
{

}

void MarioStandState::onKeyPressed(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == Constants::World::Mario::Left)
    {
        entity.setDirection(Entity::Directions::Left);
        entity.setState(Mario::States::Move);
    }
    else if (keyEvent.code == Constants::World::Mario::Right)
    {
        entity.setDirection(Entity::Directions::Right);
        entity.setState(Mario::States::Move);
    }
    else if (keyEvent.code == Constants::World::Mario::Up)
    {
        entity.setState(Mario::States::Jump);
    }
}

void MarioStandState::onKeyReleased(Mario&, const sf::Event::KeyEvent&) noexcept
{

}

bool MarioStandState::isJumping() const noexcept
{
    return false;
}

bool MarioStandState::isFalling() const noexcept
{
    return false;
}
