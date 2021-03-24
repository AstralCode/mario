#include "Item.hpp"

#include "ItemActiveState.hpp"

Item::Item(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept :
	mActiveAnimation{sprites}
{
	mActiveAnimation.setDuration(sf::seconds(Constants::World::Items::ShineAnimationDuration));
	mActiveAnimation.setDirection(Animation::Directions::Alternate);
	mActiveAnimation.setDelay(sf::seconds(Constants::World::Items::ShineAnimationDelay));
	mActiveAnimation.setRepeating(true);

	mStates.registerState<ItemActiveState>(Item::States::Active);

	setTexture(texture);
	setState(Item::States::Active);
}

void Item::setState(const Item::States identifier)
{
	mStates.setCurrentState(*this, identifier);
}

void Item::setActiveAnimation() noexcept
{
	mActiveAnimation.play();

	setSpriteArea(mActiveAnimation.getCurrentSpriteArea());
}

void Item::updateActiveAnimation(const sf::Time& dt) noexcept
{
	mActiveAnimation.update(dt);

	setSpriteArea(mActiveAnimation.getCurrentSpriteArea());
}

void Item::update(const sf::Time& dt) noexcept
{
	mStates.getCurrentState().update(*this, dt);
}

void Item::tileCollision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getCurrentState().tileCollision(*this, tile, side);
}

void Item::entityCollision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getCurrentState().entityCollision(*this, collider, side);
}

void Item::falling() noexcept
{
	mStates.getCurrentState().falling(*this);
}

bool Item::isJumping() const noexcept
{
	return mStates.getCurrentState().isJumping();
}

bool Item::isFalling() const noexcept
{
	return mStates.getCurrentState().isFalling();
}
