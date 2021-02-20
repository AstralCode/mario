#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept :
	mTilemap{tilemap},
	mSpritesetContainer{spritesetContainer}
{

}

Tilemap& CollisionHandler::getTilemap() noexcept
{
	return mTilemap;
}

SpritesetContainer& CollisionHandler::getSpritesetContainer() noexcept
{
	return mSpritesetContainer;
}
