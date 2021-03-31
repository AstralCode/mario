#include "Coin.hpp"

#include "CoinActiveState.hpp"
#include "CoinPickupState.hpp"

#include "World.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

Coin::Coin(World& world) noexcept :
	Entity{EntityType::Item, world}
{
	mStates.registerState<CoinActiveState>();
	mStates.registerState<CoinPickupState>();

	auto& resources = world.getResources();
	auto& spritesets = world.getSpritesets();

	setTexture(resources.getTexture(TextureId::Items));

	mActiveAnimation.setSpriteset(spritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::Coin));
	mActiveAnimation.setDuration(sf::seconds(0.25f));
	mActiveAnimation.setDelay(sf::seconds(0.25f));
	mActiveAnimation.setDirection(Animation::Directions::Alternate);
	mActiveAnimation.setRepeating(true);

	mPickupAnimation.setSpriteset(spritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::CoinPickup));
	mPickupAnimation.setDuration(sf::seconds(0.15f));
	mPickupAnimation.setRepeating(true);

	setState<CoinActiveState>();
	Entity::centerOrigin(*this);
}

void Coin::playActiveAnimation() noexcept
{
	mActiveAnimation.play();
	setSpriteArea(mActiveAnimation.getCurrentSpriteArea());
}

void Coin::updateActiveAnimation(const sf::Time& dt) noexcept
{
	mActiveAnimation.update(dt);
	setSpriteArea(mActiveAnimation.getCurrentSpriteArea());
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
