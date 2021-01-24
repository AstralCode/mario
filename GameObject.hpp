#pragma once

#include "SFML/System/Time.hpp"

#include "GraphicsSpriteItem.hpp"

class GameObject
{
public:
	GameObject(GraphicsSpriteItem* sprite);

	void setDestroyed(const bool destroyed);
	void setWorldPosition(const sf::Vector2f& position);
	
	void update(const sf::Time& frameTime);

	const sf::Vector2f& getWorldPosition() const;

	bool hasCollision(const GameObject& object) const;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isDestroyed() const;

private:
	GraphicsSpriteItem* mSprite;
	bool mIsDestroyed;
};