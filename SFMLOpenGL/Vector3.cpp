#include "Vector3.h"

#define PI 3.14159265358979323846

using namespace gpp;

Vector3::Vector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}

///////////////////////////////////////////////////////////////////////

Vector3::~Vector3()
{
}

///////////////////////////////////////////////////////////////////////

std::string Vector3::toString()
{
	return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
}

///////////////////////////////////////////////////////////////////////

Vector3::Vector3(sf::Vector3f t_sfVector) :
	x{ t_sfVector.x },
	y{ t_sfVector.y },
	z{ t_sfVector.z }
{
}

///////////////////////////////////////////////////////////////////////

Vector3::Vector3(sf::Vector3i t_sfVector) :
	x{ static_cast<float>(t_sfVector.x) },
	y{ static_cast<float>(t_sfVector.y) },
	z{ static_cast<float>(t_sfVector.z) }
{
}

///////////////////////////////////////////////////////////////////////

Vector3::Vector3(sf::Vector2i t_sfVector) :
	x{ static_cast<float>(t_sfVector.x) },
	y{ static_cast<float>(t_sfVector.y) },
	z{ 0.0f }
{
}

///////////////////////////////////////////////////////////////////////

Vector3::Vector3(sf::Vector2u t_sfVector) :
	x{ static_cast<float>(t_sfVector.x) },
	y{ static_cast<float>(t_sfVector.y) },
	z{ 0.0f }
{
}

///////////////////////////////////////////////////////////////////////

Vector3::Vector3(sf::Vector2f t_sfVector) :
	x{ static_cast<float>(t_sfVector.x) },
	y{ static_cast<float>(t_sfVector.y) },
	z{ 0.0f }
{
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator+(const Vector3 t_right) const
{
	return Vector3(this->x + t_right.x, this->y + t_right.y, this->z + t_right.z);
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator-(const Vector3 t_right) const
{
	return Vector3(this->x - t_right.x, this->y - t_right.y, this->z - t_right.z);
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator*(const float t_scalar) const
{
	return Vector3(this->x * t_scalar, this->y * t_scalar, this->z * t_scalar);
}

///////////////////////////////////////////////////////////////////////

float Vector3::operator*(const Vector3 t_right) const
{
	return this->dot(t_right);
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator^(const Vector3 t_right) const
{
	return this->crossProduct(t_right);
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator/(const float t_divisor) const
{
	return (t_divisor == 0)
		? Vector3(0.0f, 0.0f, 0.0f)
		: Vector3(this->x / t_divisor, this->y / t_divisor, this->z / t_divisor);
}

///////////////////////////////////////////////////////////////////////

void Vector3::operator+=(const Vector3 t_right)
{
	this->x += t_right.x;
	this->y += t_right.y;
	this->z += t_right.z;
}

///////////////////////////////////////////////////////////////////////

void Vector3::operator-=(const Vector3 t_right)
{
	this->x -= t_right.x;
	this->y -= t_right.y;
	this->z -= t_right.z;
}

///////////////////////////////////////////////////////////////////////

bool Vector3::operator==(const Vector3 t_right) const
{
	return (this->x == t_right.x && this->y == t_right.y && this->z == t_right.z);
}

///////////////////////////////////////////////////////////////////////

bool Vector3::operator!=(const Vector3 t_right) const
{
	return (this->x != t_right.x || this->y != t_right.y || this->z != t_right.z);
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator-()
{
	return this->operator*(-1.0f);
}

///////////////////////////////////////////////////////////////////////

void Vector3::reverseX()
{
	this->x *= -1;
}

///////////////////////////////////////////////////////////////////////

void Vector3::reverseY()
{
	this->y *= -1;
}

///////////////////////////////////////////////////////////////////////

float Vector3::length() const
{
	return sqrt(this->lengthSquared());
}

///////////////////////////////////////////////////////////////////////

float Vector3::lengthSquared() const
{
	return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

///////////////////////////////////////////////////////////////////////

float Vector3::dot(const Vector3 t_other) const
{
	return (this->x * t_other.x) + (this->y * t_other.y) + (this->z * t_other.z);
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::crossProduct(const Vector3 t_other) const
{
	return Vector3((this->y * t_other.z) - (this->z * t_other.y), (this->z * t_other.x) - (this->x * t_other.z), (this->x * t_other.y) - (this->y * t_other.x));
}

///////////////////////////////////////////////////////////////////////

float Vector3::angleBetween(const Vector3 t_other) const
{
	Vector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	float angleBetween;
	float angleBetweenDegrees;

	float dotProduct = newVector.dot(t_other); // u . v
	float lengthProduct = newVector.length() * t_other.length(); // ||u||*||v||

	if (lengthProduct != 0) // avoid division by zero
	{
		angleBetween = acos(dotProduct / lengthProduct); // angle = cos ((u.v) / ||u|| * ||v||), .'. acos = answer.
		angleBetweenDegrees = angleBetween * (180 / PI); // convert result to degrees
	}
	else
	{
		angleBetweenDegrees = 0.0; // return null if vector length product is zero
	}

	return angleBetweenDegrees;
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::unit() const
{
	float magnitude = this->length();

	// don't divide by 0!
	return (magnitude > 0.0f) ? (*this / magnitude) : *this;
}

///////////////////////////////////////////////////////////////////////

void Vector3::normalise()
{
	float magnitude = this->length();

	// don't divide by 0!
	if (magnitude > 0.0f)* this = (*this / this->length());
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::projection(const Vector3 t_onto) const
{
	Vector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer
	Vector3 projection{ 0.0,0.0,0.0 };

	float dotProduct = newVector.dot(t_onto); // dot product of u and v
	float magnitude = t_onto.length(); // magnitude of v
	Vector3 unitVector = t_onto.unit(); // unit vector of v

	if (magnitude != 0)
	{
		projection = unitVector * (dotProduct / magnitude);
	}

	// will return null if magnitude is zero
	return projection;
}

///////////////////////////////////////////////////////////////////////

Vector3 Vector3::rejection(const Vector3 t_onto) const
{
	Vector3 newVector{ x,y,z }; // assigned values of left operand via 'this' pointer

	Vector3 rejection = newVector - newVector.projection(t_onto); // w = u - u1

	return rejection;
}

///////////////////////////////////////////////////////////////////////

Vector3::operator sf::Vector2u()
{
	Vector3 inputVector = { x,y,z }; // input vector
	sf::Vector2u sfv2u{}; // return vector

	// if either element is negative, make positive to avoid underflow error upon cast
	if (inputVector.x < 0) inputVector.x *= -1;
	if (inputVector.y < 0) inputVector.y *= -1;

	// cast and assign
	sfv2u.x = static_cast<unsigned>(inputVector.x);
	sfv2u.y = static_cast<unsigned>(inputVector.y);

	return sfv2u;
}
