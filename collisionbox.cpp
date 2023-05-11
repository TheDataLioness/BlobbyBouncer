#include "collisionbox.h"

#include <algorithm>
#include "vector2.h"

namespace Blobbybouncer
{

	CollisionBox::CollisionBox(vec2* vecOne, vec2* vecTwo):
		minX(std::min(vecOne->GetFloorX(), vecTwo->GetFloorX())),
		minY(std::min(vecOne->GetFloorY(), vecTwo->GetFloorY())),
		maxX(std::max(vecOne->GetFloorX(), vecTwo->GetFloorX())),
		maxY(std::max(vecOne->GetFloorY(), vecTwo->GetFloorY()))
	{}

	CollisionBox* CollisionBox::Offset(float x, float y) {
		minX += x;
		minY += y;
		maxX += x;
		maxY += y;
		return this;
	}

	CollisionBox* CollisionBox::Expand(float amount, int direction) {
		if (direction == 0) minY -= amount;
		if (direction == 1) maxY += amount;
		if (direction == 2) minX -= amount;
		if (direction == 3) maxX += amount;
		return this;
	}

	bool CollisionBox::IsColliding(CollisionBox collisionBox) {
		if (collisionBox.GetMaxX() - minX > 0.0001f && maxX - collisionBox.GetMinX() > 0.0001f) {
			if (collisionBox.GetMinY() - minY > 0.0001f && GetMinY() - collisionBox.GetMinY() > 0.00001f) {
				return true;
			}
		}
		return false;
	}

	bool CollisionBox::IsColliding(vec2 vector) {
		if (vector.GetFloorX() <= minX || vector.GetFloorX() >= maxX) {
			return false;
		}
		if (vector.GetFloorY() <= minY || vector.GetFloorY() >= maxY) {
			return false;
		}

		return true;
	}
	
}
