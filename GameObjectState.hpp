#pragma once

#include <memory>

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "Animation.hpp"
#include "SpritesetContainer.hpp"

class GameObject;

class GameObjectState
{
public:
	GameObjectState(const Spriteset& spriteset);
	virtual ~GameObjectState() = default;

	void setAnimation(std::unique_ptr<Animation> animation);

	virtual void onSet(GameObject& object);
	virtual void onUnset(GameObject& object);

	void destroy();

	void update(GameObject& object, const sf::Time& frameTime);

	virtual void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent);
	virtual void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent);

	virtual void onMouseClick(GameObject& object, const sf::Event::MouseButtonEvent& mouseButtonEvent);

	virtual void onMouseEnter(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);
	virtual void onMouseLeave(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);
	virtual void onMouseOver(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);

	const sf::IntRect& getSprite(const std::string& spritesetRegionidentifier) const;

	virtual bool isWreck() const;

	bool isDestroyed() const;

protected:
	std::unique_ptr<Animation> createAnimation(const std::string& spritesetRegionIdentifier) const;

	template <typename TGameObjectState>
	std::unique_ptr<TGameObjectState> createState() const;

private:
	virtual void updateSelf(GameObject& object, const sf::Time& frameTime);

	const Spriteset& mSpriteset;

	std::unique_ptr<Animation> mAnimation;

	bool mRemoved;
};

template<typename TGameObjectState>
inline std::unique_ptr<TGameObjectState> GameObjectState::createState() const
{
	static_assert(std::is_base_of_v<GameObjectState, TGameObjectState>, "TGameObjectState must derived from GameObjectState");

	return std::make_unique<TGameObjectState>(mSpriteset);
}
