#pragma once

class GameObject;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GameObject* create() = 0;
};