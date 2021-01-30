#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"
#include "GameResourceContainer.hpp"
#include "GameSpriteAtlasManager.hpp"
#include "GraphicsTextItem.hpp"
#include "MarioStandState.hpp"
#include "EnemyMoveState.hpp"

GameObjectFactory::GameObjectFactory(GameResourceContainer& gameResourceContainer, GameSpriteAtlasManager& gameSpriteAtlasManager, GameObjectCreator& gameObjectCreator) :
	mGameResourceContainer{gameResourceContainer},
	mGameSpriteAtlasManager{gameSpriteAtlasManager},
	mGameObjectCreator{gameObjectCreator}
{

}

GameObject* GameObjectFactory::createMario(GraphicsItem* sceneLayer) const
{
	auto object = create(mGameSpriteAtlasManager.getAtlas("mario"), sceneLayer, TextureIdentifiers::Mario);
	object->setMaxAcceleration({32.0f * 28.0f, 0.0f});
	object->setMaxVelocity({32.0f * 28.0f, 0.0f});
	object->setState(MarioStandState::getInstance());

	return object;
}

GameObject* GameObjectFactory::createGoomba(GraphicsItem* sceneLayer) const
{
	auto object = create(mGameSpriteAtlasManager.getAtlas("enemy"), sceneLayer, TextureIdentifiers::Enemies);
	object->setMaxAcceleration({32.0f * 14.0f, 0.0f});
    object->setMaxVelocity({32.0f * 14.0f, 0.0f});
	object->setState(EnemyMoveState::getInstance());

	return object;
}

GameObject* GameObjectFactory::create(const GameSpriteAtlas& gameSpriteAtlas, GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const
{
	auto object = mGameObjectCreator.create(gameSpriteAtlas, sceneLayer->addItem<GraphicsSpriteItem>());
	object->setTexture(mGameResourceContainer.getTexture(textureIdentifier));

	return object;
}
