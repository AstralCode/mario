#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
#include "GraphicsItem.hpp"
#include "EntityType.hpp"
#include "CollisionSideType.hpp"
#include "Tile.hpp"

class World;
class Sprite;

class Entity : public GraphicsItem
{
public:
	enum class ComponentType
	{
		Mass,
		Movement,
		Transparency,
		Solid
	};

	enum class Directions
	{
		Left,
		Right
	};

	using Components = Flags<ComponentType>;

	Entity(const EntityType type, World& world) noexcept;
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
	virtual void collision(const Entity& collider, const CollisionSideType side) noexcept = 0;

	virtual void update(const sf::Time& dt) noexcept = 0;

	virtual void falling() noexcept = 0;

	EntityType getType() const noexcept;

	World& getWorld() noexcept;
	const World& getWorld() const noexcept;

	const Components& getComponents() const noexcept;

	const Directions& getDirection() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	FloatArea getLocalArea() const noexcept override;

	bool hasType( const EntityType type ) const noexcept;
	bool hasComponent( const ComponentType component ) const noexcept;
	bool hasDirection(const Directions direction) const noexcept;

	bool isBoundsVisible() const noexcept;
	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	EntityType mType;

	World& mWorld;

	Components mComponents;

	Sprite* mSprite;

	FloatPoint mAcceleration;
	FloatPoint mVelocity;

	Directions mDirection;

	sf::Color mBoundsColor;

	bool mIsBoundsVisible;
	bool mIsDestroyed;
};
