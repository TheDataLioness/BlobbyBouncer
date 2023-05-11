#include "vector2.h"

#include <iostream>

namespace Blobbybouncer
{
	vec2::vec2(float posX, float posY) :
		posX(posX),
		posY(posY)
	{}

	vec2::vec2(int posX, int posY):
		posX(static_cast<float>(posX)),
		posY(static_cast<float>(posY))
	{}

	vec2::~vec2() {}

	vec2 vec2::SetX(float x)
	{
		posX = x;
		return *this;
	}

	vec2 vec2::SetY(float y)
	{
		posY = y;
		return *this;
	}

	vec2 vec2::Add(float x, float y)
	{
		posX += x;
		posY += y;
		return *this;
	}

	
	float vec2::DistanceSquared(vec2 vec)
	{
		return std::pow((posX - vec.GetX()), 2) + std::pow((posY - vec.GetX()), 2);
	}

	
	float vec2::Distance(vec2 vec)
	{
		return std::sqrtf(DistanceSquared(vec));
	}

	float vec2::LengthSquared()
	{
		return GetX() * GetX() + GetY() * GetY();
	}

	float vec2::Length()
	{
		return std::sqrtf(LengthSquared());
	}

	vec2 vec2::Normalize()
	{
		int len = Length();
		if(len > 0)
		{
			return *this / len;
		}
		return vec2(0, 0);
	}




	
}
