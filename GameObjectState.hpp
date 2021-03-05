#pragma once

#include <memory>

#include "Animation.hpp"
#include "SpritesetContainer.hpp"

class GameObject;

class GameObjectState
{
public:
	GameObjectState(const Spriteset& spriteset) noexcept;
	virtual ~GameObjectState() = default;

	void setAnimation(std::unique_ptr<Animation> animation) noexcept;

	virtual void onSet(GameObject& object) noexcept;
	virtual void onUnset(GameObject& object) noexcept;

	void destroy() noexcept;

	virtual void onCollision(GameObject& object) noexcept;

	void update(GameObject& object, const sf::Time& frameTime) noexcept;

	virtual void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept;
	virtual void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept;

	virtual void onMouseClick(GameObject& object, const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept;

	virtual void onMouseEnter(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;
	virtual void onMouseLeave(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;
	virtual void onMouseOver(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;

	const SpriteArea& getSpriteArea(const std::string& spritesetRegionidentifier) const noexcept;

	bool isDestroyed() const noexcept;

protected:
	std::unique_ptr<Animation> createAnimation(const std::string& spritesetRegionIdentifier) const noexcept;

	template <typename TGameObjectState>
	std::unique_ptr<TGameObjectState> createState() const noexcept;

private:
	virtual void updateSelf(GameObject& object, const sf::Time& frameTime) noexcept;

	const Spriteset& mSpriteset;

	std::unique_ptr<Animation> mAnimation;

	bool mRemoved;
};

template<typename TGameObjectState>
inline std::unique_ptr<TGameObjectState> GameObjectState::createState() const noexcept
{
	static_assert(std::is_base_of_v<GameObjectState, TGameObjectState>, "TGameObjectState must derived from GameObjectState");

	return std::make_unique<TGameObjectState>(mSpriteset);
}
