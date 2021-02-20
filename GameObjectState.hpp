#pragma once

#include <memory>

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "Animation.hpp"
#include "SpritesetContainer.hpp"

class GraphicsGameObject;

class GameObjectState
{
public:
	GameObjectState(const Spriteset& spriteset);
	virtual ~GameObjectState() = default;

	void setAnimation(std::unique_ptr<Animation> animation);

	virtual void onSet(GraphicsGameObject& object);
	virtual void onUnset(GraphicsGameObject& object);

	void destroy();

	void update(GraphicsGameObject& object, const sf::Time& frameTime);

	virtual void onKeyPressed(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent);
	virtual void onKeyReleased(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent);

	virtual void onMouseClick(GraphicsGameObject& object, const sf::Event::MouseButtonEvent& mouseButtonEvent);

	virtual void onMouseEnter(GraphicsGameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);
	virtual void onMouseLeave(GraphicsGameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);
	virtual void onMouseOver(GraphicsGameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);

	const SpriteArea& getSpriteArea(const std::string& spritesetRegionidentifier) const;

	bool isDestroyed() const;

protected:
	std::unique_ptr<Animation> createAnimation(const std::string& spritesetRegionIdentifier) const;

	template <typename TGameObjectState>
	std::unique_ptr<TGameObjectState> createState() const;

private:
	virtual void updateSelf(GraphicsGameObject& object, const sf::Time& frameTime);

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
