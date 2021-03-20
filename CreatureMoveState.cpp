#include "CreatureMoveState.hpp"

#include "CreatureFallState.hpp"

void CreatureMoveState::onSet(Creature& entity) noexcept
{
    auto& animation = entity.getMoveAnimation();

    entity.setSpriteArea(animation.getCurrentSpriteArea());
    entity.setAccelerationX(Constants::World::Creature::AccelerationX);
    entity.setAccelerationY(0.0f);

    animation.setDuration(sf::seconds(Constants::World::Creature::MoveAnimationDuration));
    animation.setRepeating(true);
    animation.play();
}

void CreatureMoveState::update(Creature& entity, const sf::Time& dt) noexcept
{
    auto& animation = entity.getMoveAnimation();
    animation.update(dt);

    entity.setSpriteArea(animation.getCurrentSpriteArea());
}

void CreatureMoveState::tileCollision(Creature& entity, const Tile& tile, const Tile::Sides side) noexcept
{
    if (side == Tile::Sides::Left || side == Tile::Sides::Right)
    {
        if (entity.hasDirection(Entity::Direction::Right))
        {
            entity.setDirection(Entity::Direction::Left);
        }
        else
        {
            entity.setDirection(Entity::Direction::Right);
        }

        entity.setVelocityX(-entity.getVelocity().getX());
    }
}

void CreatureMoveState::entityCollision(Creature& entity, Creature& collider) noexcept
{
    if (entity.hasDirection(Entity::Direction::Right))
    {
        entity.setDirection(Entity::Direction::Left);
        collider.setDirection(Entity::Direction::Right);
    }
    else
    {
        entity.setDirection(Entity::Direction::Right);
        collider.setDirection(Entity::Direction::Left);
    }

    entity.setVelocityX(-entity.getVelocity().getX());
    collider.setVelocityX(-collider.getVelocity().getX());
}

void CreatureMoveState::falling() noexcept
{
    // object.setState<CreatureFallState>(mMoveAnimation.getSpritesetRegion());
}

bool CreatureMoveState::isJumping() const noexcept
{
    return false;
}

bool CreatureMoveState::isFalling() const noexcept
{
    return false;
}
