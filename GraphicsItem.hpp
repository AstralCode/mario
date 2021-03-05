#pragma once

#include <vector>
#include <memory>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Event.hpp"

#include "Area.hpp"

class GraphicsItem : public sf::Drawable
{
public:
	GraphicsItem() noexcept;
	virtual ~GraphicsItem() = default;

	void setPosition(const float x, const float y) noexcept;
	void setPosition(const FloatPoint& position) noexcept;
	void setPositionX(const float x) noexcept;
	void setPositionY(const float y) noexcept;

	void move(const float x, const float y) noexcept;
	void move(const FloatPoint& offset) noexcept;

	void setOrigin(const float x, const float y);
	void setOrigin(const FloatPoint& origin);

	void setVisible(const bool visible) noexcept;

	void remove() noexcept;

	template<typename TGraphicsItem, typename... TArguments>
	TGraphicsItem* addItem(TArguments&&... arguments) noexcept;

	void addItem(std::unique_ptr<GraphicsItem> item) noexcept;

	void clean() noexcept;
	
	void receiveEvents(const sf::Event& event) noexcept;

	virtual FloatArea getArea() const noexcept;

	sf::Transform getLocalTransform() const noexcept;
	sf::Transform getGlobalTransform() const noexcept;

	FloatPoint getLocalPosition() const noexcept;
	FloatPoint getGlobalPosition() const noexcept;

	bool isContainsPoint(const FloatPoint& point) const noexcept;
	bool isIntersectsItem(const GraphicsItem& item) const noexcept;

	bool isVisible() const noexcept;
	bool isRemoved() const noexcept;

private:
	void setParent(GraphicsItem* item) noexcept;
	GraphicsItem* getParent() const noexcept;

	void cleanItems() noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void drawItems(sf::RenderTarget& target, sf::RenderStates states) const noexcept;

	virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
	virtual void receiveEventsSelf(const sf::Event& event) noexcept;

	sf::Transformable mTransform;

	GraphicsItem* mParentItem;

	bool mVisible;
	bool mRemoved;

	std::vector<std::unique_ptr<GraphicsItem>> mItems;
};

template<typename TGraphicsItem, typename... TArguments>
inline TGraphicsItem* GraphicsItem::addItem(TArguments&&... arguments) noexcept
{
	static_assert(std::is_base_of_v<GraphicsItem, TGraphicsItem>, "TGraphicsItem must derived from GraphicsItem");

	auto item = std::make_unique<TGraphicsItem>(std::forward<TArguments&&>(arguments)...);
	auto itemPointer = item.get();

	addItem(std::move(item));

	return itemPointer;
}
