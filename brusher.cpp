#include "brusher.h"
#include "timer.h"
#include "vector2.h"
#include <numeric>


namespace Blobbybouncer
{
	BRusher::BRusher(std::shared_ptr<Tmpl8::Sprite> sprite, Tmpl8::Surface* screen, float x, float y) :
		sprite(sprite),
		screen(screen),
		position(vec2(x, y)),
		originPosition(vec2(x, y)),
		toPosition(vec2(x - 64, y))
	{
		vec2* maxVector = new vec2(position.GetX() + (sprite->GetWidth() * scale), position.GetY() + (sprite->GetHeight() * scale));
		collisionBox = std::make_shared<CollisionBox>(&position, maxVector);
		delete(maxVector);

		// Sprite size is a bit bigger than actual Blobby
		collisionBox->Contract(12, 0);
		collisionBox->Contract(5, 1);
		collisionBox->Contract(8, 2);
		collisionBox->Contract(8, 3);
	}

	void BRusher::UpdateMap(std::shared_ptr<TileMap> map) {
		tileMap = map;
	}

	void BRusher::EntityTick(float deltaTime)
	{

		if (motion.GetX() != 0) {
			facing = motion.GetX() > 0;
			if (velocity > 0 && isOnGround) velocity = 0;
		}

		UpdateFrame();

		// Apply motion to position
		position = position + motion;

		// Making Sure player can't get out of the screen
		if (position.GetY() - sprite->GetHeight() * scale < 0) {
			position.SetY(static_cast<float>(sprite->GetHeight() * scale));
		}
		if (position.GetFloorX() < 0) position.SetX(0);

		lastMotion = motion;
		motion.SetX(0);
		motion.SetY(0);

		sprite->DrawScaled(position.GetFloorX(), position.GetFloorY(), sprite->GetWidth() * scale, sprite->GetHeight() * scale, screen);

		ticksAlive++;

		motion.Add(static_cast<float>(std::sin(ticksAlive * 0.01)));

		UpdateCollisionBox();

		// Gravity magic
		if (velocity < 8 && !isOnGround) velocity += acceleration;

		motion = motion.Add(0.0f, velocity);

		// A big collision detection code for all kinds of collisions
		float minX = std::floor(collisionBox->GetMinX() + motion.GetX());
		float maxX = std::ceil(collisionBox->GetMaxX() + motion.GetX());
		float minY = std::floor(collisionBox->GetMinY() + motion.GetFloorY());
		float maxY = std::ceil(collisionBox->GetMaxY() + motion.GetFloorY());

		// All collision corners
		Blobbybouncer::vec2 l_t(minX, minY);
		Blobbybouncer::vec2 l_b(minX, maxY);
		Blobbybouncer::vec2 r_t(maxX, minY);
		Blobbybouncer::vec2 r_b(maxX, maxY);


		while (CheckCollisionBetween(l_t, l_b) && motion.GetX() < 0) {
				motion.Add(1, 0);
				l_t.Add(1, 0);
				l_b.Add(1, 0);
		}

		while (CheckCollisionBetween(r_t, r_b) && motion.GetX() > 0) {
				motion.Subtract(1, 0);
				r_t.Subtract(1, 0);
				r_b.Subtract(1, 0);
		}

		// Collision for top of B-Rusher so it will stop at ceilings
		if (CheckCollisionBetween(l_t, r_t) && motion.GetY() < 0) {
			if (velocity < 0) velocity = 0;
		}

		if (CheckCollisionBetween(l_b, r_b) && motion.GetY() > 0) {
			if (CheckCollisionBetween(l_b.Subtract(0, 1), r_b.Subtract(0, 1))) {
				motion.SetY(-1);
			}
			else {
				motion.SetY(0);
			}

			isOnGround = true;
		}
		else {
			if (velocity >= 10 && isOnGround) velocity = 0;
			isOnGround = false;
		}

	}

	void BRusher::UpdateCollisionBox()
	{
		collisionBox->Expand(12, 0);
		collisionBox->Expand(5, 1);
		collisionBox->Expand(8, 2);
		collisionBox->Expand(8, 3);
		collisionBox->Offset(position.GetX() - collisionBox->GetMinX(), position.GetY() - collisionBox->GetMinY());
		collisionBox->Contract(12, 0);
		collisionBox->Contract(5, 1);
		collisionBox->Contract(8, 2);
		collisionBox->Contract(8, 3);
	}

	void BRusher::UpdateFrame()
	{
		frameTimer.tick();
		if ((frameTimer.totalSeconds() > 0.25)) {

			currentFrame++;
			if (currentFrame >= 4) currentFrame = 0;

			if (facing == 0) {
				sprite->SetFrame(currentFrame);
			}
			else if (facing == 1) {
				sprite->SetFrame(currentFrame + 4);
			}
			frameTimer.reset();
		}
	}

	bool BRusher::CheckCollision(float x, float y)
	{

		// These tiles are all solid
		char solids[8] = { 'B', 'S', 'D', 'L', 'H', 'T', 'U' };
		bool collision = false;
		for (int i = 0; i < 7; i++)
		{
			if (tileMap->CheckForChar(x, y, solids[i]))
			{
				collision = true;
				break;
			}

		}

		return collision;
	}

	bool BRusher::CheckCollisionBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t) {

		// These tiles are all solid
		char solids[8] = { 'B', 'S', 'D', 'L', 'H', 'T', 'U' };
		bool collision = false;
		for (int i = 0; i < 7; i++)
		{
			if (tileMap->CheckCharBetween(pos, pos_t, solids[i])) {
				collision = true;
				break;
			}
		}

		return collision;
	}
}