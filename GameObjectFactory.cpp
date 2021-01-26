#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"
#include "GameResourceContainer.hpp"
#include "GraphicsTextItem.hpp"
#include "MarioStandState.hpp"

GameObjectFactory::GameObjectFactory(GameResourceContainer& gameResourceContainer, GameObjectCreator& gameObjectCreator) :
	mGameResourceContainer{gameResourceContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

GameObject* GameObjectFactory::createMario(GraphicsItem* sceneLayer) const
{
	auto object = create(sceneLayer, TextureIdentifiers::Mario, MarioStandState::getInstance());

	return object;
}

GameObject* GameObjectFactory::createGoomba(GraphicsItem* sceneLayer) const
{
	auto object = create(sceneLayer, TextureIdentifiers::Enemies, MarioStandState::getInstance());

	return object;
}

GameObject* GameObjectFactory::create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier, GameObjectState* state) const
{
	auto object = mGameObjectCreator.create(sceneLayer->addItem<GraphicsSpriteItem>());
	object->setTexture(mGameResourceContainer.getTexture(textureIdentifier));
	object->setState(state);

	return object;
}
