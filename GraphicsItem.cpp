#include "GraphicsItem.hpp"

#include <algorithm>
#include <functional>

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsItem::GraphicsItem() noexcept :
	mParentItem{nullptr},
	mIsVisible{true},
	mIsRemoved{false},
	mIsMouseOver{false}
{
	
}

void GraphicsItem::setPosition(const float x, const float y) noexcept
{
	mTransform.setPosition(x, y);
}

void GraphicsItem::setPosition(const FloatPoint& position) noexcept
{
	mTransform.setPosition(position.getX(), position.getY());
}

void GraphicsItem::setPositionX(const float x) noexcept
{
	mTransform.setPosition(x, getLocalPosition().getY());
}

void GraphicsItem::setPositionY(const float y) noexcept
{
	mTransform.setPosition(getLocalPosition().getX(), y);
}

void GraphicsItem::move(const float x, const float y) noexcept
{
	mTransform.move(x, y);
}

void GraphicsItem::move(const FloatPoint& offset) noexcept
{
	mTransform.move(offset.getX(), offset.getY());
}

void GraphicsItem::setOrigin(const float x, const float y)
{
	mTransform.setOrigin(x, y);
}

void GraphicsItem::setOrigin(const FloatPoint& origin)
{
	mTransform.setOrigin(origin.getX(), origin.getY());
}

void GraphicsItem::setVisible(const bool visible) noexcept
{
	mIsVisible = visible;
}

void GraphicsItem::remove() noexcept
{
	mIsRemoved = true;
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

void GraphicsItem::receiveEvents(const sf::Event& event) noexcept
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		onKeyPressed(event.key);
		break;

	case sf::Event::KeyReleased:
		onKeyReleased(event.key);
		break;

	case sf::Event::MouseButtonPressed:
		if (isContainsPoint({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
		{
			onMouseClick(event.mouseButton);
		}
		break;

	case sf::Event::MouseMoved:
	{
		const bool isMouseOver = isContainsPoint({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)});

		if (isMouseOver)
		{
			if (mIsMouseOver)
			{
				onMouseOver(event.mouseMove);
			}
			else
			{
				onMouseEnter(event.mouseMove);
				onMouseOver(event.mouseMove);

				mIsMouseOver = true;
			}
		}
		else
		{
			if (mIsMouseOver)
			{
				onMouseLeave(event.mouseMove);

				mIsMouseOver = false;
			}
		}
		break;
	}

	default:
		break;
	}

	for (auto& item : mItems)
	{
		item->receiveEvents(event);
	}
}

FloatArea GraphicsItem::getLocalArea() const noexcept
{
	return {};
}

FloatArea GraphicsItem::getArea() const noexcept
{
	const auto position = getPosition();
	const auto size = getLocalArea().getSize();

	return {position, size};
}

sf::Transform GraphicsItem::getLocalTransform() const noexcept
{
	return mTransform.getTransform();
}

sf::Transform GraphicsItem::getGlobalTransform() const noexcept
{
	auto transform = sf::Transform::Identity;

	for (auto item{this}; item != nullptr; item = item->getParent())
	{
		transform.combine(item->getLocalTransform());
	}

	return transform;
}

FloatPoint GraphicsItem::getLocalPosition() const noexcept
{
	return mTransform.getPosition();
}

FloatPoint GraphicsItem::getPosition() const noexcept
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
	return mIsVisible;
}

bool GraphicsItem::isRemoved() const noexcept
{
	return mIsRemoved;
}


void GraphicsItem::onKeyPressed(const sf::Event::KeyEvent&) noexcept
{

}

void GraphicsItem::onKeyReleased(const sf::Event::KeyEvent&) noexcept
{

}

void GraphicsItem::onMouseClick(const sf::Event::MouseButtonEvent&) noexcept
{

}

void GraphicsItem::onMouseOver(const sf::Event::MouseMoveEvent&) noexcept
{

}

void GraphicsItem::onMouseEnter(const sf::Event::MouseMoveEvent&) noexcept
{

}

void GraphicsItem::onMouseLeave(const sf::Event::MouseMoveEvent&) noexcept
{

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
	if (mIsVisible)
	{
		states.transform.combine(mTransform.getTransform());

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
