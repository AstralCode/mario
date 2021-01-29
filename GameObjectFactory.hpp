#pragma once

#include "GameResourceIdentifiers.hpp"
#include "EmptyGameObjectState.hpp"

class GameObject;
class GameObjectState;
class GraphicsItem;
class GameObjectCreator;
class GameResourceContainer;

class GameObjectFactory final
{
public:
	GameObjectFactory(GameResourceContainer& gameResourceContainer, GameObjectCreator& gameObjectCreator);

	GameObject* createMario(GraphicsItem* sceneLayer) const;
	GameObject* createGoomba(GraphicsItem* sceneLayer) const;

private:
	GameObject* create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const;

	GameResourceContainer& mGameResourceContainer;
	GameObjectCreator& mGameObjectCreator;
};
