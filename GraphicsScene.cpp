#include "GraphicsScene.hpp"

GraphicsScene::GraphicsScene() noexcept
{

}

void GraphicsScene::addItem(std::unique_ptr<GraphicsItem> item) noexcept
{
	mRoot.addItem(std::move(item));
}

void GraphicsScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
