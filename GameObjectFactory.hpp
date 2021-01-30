#pragma once

#include "GameResourceIdentifiers.hpp"
#include "EmptyGameObjectState.hpp"

class GameObject;
class GameObjectState;
class GraphicsItem;
class GameSpriteAtlasManager;
class GameSpriteAtlas;
class GameObjectCreator;
class GameResourceContainer;

class GameObjectFactory final
{
public:
	GameObjectFactory(GameResourceContainer& gameResourceContainer, GameSpriteAtlasManager& gameSpriteAtlasManager, GameObjectCreator& gameObjectCreator);

	GameObject* createMario(GraphicsItem* sceneLayer) const;
	GameObject* createGoomba(GraphicsItem* sceneLayer) const;

private:
	GameObject* create(const GameSpriteAtlas& gameSpriteAtlas, GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const;

	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasManager& mGameSpriteAtlasManager;
	GameObjectCreator& mGameObjectCreator;
};
