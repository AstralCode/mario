#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler(TilemapView& tilemapView) noexcept :
	mTilemapView{tilemapView}
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

TilemapView& CollisionHandler::getTilemapView() noexcept
{
	return mTilemapView;
}

bool CollisionHandler::isSetTarget(const GameObjectIdentifiers identifier) const noexcept
{
	return mTargets.isSet(identifier);
}
