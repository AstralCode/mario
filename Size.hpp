#pragma once

#include "SFML/System/Vector2.hpp"

template <typename T>
class Size final
{
public:
	Size() = default;
	Size(const T width, const T height) noexcept;
	Size(const sf::Vector2<T>& size) noexcept;

	void setWidth(const T width) noexcept;
	void setHeight(const T height) noexcept;

	T getWidth() const noexcept;
	T getHeight() const noexcept;

private:
	T mWidth;
	T mHeight;
};

template <typename T>
inline Size<T>::Size(const T width, const T height) noexcept :
	mWidth{width},
	mHeight{height}
{

}

template <typename T>
inline Size<T>::Size(const sf::Vector2<T>& size) noexcept :
	mWidth{size.x},
	mHeight{size.y}
{

}

template<typename T>
inline void Size<T>::setWidth(const T width) noexcept
{
	mWidth = width;
}

template<typename T>
inline void Size<T>::setHeight(const T height) noexcept
{
	mHeight = height;
}

template <typename T>
inline T Size<T>::getWidth() const noexcept
{
	return mWidth;
}

template <typename T>
inline T Size<T>::getHeight() const noexcept
{
	return mHeight;
}
