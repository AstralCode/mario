#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "ResourceContainer.hpp"
#include "GameObjectCreator.hpp"
#include "MarioStandState.hpp"

GameObjectFactory::GameObjectFactory(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept :
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

GameObject* GameObjectFactory::createMario() noexcept
{
	auto state = createObjectState<MarioStandState>(SpritesetIdentifiers::Mario);

	auto object = createObject(GameObjectIdentifiers::Mario, TextureIdentifiers::Mario);
	object->setMaxAcceleration({32.0f * 24.0f, 0.0f});
	object->setMaxVelocity({32.0f * 20.0f, 0.0f});
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createGoomba() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Enemy, SpritesetRegionIdentifiers::Goomba::Move);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Normal);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Enemy);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::Goomba, TextureIdentifiers::Enemies);
	object->setState(std::move(state));
	object->setMaxAcceleration({32.0f * 8.0f, 0.0f});
    object->setMaxVelocity({32.0f * 8.0f, 0.0f});
	object->setAcceleration(object->getMaxAcceleration());

	return object;
}

GameObject* GameObjectFactory::createCoin() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::Coin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Items);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::Coin, TextureIdentifiers::Items);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createScoreCoin() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::ScoreCoin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Items);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::ScoreCoin, TextureIdentifiers::Items);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createQuestionMarkBox() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Blocks, SpritesetRegionIdentifiers::Blocks::QuestionMarkBox);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Blocks);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::QuestionMarkBox, TextureIdentifiers::Items);
	object->setState(std::move(state));

	return object;
}

std::unique_ptr<Animation> GameObjectFactory::createAnimation(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept
{
	return std::make_unique<Animation>(mSpritesetContainer.getSpriteset(spritesetIdetntifier).getRegion(spritesetRegionIdentifier));
}

GameObject* GameObjectFactory::createObject(const GameObjectIdentifiers identifier, const TextureIdentifiers textureIdentifier) const noexcept
{
	auto object = mGameObjectCreator.create(identifier);
	object->setTexture(mResourceContainer.getTexture(textureIdentifier));

	return object;
}
