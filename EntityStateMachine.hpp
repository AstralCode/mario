#pragma once

#include <map>
#include <memory>

#include "Entity.hpp"
#include "EntityState.hpp"
#include "TypeIdGenerator.hpp"

template <typename TEntity>
class EntityStateMachine final
{
public:
	template <typename TState>
	void registerState() noexcept;

	template <typename TState>
	void setState(TEntity& entity);

	EntityState<TEntity>& getState() noexcept;
	const EntityState<TEntity>& getState() const noexcept;

private:
	std::map<TypeId, std::unique_ptr<EntityState<TEntity>>> mStates;

	EntityState<TEntity>* mCurrentState;
};

template <typename TEntity>
template <typename TState>
inline void EntityStateMachine<TEntity>::registerState() noexcept
{
	static_assert(std::is_base_of_v<EntityState<TEntity>, TState>, "TState must derived from EntityState class");

	mStates.emplace(TypeIdGenerator::id<TState>(), std::make_unique<TState>());
}

template <typename TEntity>
template <typename TState>
inline void EntityStateMachine<TEntity>::setState(TEntity& entity)
{
	mCurrentState = mStates.at(TypeIdGenerator::id<TState>()).get();
	mCurrentState->onSet(entity);
}

template<typename TEntity>
inline EntityState<TEntity>& EntityStateMachine<TEntity>::getState() noexcept
{
	return *mCurrentState;
}

template <typename TEntity>
inline const EntityState<TEntity>& EntityStateMachine<TEntity>::getState() const noexcept
{
	return *mCurrentState;
}
