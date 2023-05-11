#pragma once
#include "vector2.h"

// DIRECTION FLAGS

namespace Blobbybouncer
{

	

	class CollisionBox
	{
		public:
			CollisionBox( vec2* vecOne, vec2* vecTwo );
			CollisionBox() { minX = 0; maxX = 0; minY = 0; maxY = 0; }

			// Size manipulation
			// DIRECTIONS:
			// 0 = TOP
			// 1 = BOTTOM
			// 2 = LEFT
			// 3 = RIGHT
			CollisionBox* Expand(float amount, int direction);
			CollisionBox* Expand(int amount, int direction) { return Expand(static_cast<float>(amount), direction); };

			CollisionBox* Contract(float amount, int direction) { return Expand(-amount, direction); }
			CollisionBox* Contract(int amount, int direction) { return Contract(static_cast<float>(amount), direction); }
			

			// Position manipulation
			CollisionBox* Offset(float x = 0, float y = 0);
			CollisionBox* Offset(int x = 0, int y = 0) { return Offset(static_cast<float>(x), static_cast<float>(y)); };


			// Collision detection
			bool IsColliding(CollisionBox collisionBox);
			bool IsColliding(vec2 vector);

			// Calculations
			float GetHeight();
			float GetWidth();
			float GetVolume() { return GetHeight()* GetWidth(); }

			float GetMinX() { return minX; }
			float GetMinY() { return minY; }
			float GetMaxX() { return maxX; }
			float GetMaxY() { return maxY; }
		
	
		private:
			float minX;
			float minY;
			float maxX;
			float maxY;


	};
}

