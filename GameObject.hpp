#pragma once

#include "GameObjectState.hpp"
#include "GraphicsSpriteItem.hpp"

class GameObject
{
public:
	GameObject(GraphicsSpriteItem* sprite);

	void setState(GameObjectState* state);

	void setPosition(const sf::Vector2f& position);
	void setTexture(const sf::Texture& texture);
	void setTextureArea(const sf::IntRect& area);

	void removeSprite();
	void destroy();

	void receiveEvents(const sf::Event& event);
	
	void update(const sf::Time& frameTime);

	sf::Vector2f getPosition() const;

	bool hasCollision(const GameObject& object) const;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isDestroyed() const;

private:
	GraphicsSpriteItem* mSprite;
	GameObjectState* mState;

	bool mIsMouseOver;
};
