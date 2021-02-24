#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
	mTilemap{tilemap},
	mSpritesetContainer{spritesetContainer}
{

}

void CollisionHandler::setTarget(const GameObjectIdentifiers identifier) noexcept
{
	mTargets.set(identifier);
}

void CollisionHandler::unsetTarget(const GameObjectIdentifiers identifier) noexcept
{
	mTargets.unset(identifier);
}

void CollisionHandler::setTargets(const GameObjectIdentifierFlags& identifiers) noexcept
{
	mTargets.set(identifiers);
}

void CollisionHandler::unsetTargets(const GameObjectIdentifierFlags& identifiers) noexcept
{
	mTargets.unset(identifiers);
}

const GameObjectIdentifierFlags& CollisionHandler::getTargets() const noexcept
{
	return mTargets;
}

Tilemap& CollisionHandler::getTilemap() noexcept
{
	return mTilemap;
}

SpritesetContainer& CollisionHandler::getSpritesetContainer() noexcept
{
	return mSpritesetContainer;
}

bool CollisionHandler::isSetTarget(const GameObjectIdentifiers identifier) const noexcept
{
	return mTargets.isSet(identifier);
}