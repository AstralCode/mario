#pragma once

#include <vector>
#include <memory>

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

class GraphicsItem : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	GraphicsItem();
	virtual ~GraphicsItem() = default;

	void addItem(std::unique_ptr<GraphicsItem> item);

	sf::FloatRect getBounds() const;

	virtual sf::Transform getGlobalTransform() const;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isIntersectsItem(const GraphicsItem& item) const;

private:
	void setParent(GraphicsItem* item);
	GraphicsItem* getParent() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void drawItems(sf::RenderTarget& target, sf::RenderStates& states) const;

	virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	GraphicsItem* mParentItem;
	std::vector<std::unique_ptr<GraphicsItem>> mItems;
};
