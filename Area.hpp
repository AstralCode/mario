#pragma once

#include "SFML/Graphics/Rect.hpp"

template <typename T>
class Area final
{
public:
	Area() = default;
	Area(const sf::Rect<T>& rectangle) noexcept;
	Area(const T x, const T y, const T width, const T height) noexcept;

	void setX(const T x) noexcept;
	void setY(const T y) noexcept;

	void setWidth(const T width) noexcept;
	void setHeight(const T height) noexcept;

	void setRectangle(const sf::Rect<T>& rectangle);

	T getTop() const noexcept;
	T getLeft() const noexcept;
	T getRight() const noexcept;
	T getBottom() const noexcept;

	sf::Vector2<T> getTopLeft() const noexcept;
	sf::Vector2<T> getTopRight() const noexcept;
	sf::Vector2<T> getBottomLeft() const noexcept;
	sf::Vector2<T> getBottomRight() const noexcept;
	sf::Vector2<T> getCenter() const noexcept;

	T getX() const noexcept;
	T getY() const noexcept;

	T getWidth() const noexcept;
	T getHeight() const noexcept;

	sf::Vector2<T> getSize() const noexcept;

	const sf::Rect<T>& getRectangle() const noexcept;

	bool isContainsPoint(const T x, const T y) const noexcept;
	bool isContainsPoint(const sf::Vector2<T>& point) const noexcept;

	bool isIntersects(const Area<T>& area) const noexcept;
	bool isIntersects(const sf::Rect<T>& rectangle) const noexcept;

private:
	sf::Rect<T> mRectangle;
};

template <typename T>
inline Area<T>::Area(const sf::Rect<T>& rectangle) noexcept :
	mRectangle{rectangle}
{

}

template <typename T>
inline Area<T>::Area(const T x, const T y, const T width, const T height) noexcept :
	mRectangle{x, y, width, height}
{

}

template <typename T>
inline void Area<T>::setX(const T x) noexcept
{
	mRectangle.left = x;
}

template <typename T>
inline void Area<T>::setY(const T y) noexcept
{
	mRectangle.top = y;
}

template<typename T>
inline void Area<T>::setWidth(const T width) noexcept
{
	mRectangle.width = width;
}

template<typename T>
inline void Area<T>::setHeight(const T height) noexcept
{
	mRectangle.height = height;
}

template <typename T>
inline void Area<T>::setRectangle(const sf::Rect<T>& rectangle)
{
	mRectangle = rectangle;
}

template <typename T>
inline T Area<T>::getTop() const noexcept
{
	return mRectangle.top;
}

template <typename T>
inline T Area<T>::getLeft() const noexcept
{
	return mRectangle.left;
}

template <typename T>
inline T Area<T>::getRight() const noexcept
{
	return mRectangle.left + mRectangle.width;
}

template <typename T>
inline T Area<T>::getBottom() const noexcept
{
	return mRectangle.top + mRectangle.height;
}

template <typename T>
inline sf::Vector2<T> Area<T>::getTopLeft() const noexcept
{
	return {mRectangle.left, mRectangle.top};
}

template <typename T>
inline sf::Vector2<T> Area<T>::getTopRight() const noexcept
{
	return {mRectangle.left + mRectangle.width, mRectangle.top};
}

template <typename T>
inline sf::Vector2<T> Area<T>::getBottomLeft() const noexcept
{
	return {mRectangle.left, mRectangle.top + mRectangle.height};
}

template <typename T>
inline sf::Vector2<T> Area<T>::getBottomRight() const noexcept
{
	return {mRectangle.left + mRectangle.width, mRectangle.top + mRectangle.height};
}

template <typename T>
inline sf::Vector2<T> Area<T>::getCenter() const noexcept
{
	return {mRectangle.left + mRectangle.width / 2, mRectangle.top + mRectangle.height / 2};
}

template <typename T>
inline T Area<T>::getX() const noexcept
{
	return mRectangle.left;
}

template <typename T>
inline T Area<T>::getY() const noexcept
{
	return mRectangle.top;
}

template <typename T>
inline T Area<T>::getWidth() const noexcept
{
	return mRectangle.width;
}

template <typename T>
inline T Area<T>::getHeight() const noexcept
{
	return mRectangle.height;
}

template <typename T>
inline sf::Vector2<T> Area<T>::getSize() const noexcept
{
	return {mRectangle.width, mRectangle.height};
}

template <typename T>
inline const sf::Rect<T>& Area<T>::getRectangle() const noexcept
{
	return mRectangle;
}

template <typename T>
inline bool Area<T>::isContainsPoint(const T x, const T y) const noexcept
{
	return mRectangle.contains(x, y);
}

template <typename T>
inline bool Area<T>::isContainsPoint(const sf::Vector2<T>& point) const noexcept
{
	return mRectangle.contains(point);
}

template <typename T>
inline bool Area<T>::isIntersects(const Area<T>& area) const noexcept
{
	return mRectangle.intersects(area.mRectangle);
}

template <typename T>
inline bool Area<T>::isIntersects(const sf::Rect<T>& rectangle) const noexcept
{
	return mRectangle.intersects(rectangle);
}

using IntArea = Area<int>;
using FloatArea = Area<float>;
