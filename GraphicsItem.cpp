#include "GraphicsItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsItem::GraphicsItem() :
	mParentItem{nullptr}
{

}

void GraphicsItem::addItem(std::unique_ptr<GraphicsItem> item)
{
	item->setParent(this);
	mItems.emplace_back(std::move(item));
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

bool GraphicsItem::isContainsPoint(const sf::Vector2f& point) const
{
	return getBounds().contains(point);
}

bool GraphicsItem::isIntersectsItem(const GraphicsItem& item) const
{
	return getBounds().intersects(item.getBounds());
}

void GraphicsItem::setParent(GraphicsItem* item)
{
	mParentItem = item;
}

GraphicsItem* GraphicsItem::getParent() const
{
	return mParentItem;
}

void GraphicsItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());

	drawSelf(target, states);
	drawItems(target, states);
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
