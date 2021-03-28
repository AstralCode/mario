#pragma once

class Item;

class ItemBuilder
{
public:
	virtual ~ItemBuilder() = default;

	virtual void buildTexture() noexcept = 0;
	virtual void buildComponents() noexcept = 0;

	virtual void buildActiveAnimation() noexcept = 0;
	virtual void buildPickupAnimation() noexcept = 0;

	virtual void buildState() noexcept = 0;
};
