#include "Coin.hpp"

#include "CoinShineState.hpp"
#include "CoinPickupState.hpp"

#include "World.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

Coin::Coin(World& world) noexcept :
	Entity{EntityType::Item, world}
{
	mStates.registerState<CoinShineState>();
	mStates.registerState<CoinPickupState>();

	auto& resources = world.getResources();
	auto& spritesets = world.getSpritesets();

	setTexture(resources.getTexture(TextureId::Items));

	mShineAnimation.setSpriteset(spritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::Coin));
	mShineAnimation.setDuration(sf::seconds(0.25f));
	mShineAnimation.setDelay(sf::seconds(0.25f));
	mShineAnimation.setDirection(Animation::Directions::Alternate);
	mShineAnimation.setRepeating(true);

	mPickupAnimation.setSpriteset(spritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::CoinPickup));
	mPickupAnimation.setDuration(sf::seconds(0.15f));
	mPickupAnimation.setRepeating(true);

	setState<CoinShineState>();
	Entity::centerOrigin(*this);
}

void Coin::playShineAnimation() noexcept
{
	mShineAnimation.play();
	setSpriteArea(mShineAnimation.getCurrentSpriteArea());
}

void Coin::updateShineAnimation(const sf::Time& dt) noexcept
{
	mShineAnimation.update(dt);
	setSpriteArea(mShineAnimation.getCurrentSpriteArea());
}

void Coin::playPickupAnimation() noexcept
{
	mPickupAnimation.play();
	setSpriteArea(mPickupAnimation.getCurrentSpriteArea());
}

void Coin::updatePickupAnimation(const sf::Time& dt) noexcept
{
	mPickupAnimation.update(dt);
	setSpriteArea(mPickupAnimation.getCurrentSpriteArea());

	mPickupAnimationTime += dt;
}

void Coin::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Coin::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void Coin::collision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, collider, side);
}

void Coin::falling() noexcept
{
	mStates.getState().falling(*this);
}

const sf::Time& Coin::getPickupTime() const noexcept
{
	return mPickupAnimationTime;
}
