#include "GameSpriteAtlasManager.hpp"

GameSpriteAtlas& GameSpriteAtlasManager::createAtlas(const std::string& identifier)
{
	auto atlas = std::make_unique<GameSpriteAtlas>();
	auto atlasPointer = atlas.get();

	mSpriteAtlases.emplace(identifier, std::move(atlas));

	return *atlasPointer;
}

GameSpriteAtlas& GameSpriteAtlasManager::getAtlas(const std::string& identifier) const
{
	return *mSpriteAtlases.at(identifier);
}
