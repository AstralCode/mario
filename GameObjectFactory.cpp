#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "Tilemap.hpp"
#include "ResourceContainer.hpp"
#include "GameObjectCreator.hpp"
#include "MarioStandState.hpp"

GameObjectFactory::GameObjectFactory(Tilemap& tilemap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept :
	mTilemap{tilemap},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

GameObject* GameObjectFactory::createMario(const sf::Vector2u& tileIndex) noexcept
{
	auto state = createObjectState<MarioStandState>(SpritesetIdentifiers::Mario);

	auto object = createObject(TextureIdentifiers::Mario, tileIndex);
	object->setMaxAcceleration({32.0f * 22.0f, 0.0f});
	object->setMaxVelocity({32.0f * 22.0f, 0.0f});
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createGoomba(const sf::Vector2u& tileIndex) noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Enemy, SpritesetRegionIdentifiers::Goomba::Move);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Normal);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Enemy);
	state->setAnimation(std::move(animation));

	auto object = createObject(TextureIdentifiers::Enemies, tileIndex);
	object->setState(std::move(state));
	object->setMaxAcceleration({32.0f * 8.0f, 0.0f});
    object->setMaxVelocity({32.0f * 8.0f, 0.0f});
	object->setAcceleration(object->getMaxAcceleration());

	return object;
}

GameObject* GameObjectFactory::createCoin(const sf::Vector2u& tileIndex) noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::Coin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Items);
	state->setAnimation(std::move(animation));

	auto object = createObject(TextureIdentifiers::Scenery, tileIndex);
	object->setState(std::move(state));

	mTilemap.setTileIdentifier(229u, tileIndex);

	return object;
}

GameObject* GameObjectFactory::createScoreCoin(const sf::Vector2u& tileIndex) noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::ScoreCoin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Items);
	state->setAnimation(std::move(animation));

	auto object = createObject(TextureIdentifiers::Scenery, tileIndex);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createQuestionMarkBox(const sf::Vector2u& tileIndex) noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Blocks, SpritesetRegionIdentifiers::Blocks::QuestionMarkBox);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Blocks);
	state->setAnimation(std::move(animation));

	auto object = createObject(TextureIdentifiers::Scenery, tileIndex);
	object->setState(std::move(state));

	mTilemap.setTileIdentifier(55u, tileIndex);

	return object;
}

std::unique_ptr<Animation> GameObjectFactory::createAnimation(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept
{
	return std::make_unique<Animation>(mSpritesetContainer.getSpriteset(spritesetIdetntifier).getRegion(spritesetRegionIdentifier));
}

GameObject* GameObjectFactory::createObject(const TextureIdentifiers textureIdentifier, const sf::Vector2u& tileIndex) const noexcept
{
	auto object = mGameObjectCreator.create();
	object->setTexture(mResourceContainer.getTexture(textureIdentifier));
	object->setPosition(mTilemap.getTileCenterPosition(tileIndex));

	return object;
}
