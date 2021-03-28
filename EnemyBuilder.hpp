#pragma once

class Enemy;

class EnemyBuilder
{
public:
	virtual ~EnemyBuilder() = default;

	virtual void buildTexture() noexcept = 0;
	virtual void buildComponents() noexcept = 0;

	virtual void buildMoveAnimation() noexcept = 0;
	virtual void buildLoseAnimation() noexcept = 0;

	virtual void buildState() noexcept = 0;
};
