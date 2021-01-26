#include "GraphicsItem.hpp"

#include <algorithm>
#include <functional>

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsItem::GraphicsItem() :
	mParentItem{nullptr},
	mIsVisible{true},
	mIsRemoved{false}
{

}

void GraphicsItem::setVisible(const bool visible)
{
	mIsVisible = visible;
}

void GraphicsItem::remove()
{
	mIsRemoved = true;
}

void GraphicsItem::addItem(std::unique_ptr<GraphicsItem> item)
{
	item->setParent(this);

	mItems.emplace_back(std::move(item));
}

void GraphicsItem::clean()
{
	cleanItems();

	for (auto& item : mItems)
	{
		item->clean();
	}
}

sf::FloatRect GraphicsItem::getBounds() const
{
	return getGlobalTransform().transformRect({});
}

sf::Transform GraphicsItem::getGlobalTransform() const
{
	auto transform = sf::Transform::Identity;

	for (auto item{this}; item != nullptr; item = item->getParent())
	{
		transform.combine(item->getTransform());
	}

	return transform;
}

sf::Vector2f GraphicsItem::getGlobalPosition() const
{
	return getGlobalTransform() * sf::Vector2f{};
}

bool GraphicsItem::isContainsPoint(const sf::Vector2f& point) const
{
	return getBounds().contains(point);
}

bool GraphicsItem::isIntersectsItem(const GraphicsItem& item) const
{
	return getBounds().intersects(item.getBounds());
}

bool GraphicsItem::isVisible() const
{
	return mIsVisible;
}

bool GraphicsItem::isRemoved() const
{
	return mIsRemoved;
}

void GraphicsItem::setParent(GraphicsItem* item)
{
	mParentItem = item;
}

GraphicsItem* GraphicsItem::getParent() const
{
	return mParentItem;
}

void GraphicsItem::cleanItems()
{
	auto itemsIterator = std::remove_if(mItems.begin(), mItems.end(), std::mem_fn(&GraphicsItem::isRemoved));
	mItems.erase(itemsIterator, mItems.end());
}

void GraphicsItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mIsVisible)
	{
		states.transform.combine(getTransform());

		drawSelf(target, states);
		drawItems(target, states);
	}
}

void GraphicsItem::drawItems(sf::RenderTarget& target, sf::RenderStates& states) const
{
	for (auto& item : mItems)
	{
		target.draw(*item, states);
	}
}

void GraphicsItem::drawSelf(sf::RenderTarget&, sf::RenderStates) const
{

}
