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

	FloatPoint getOrigin() const noexcept;

	virtual FloatArea getLocalArea() const noexcept;
	FloatArea getArea() const noexcept;

	sf::Transform getLocalTransform() const noexcept;
	sf::Transform getGlobalTransform() const noexcept;

	FloatPoint getLocalPosition() const noexcept;
	FloatPoint getPosition() const noexcept;

	bool isContainsPoint(const IntPoint& point) const noexcept;
	bool isContainsPoint(const FloatPoint& point) const noexcept;

	bool isIntersects(const FloatArea& area) const noexcept;
	bool isIntersects(const GraphicsItem& item) const noexcept;

	bool isVisible() const noexcept;
	bool isRemoved() const noexcept;

protected:
	virtual void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept;
	virtual void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept;

	virtual void onMouseClick(const sf::Event::MouseButtonEvent& mouseEvent) noexcept;
	virtual void onMouseOver(const sf::Event::MouseMoveEvent& mouseEvent) noexcept;
	virtual void onMouseEnter(const sf::Event::MouseMoveEvent& mouseEvent) noexcept;
	virtual void onMouseLeave(const sf::Event::MouseMoveEvent& mouseEvent) noexcept;

private:
	void setParent(GraphicsItem* item) noexcept;
	GraphicsItem* getParent() const noexcept;

	void cleanItems() noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void drawItems(sf::RenderTarget& target, sf::RenderStates states) const noexcept;

	virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept;

	sf::Transformable mTransform;

	GraphicsItem* mParentItem;

	bool mIsVisible;
	bool mIsRemoved;
	bool mIsMouseOver;

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
