#pragma once

#include <cmath>

#include "SFML/System/Vector2.hpp"

template <typename T>
class Point final
{
public:
	Point() noexcept;
	Point(const T x, const T y) noexcept;
	Point(const sf::Vector2<T>& point) noexcept;

	void set(const T x, const T y) noexcept;
	void set(const sf::Vector2<T>& point) noexcept;

	void setX(const T x) noexcept;
	void setY(const T y) noexcept;

	float distance(const Point& point) const noexcept;

	template <typename U>
	Point<U> cast() const noexcept;

	T& getX() noexcept;
	T& getY() noexcept;

	T getX() const noexcept;
	T getY() const noexcept;

	sf::Vector2<T> getVector() const noexcept;

	Point<T> operator-() const noexcept;

private:
	sf::Vector2<T> mPoint;
};

template <typename T>
inline Point<T>::Point() noexcept :
	mPoint{}
{

}

template <typename T>
inline Point<T>::Point(const T x, const T y) noexcept :
	mPoint{x, y}
{

}

template <typename T>
inline Point<T>::Point(const sf::Vector2<T>& point) noexcept :
	mPoint{point}
{

}

template <typename T>
inline void Point<T>::set(const T x, const T y) noexcept
{
	mPoint.x = x;
	mPoint.y = y;
}

template <typename T>
inline void Point<T>::set(const sf::Vector2<T>& point) noexcept
{
	mPoint = point;
}

template <typename T>
inline void Point<T>::setX(const T x) noexcept
{
	mPoint.x = x;
}

template <typename T>
inline void Point<T>::setY(const T y) noexcept
{
	mPoint.y = y;
}

template <typename T>
inline float Point<T>::distance(const Point& point) const noexcept
{
	const auto x = point.getX() - mPoint.x;
	const auto y = point.getY() - mPoint.y;

	return std::sqrt(x * x + y * y);
}

template<typename T>
template<typename U>
inline Point<U> Point<T>::cast() const noexcept
{
	return Point<U>{static_cast<U>(mPoint.x), static_cast<U>(mPoint.y)};
}

template <typename T>
inline T& Point<T>::getX() noexcept
{
	return mPoint.x;
}

template <typename T>
inline T& Point<T>::getY() noexcept
{
	return mPoint.y;
}

template <typename T>
inline T Point<T>::getX() const noexcept
{
	return mPoint.x;
}

template <typename T>
inline T Point<T>::getY() const noexcept
{
	return mPoint.y;
}

template <typename T>
inline sf::Vector2<T> Point<T>::getVector() const noexcept
{
	return mPoint;
}

template <typename T>
Point<T> Point<T>::operator-() const noexcept
{
	return -mPoint;
}

using IntPoint = Point<int>;
using FloatPoint = Point<float>;
