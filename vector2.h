#pragma once
#include <complex>


namespace Blobbybouncer
{
	class vec2
	{
		public:

			vec2(float posX, float posY);
			vec2(int posX, int posY);
			~vec2();

			float GetX() { return posX; }
			int GetFloorX() { return static_cast<int>(posX); }
			float GetY() { return posY; }
			int GetFloorY() { return static_cast<int>(posY); }
			vec2 SetX(float x);
			vec2 SetX(int x) { return SetX(static_cast<float>(x)); };
			vec2 SetY(float y);
			vec2 SetY(int y) { return SetY(static_cast<float>(y)); };
			vec2 Add(float x = 0, float y = 0);
			vec2 Add(int x = 0, int y = 0) { return Add(static_cast<float>(x), static_cast<float>(y)); };
			vec2 Subtract(float x = 0, float y = 0) { return Add(-x, -y); };
			vec2 Subtract(int x = 0, int y = 0) { return Add(static_cast<float>(-x), static_cast<float>(-y)); };
			

			// Calculations MATH yay
			// Calculate distance between 2 vectors
			float DistanceSquared(vec2 vec);
			float Distance(vec2 vec);

			float LengthSquared();
			float Length();
			vec2 Normalize();
			
			// New operator logic
			vec2 operator + (vec2& other) const { return vec2(posX + other.GetX(), posY + other.GetY()); }
			vec2 operator - (vec2& other) const { return vec2(posX - other.GetX(), posY - other.GetY()); }
			vec2 operator / (vec2& other) const { return vec2(posX / other.GetX(), posY / other.GetY()); }
			vec2 operator * (vec2& other) const { return vec2(posX * other.GetX(), posY * other.GetY()); }

			vec2 operator * (float& other) const { return vec2(posX * other, posY * other); }
			vec2 operator / (float& other) const { return vec2(posX / other, posY / other); }

			vec2 operator * (int& other) const { return vec2(posX * other, posY * other); }
			vec2 operator / (int& other) const { return vec2(posX / other, posY / other); }

			bool operator == (vec2& other) const { return (posX == other.GetX() && posY == other.GetY()); }
			bool operator != (vec2& other) const { return (posX != other.GetX() || posY != other.GetY()); }

		private:
			float posX;
			float posY;
	};
	

}

