#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
#include "GraphicsItem.hpp"
#include "Tile.hpp"
#include "CollisionSideType.hpp"

class Sprite;

class Entity : public GraphicsItem
{
public:
	enum class Attributes
	{
		Movable,
		Controlablle,
		Collectable,
		Deadly,
		Transparent
	};

	enum class Directions
	{
		Left,
		Right
	};

	using AttributeFlags = Flags<Attributes, 5u>;

	Entity() noexcept;
	virtual ~Entity() = default;

	static FloatPoint centerOrigin(const Entity& entity) noexcept;

	void setAttributes(const AttributeFlags& attributes) noexcept;
	void setAttribute(const Attributes attribute) noexcept;

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

	virtual void update(const sf::Time& dt) noexcept = 0;

	virtual void tileCollision(const Tile& tile, const CollisionSideType side) noexcept = 0;
	virtual void entityCollision(const Entity& entity, const CollisionSideType side) noexcept = 0;

	virtual void falling() noexcept = 0;

	bool hasAttribute(const Attributes attribute) const noexcept;

	const AttributeFlags& getAttrubutes() const noexcept;

	const Directions& getDirection() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	FloatArea getLocalArea() const noexcept override;

	bool hasDirection(const Directions direction) const noexcept;

	bool isBoundsVisible() const noexcept;

	virtual bool isJumping() const noexcept = 0;
	virtual bool isFalling() const noexcept = 0;

	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	AttributeFlags mAttributes;

	Sprite* mSprite;

	FloatPoint mAcceleration;
	FloatPoint mVelocity;

	Directions mDirection;

	sf::Color mBoundsColor;

	bool mIsBoundsVisible;
	bool mIsDestroyed;
};
