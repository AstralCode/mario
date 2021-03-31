#include "Goomba.hpp"

#include "GoombaMoveState.hpp"
#include "GoombaFallState.hpp"
#include "GoombaLoseState.hpp"

#include "World.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

Goomba::Goomba(World& world) noexcept :
	Entity{EntityType::Enemy, world}
{
	mStates.registerState<GoombaMoveState>();
	mStates.registerState<GoombaFallState>();
	mStates.registerState<GoombaLoseState>();

	auto& resources = getWorld().getResources();
	auto& spritesets = getWorld().getSpritesets();

	setTexture(resources.getTexture(TextureId::Enemies));
	setComponent(Entity::ComponentType::Mass);
	setComponent(Entity::ComponentType::Movement);

	mMoveAnimation.setSpriteset(spritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegionType::Move));
	mMoveAnimation.setDuration(sf::seconds(0.25f));
	mMoveAnimation.setRepeating(true);

	mLoseAnimation.setSpriteset(spritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegionType::Lose));

	setState<GoombaMoveState>();
}

void Goomba::playMoveAnimation() noexcept
{
	mMoveAnimation.play();
	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Goomba::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mMoveAnimation.update(dt);
	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Goomba::playLoseAnimation() noexcept
{
	mLoseAnimation.play();
	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());

	move(0.0f, getWorld().getTilemapView().getTileHeight() - getArea().getHeight());
}

void Goomba::updateLoseAnimation(const sf::Time& dt) noexcept
{
	mLoseAnimation.update(dt);
	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());

	mLoseTime += dt;
}

void Goomba::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Goomba::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void Goomba::collision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, collider, side);
}

void Goomba::falling() noexcept
{
	mStates.getState().falling(*this);
}

const sf::Time& Goomba::getLoseTime() const noexcept
{
	return mLoseTime;
}
