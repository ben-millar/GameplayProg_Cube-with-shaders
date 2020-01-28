#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace gpp
{
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		/// <summary>
		/// Default constructor
		/// </summary>
		Vector3();

		/// <summary>
		/// Default destructor
		/// </summary>
		~Vector3();

		/// <summary>
		/// @brief Converts our 3D vectors to strings
		/// </summary>
		std::string toString();


		// Casting an SFML vector to Vector3 vector
		Vector3(float t_x, float t_y, float t_z) : x{ t_x }, y{ t_y }, z{ t_z } {}
		Vector3(sf::Vector3f t_sfVector);
		Vector3(sf::Vector3i t_sfVector);
		Vector3(sf::Vector2i t_sfVector);
		Vector3(sf::Vector2u t_sfVector);
		Vector3(sf::Vector2f t_sfVector);


		// OPERATOR OVERLOADS

		/// <summary>
		/// @brief Return value of LHS vector plus RHS vector
		/// </summary>
		Vector3 operator +(const Vector3 t_right) const;

		/// <summary>
		/// @brief Return value of LHS vector minus RHS vector
		/// </summary>
		Vector3 operator -(const Vector3 t_right) const;

		/// <summary>
		/// @brief Multiply vector by a given float scalar
		/// </summary>
		Vector3 operator *(const float t_scalar) const;

		/// <summary>
		/// @brief Return scalar/dot product of two vectors
		/// </summary>
		float operator *(const Vector3 t_right) const;

		/// <summary>
		/// @brief Return vector/cross product of two vectors
		/// </summary>
		Vector3 operator ^(const Vector3 t_right) const;

		/// <summary>
		/// @brief Divide vector by float divisor
		/// </summary>
		Vector3 operator /(const float t_divisor) const;

		/// <summary>
		/// @brief In-place addition of vectors
		/// </summary>
		void operator +=(const Vector3 t_right);

		/// <summary>
		/// @brief In-place subtraction of vectors
		/// </summary>
		void operator -=(const Vector3 t_right);

		/// <summary>
		/// @brief Check equality between vectors
		/// </summary>
		bool operator == (const Vector3 t_right) const;

		/// <summary>
		/// @brief Check inequality between vectors
		/// </summary>
		bool operator != (const Vector3 t_right) const;

		/// <summary>
		/// @brief Negate a vector
		/// </summary>
		Vector3 operator -();

		/// <summary>
		/// @brief Get the X component of a vector
		/// </summary>
		inline float getX() { return x; }

		/// <summary>
		/// @brief Get the Y component of a vector
		/// </summary>
		inline float getY() { return y; }

		/// <summary>
		/// @brief Get the Z component of a vector
		/// </summary>
		inline float getZ() { return z; }

		/// <summary>
		/// @brief Negate just the x-component of a vector
		/// </summary>
		void reverseX();

		/// <summary>
		/// @brief Negate just the y-component of a vector
		/// </summary>
		void reverseY();

		/// <summary>
		/// @brief Get the magnitude of a vector
		/// </summary>
		float length()const;

		/// <summary>
		/// @brief Get the squared magnitude of a vector
		/// </summary>
		/// <returns></returns>
		float lengthSquared()const;

		/// <summary>
		/// @brief Get the scalar/dot product of two vectors
		/// </summary>
		float dot(const Vector3 t_other) const;

		/// <summary>
		/// @brief Get the vector/cross product of two vectors
		/// </summary>
		Vector3 crossProduct(const Vector3 t_other)const;

		/// <summary>
		/// @brief Get the angle between two vectors
		/// </summary>
		float angleBetween(const Vector3 t_other)const;

		/// <summary>
		/// @brief Return the unit vector of a given vector
		/// </summary>
		Vector3 unit() const;

		/// <summary>
		/// @brief Normalise a vector to its unit vector
		/// </summary>
		void normalise();

		/// <summary>
		/// @brief Project a vector along a given vector
		/// </summary>
		Vector3 projection(const Vector3 t_onto)const;

		/// <summary>
		/// @brief Get vector rejection along a given vector
		/// </summary>
		/// <param name="t_onto"></param>
		/// <returns></returns>
		Vector3 rejection(const Vector3 t_onto)const;

		// Construct SFML vectors from our own vectors
		operator sf::Vector2f() { return sf::Vector2f{ static_cast<float>(x),static_cast<float>(y) }; }; // {2.4,-2.6,3.0} ->  {2.4~,-2.6~}
		operator sf::Vector2i() { return sf::Vector2i{ static_cast<int>(x),static_cast<int>(y) }; };// {2.4,-2.6,3.0} ->  {2,-3}
		operator sf::Vector2u();// {2.4,-2.6,3.0} ->  {2,3}  needs more space than an inline
		operator sf::Vector3i() { return sf::Vector3i{ static_cast<int>(x),static_cast<int>(y), static_cast<int>(z) }; };// {2.4,-2.6,3.0} ->  {2,-3,3}
		operator sf::Vector3f() { return sf::Vector3f{ static_cast<float>(x),static_cast<float>(y), static_cast<float>(z) }; };// {2.4,-2.6,3.0} ->  {2.4~,-2.6~, 3.0}
	};
}