#pragma once

class GameObject;
class GraphicsItem;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GameObject* create(GraphicsItem& graphicsScene) = 0;
};