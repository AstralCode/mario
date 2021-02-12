#pragma once

#include "GameResourceIdentifiers.hpp"

class GameObject;
class GameObjectState;
class GraphicsItem;
class GameSpriteAtlasContainer;
class GameSpriteAtlas;
class GameObjectCreator;
class GameResourceContainer;
class AnimationFactory;

class GameObjectFactory final
{
public:
	GameObjectFactory(GameResourceContainer& gameResourceContainer, GameSpriteAtlasContainer& gameSpriteAtlasContainer, GameObjectCreator& gameObjectCreator, AnimationFactory& animationFactory);

	GameObject* createMario(GraphicsItem* sceneLayer) const;
	GameObject* createGoomba(GraphicsItem* sceneLayer) const;

	GameObject* createCoin(GraphicsItem* sceneLayer) const;

private:
	GameObject* create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const;

	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasContainer& mGameSpriteAtlasContainer;
	GameObjectCreator& mGameObjectCreator;
	AnimationFactory& mAnimationFactory;
};
