#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
#include "GraphicsItem.hpp"
#include "CollisionSideType.hpp"
#include "Tile.hpp"

class Hero;
class Enemy;
class Item;
class Sprite;

class Entity : public GraphicsItem
{
public:
	enum class ComponentType
	{
		Mass,
		Movement,
		Transparency
	};

	enum class Directions
	{
		Left,
		Right
	};

	using Components = Flagset<ComponentType, 6u>;

	Entity() noexcept;
	virtual ~Entity() = default;

	static void centerOrigin(Entity& entity) noexcept;

	void setComponent(const ComponentType component) noexcept;
	void unsetComponent(const ComponentType component) noexcept;

	void setTexture(const sf::Texture& texture) noexcept;
	void setSpriteArea(const IntArea& area) noexcept;

	void setBoundsColor(const sf::Color& color) noexcept;
	void setBoundsVisible(const bool visible) noexcept;

	void setDirection(const Directions direction) noexcept;

	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;

	void destroy() noexcept;

	virtual void collision(const Tile& tile, const CollisionSideType side) noexcept = 0;
	virtual void collision(Entity& entity, const CollisionSideType side) const noexcept = 0;

	virtual void collision(const Hero& hero, const CollisionSideType side) noexcept = 0;
	virtual void collision(const Enemy& enemy, const CollisionSideType side) noexcept = 0;
	virtual void collision(const Item& item, const CollisionSideType side) noexcept = 0;

	virtual void update(const sf::Time& dt) noexcept = 0;

	virtual void falling() noexcept = 0;

	bool hasComponent(const ComponentType trait) const noexcept;

	const Components& getComponents() const noexcept;

	const Directions& getDirection() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	FloatArea getLocalArea() const noexcept override;

	bool hasDirection(const Directions direction) const noexcept;

	bool isBoundsVisible() const noexcept;

	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	Components mComponents;

	Sprite* mSprite;

	FloatPoint mAcceleration;
	FloatPoint mVelocity;

	Directions mDirection;

	sf::Color mBoundsColor;

	bool mIsBoundsVisible;
	bool mIsDestroyed;
};
