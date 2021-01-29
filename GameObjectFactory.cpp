#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"
#include "GameResourceContainer.hpp"
#include "GraphicsTextItem.hpp"
#include "MarioStandState.hpp"
#include "EnemyMoveState.hpp"

GameObjectFactory::GameObjectFactory(GameResourceContainer& gameResourceContainer, GameObjectCreator& gameObjectCreator) :
	mGameResourceContainer{gameResourceContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

GameObject* GameObjectFactory::createMario(GraphicsItem* sceneLayer) const
{
	auto object = create(sceneLayer, TextureIdentifiers::Mario);
	object->setMaxAcceleration({32.0f * 28.0f, 0.0f});
	object->setMaxVelocity({32.0f * 28.0f, 0.0f});
	object->setState(MarioStandState::getInstance());

	return object;
}

GameObject* GameObjectFactory::createGoomba(GraphicsItem* sceneLayer) const
{
	auto object = create(sceneLayer, TextureIdentifiers::Enemies);
	object->setMaxAcceleration({32.0f * 14.0f, 0.0f});
    object->setMaxVelocity({32.0f * 14.0f, 0.0f});
	object->setState(EnemyMoveState::getInstance());

	return object;
}

GameObject* GameObjectFactory::create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const
{
	auto object = mGameObjectCreator.create(sceneLayer->addItem<GraphicsSpriteItem>());
	object->setTexture(mGameResourceContainer.getTexture(textureIdentifier));

	return object;
}
