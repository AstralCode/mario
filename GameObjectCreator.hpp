#pragma once

class GameObject;
class GraphicsSpriteItem;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GameObject* create(GraphicsSpriteItem* sprite) = 0;
};