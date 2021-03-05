#pragma once

#include "GraphicsItem.hpp"
#include "TilemapView.hpp"

class GraphicsScene final : public sf::Drawable
{
public:
	GraphicsScene() noexcept;
	
	void addItem(std::unique_ptr<GraphicsItem> item) noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	GraphicsItem mRoot;
};
