#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

class GameObject;

class GameObjectState
{
public:
	virtual ~GameObjectState() = default;

	virtual void onSet(GameObject& object) = 0;
	virtual void onUnset(GameObject& object) = 0;

	virtual void destroy() = 0;

	virtual void update(GameObject& object, const sf::Time& frameTime) = 0;

	virtual void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent);
	virtual void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent);

	virtual void onMouseClick(GameObject& object, const sf::Event::MouseButtonEvent& mouseButtonEvent);

	virtual void onMouseEnter(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);
	virtual void onMouseLeave(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);
	virtual void onMouseOver(GameObject& object, const sf::Event::MouseMoveEvent& mouseMoveEvent);

	virtual bool isDestroyed() const = 0;

protected:
	bool isKeyPressed(const sf::Event::KeyEvent& keyEvent, const sf::Keyboard::Key keyCode) const;
};
