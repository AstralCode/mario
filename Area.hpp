#pragma once

#include "SFML/Graphics/Rect.hpp"

#include "Size.hpp"
#include "Point.hpp"

template <typename T>
class Area final
{
public:
	Area() = default;
	Area(const T x, const T y, const T width, const T height) noexcept;
	Area(const Point<T>& point, const Size<T>& size) noexcept;
	Area(const sf::Rect<T>& rectangle) noexcept;

	void set(const sf::Rect<T>& rectangle);

	void setPosition(const T x, const T y) noexcept;
	void setPosition(const Point<T>& point) noexcept;

	void setX(const T x) noexcept;
	void setY(const T y) noexcept;

	void setSize(const Size<T> size) noexcept;

	void setWidth(const T width) noexcept;
	void setHeight(const T height) noexcept;

	T getTop() const noexcept;
	T getLeft() const noexcept;
	T getRight() const noexcept;
	T getBottom() const noexcept;

	Point<T> getTopLeft() const noexcept;
	Point<T> getTopRight() const noexcept;
	Point<T> getBottomLeft() const noexcept;
	Point<T> getBottomRight() const noexcept;
	Point<T> getCenter() const noexcept;

	T getX() const noexcept;
	T getY() const noexcept;

	T getWidth() const noexcept;
	T getHeight() const noexcept;

	Size<T> getSize() const noexcept;

	const sf::Rect<T>& getRectangle() const noexcept;

	bool isContainsPoint(const T x, const T y) const noexcept;
	bool isContainsPoint(const Point<T>& point) const noexcept;

	bool isIntersects(const Area<T>& area) const noexcept;
	bool isIntersects(const sf::Rect<T>& rectangle) const noexcept;

private:
	sf::Rect<T> mRectangle;
};

template <typename T>
inline Area<T>::Area(const T x, const T y, const T width, const T height) noexcept :
	mRectangle{x, y, width, height}
{

}

template <typename T>
inline Area<T>::Area(const Point<T>& point, const Size<T>& size) noexcept :
	mRectangle{point.getX(), point.getY(), size.getWidth(), size.getHeight()}
{

}

template <typename T>
inline Area<T>::Area(const sf::Rect<T>& rectangle) noexcept :
	mRectangle{rectangle}
{

}

template <typename T>
inline void Area<T>::set(const sf::Rect<T>& rectangle)
{
	mRectangle = rectangle;
}

template <typename T>
inline void Area<T>::setPosition( const T x, const T y ) noexcept
{
	mRectangle.left = x;
	mRectangle.top = y;
}

template <typename T>
inline void Area<T>::setPosition(const Point<T>& point) noexcept
{
	mRectangle.left = point.getX();
	mRectangle.top = point.getY();
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

template <typename T>
inline void Area<T>::setSize(const Size<T> size) noexcept
{
	mRectangle.width = size.getWidth();
	mRectangle.height = size.getHeight();
}

template <typename T>
inline void Area<T>::setWidth(const T width) noexcept
{
	mRectangle.width = width;
}

template <typename T>
inline void Area<T>::setHeight(const T height) noexcept
{
	mRectangle.height = height;
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
inline Point<T> Area<T>::getTopLeft() const noexcept
{
	return {mRectangle.left, mRectangle.top};
}

template <typename T>
inline Point<T> Area<T>::getTopRight() const noexcept
{
	return {mRectangle.left + mRectangle.width, mRectangle.top};
}

template <typename T>
inline Point<T> Area<T>::getBottomLeft() const noexcept
{
	return {mRectangle.left, mRectangle.top + mRectangle.height};
}

template <typename T>
inline Point<T> Area<T>::getBottomRight() const noexcept
{
	return {mRectangle.left + mRectangle.width, mRectangle.top + mRectangle.height};
}

template <typename T>
inline Point<T> Area<T>::getCenter() const noexcept
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
inline Size<T> Area<T>::getSize() const noexcept
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
inline bool Area<T>::isContainsPoint(const Point<T>& point) const noexcept
{
	return mRectangle.contains(point.getX(), point.getY());
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
