#pragma once

#include <map>

#include "SFML/Graphics/Drawable.hpp"

#include "GraphicsItem.hpp"
#include "TilemapView.hpp"

class GraphicsScene final : public sf::Drawable
{
public:
	GraphicsScene() noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
