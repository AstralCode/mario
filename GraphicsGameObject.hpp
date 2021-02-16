#pragma once

#include "GraphicsItem.hpp"
#include "GameObject.hpp"

class GraphicsSpriteItem;

class GraphicsGameObject final : public GraphicsItem, public GameObject
{
public:
	GraphicsGameObject();

	void setState(std::unique_ptr<GameObjectState> state) override;

	void setPosition(const sf::Vector2f& position) override;
	void setTexture(const sf::Texture& texture) override;
	void setTextureArea(const sf::IntRect& area) override;

	void setMaxAcceleration(const sf::Vector2f& acceleration) override;
	void setAcceleration(const sf::Vector2f& acceleration) override;
	void setMaxVelocity(const sf::Vector2f& velocity) override;
	void setVelocity(const sf::Vector2f& velocity) override;

	void accelerateVelocity(const sf::Vector2f& acceleration) override;
	void move(const sf::Vector2f& offset) override;

	void setDirectionFactor(const sf::Vector2f& factor) override;
	void setDirection(const Directions direction) override;
	void turnAround() override;

	void destroy() override;

	void receiveEvents(const sf::Event& event) override;

	void update(const sf::Time& frameTime) override;

	sf::Vector2f getPosition() const override;

	sf::FloatRect getBounds() const;

	const sf::Vector2f& getMaxAcceleration() const override;
	const sf::Vector2f& getAcceleration() const override;
	const sf::Vector2f& getMaxVelocity() const override;
	const sf::Vector2f& getVelocity() const override;

	const sf::Vector2f& getDirectionFactor() const override;
	Directions getDirection() const override;

	bool hasCollision(const GraphicsItem& item) const override;

	bool isContainsPoint(const sf::Vector2f& point) const override;
	bool isDestroyed() const override;

protected:
	bool isWreck() const override;

private:
	GraphicsSpriteItem* mSprite;

	std::unique_ptr<GameObjectState> mState;

	sf::Vector2f mMaxAcceleration;
	sf::Vector2f mAcceleration;
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;

	sf::Vector2f mDirectionFactor;
	Directions mDirection;

	bool mMouseOver;
};
