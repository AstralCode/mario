#include "GraphicsItem.hpp"

#include <algorithm>
#include <functional>

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsItem::GraphicsItem() noexcept :
	mParentItem{nullptr},
	mVisible{true},
	mRemoved{false}
{

}

void GraphicsItem::setPosition(const float x, const float y) noexcept
{
	Transformable::setPosition(x, y);
}

void GraphicsItem::setPosition(const FloatPoint& position) noexcept
{
	Transformable::setPosition(position.getX(), position.getY());
}

void GraphicsItem::setPositionX(const float x) noexcept
{
	Transformable::setPosition(x, getPosition().getY());
}

void GraphicsItem::setPositionY(const float y) noexcept
{
	Transformable::setPosition(getPosition().getX(), y);
}

void GraphicsItem::setVisible(const bool visible) noexcept
{
	mVisible = visible;
}

void GraphicsItem::remove() noexcept
{
	mRemoved = true;
}

void GraphicsItem::addItem(std::unique_ptr<GraphicsItem> item) noexcept
{
	item->setParent(this);

	mItems.emplace_back(std::move(item));
}

void GraphicsItem::clean() noexcept
{
	cleanItems();

	for (auto& item : mItems)
	{
		item->clean();
	}
}

FloatArea GraphicsItem::getArea() const noexcept
{
	return {};
}

sf::Transform GraphicsItem::getGlobalTransform() const noexcept
{
	auto transform = sf::Transform::Identity;

	for (auto item{this}; item != nullptr; item = item->getParent())
	{
		transform.combine(item->getTransform());
	}

	return transform;
}

FloatPoint GraphicsItem::getPosition() const noexcept
{
	return Transformable::getPosition();
}

FloatPoint GraphicsItem::getGlobalPosition() const noexcept
{
	return getGlobalTransform() * sf::Vector2f{};
}

bool GraphicsItem::isContainsPoint(const FloatPoint& point) const noexcept
{
	return getArea().isContainsPoint(point);
}

bool GraphicsItem::isIntersectsItem(const GraphicsItem& item) const noexcept
{
	return getArea().isIntersects(item.getArea());
}

bool GraphicsItem::isVisible() const noexcept
{
	return mVisible;
}

bool GraphicsItem::isRemoved() const noexcept
{
	return mRemoved;
}

void GraphicsItem::setParent(GraphicsItem* item) noexcept
{
	mParentItem = item;
}

GraphicsItem* GraphicsItem::getParent() const noexcept
{
	return mParentItem;
}

void GraphicsItem::cleanItems() noexcept
{
	auto itemsIterator = std::remove_if(mItems.begin(), mItems.end(), std::mem_fn(&GraphicsItem::isRemoved));
	mItems.erase(itemsIterator, mItems.end());
}

void GraphicsItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mVisible)
	{
		states.transform.combine(getTransform());

		drawSelf(target, states);
		drawItems(target, states);
	}
}

void GraphicsItem::drawItems(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	for (auto& item : mItems)
	{
		target.draw(*item, states);
	}
}

void GraphicsItem::drawSelf(sf::RenderTarget&, sf::RenderStates) const noexcept
{

}
