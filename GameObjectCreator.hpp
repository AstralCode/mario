#pragma once

class GraphicsGameObject;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GraphicsGameObject* create() = 0;
};