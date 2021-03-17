#pragma once

#include <memory>

#include "SFML/Window/Event.hpp"

#include "Tile.hpp"

class GameObject;

class GameObjectState
{
public:
	virtual ~GameObjectState() = default;

	virtual void onSet(GameObject& object) noexcept = 0;
	virtual void update(GameObject& object, const sf::Time& fixedFrameTime) noexcept = 0;

	void destroy() noexcept;

	virtual void onTileTopCollision(GameObject& object, const Tile& tile) noexcept;
	virtual void onTileBottomCollision(GameObject& object, const Tile& tile) noexcept;
	virtual void onTileLeftCollision(GameObject& object, const Tile& tile) noexcept;
	virtual void onTileRightCollision(GameObject& object, const Tile& tile) noexcept;

	virtual void onObjectCollision(GameObject& object) noexcept;

	virtual void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept;
	virtual void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept;

	virtual void onMouseClick(GameObject& object, const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept;

	virtual void onMouseEnter(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;
	virtual void onMouseLeave(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;
	virtual void onMouseOver(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;

	virtual bool isJumping() const noexcept;

	bool isDestroyed() const noexcept;

private:
	bool mRemoved{false};
};
