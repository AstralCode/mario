#pragma once

class GameObject;
class GameSpriteAtlas;
class GraphicsSpriteItem;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GameObject* create(const GameSpriteAtlas& spriteAtlas, GraphicsSpriteItem* sprite) = 0;
};