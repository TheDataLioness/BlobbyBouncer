#pragma once



#include "collisionbox.h"
#include "surface.h"
#include "TileMap.h"
#include "timer.h"

namespace Blobbybouncer {

	class BRusher
	{
		public:
			BRusher(std::shared_ptr<Tmpl8::Sprite> sprite,Tmpl8::Surface* screen, float x, float y);

			vec2 GetPosition() { return position; }
			std::shared_ptr<CollisionBox> getCollisionBox() { return collisionBox; }
			void EntityTick(float deltaTime);
			vec2 GetMotion() { return motion; }
			std::shared_ptr<Tmpl8::Sprite> GetSprite() { return sprite; }
			void SetMotion(float x, float y) { motion.SetX(x); motion.SetY(y); }
			void SetPosition(vec2 pos) { position = pos; }
			void UpdateMap(std::shared_ptr<TileMap> map);

		private:
			std::shared_ptr<Tmpl8::Sprite> sprite;
			vec2 position;
			vec2 originPosition = vec2(0, 0);
			vec2 toPosition = vec2(0, 0);
			std::shared_ptr<TileMap> tileMap;
			Tmpl8::Surface* screen;
			std::shared_ptr<CollisionBox> collisionBox;

			vec2 motion = vec2(0, 0);
			vec2 lastMotion = vec2(0, 0);

			Tmpl8::Timer frameTimer = Tmpl8::Timer();

			int ticksAlive = 0;

			int facing = 0;
			int currentFrame = 0;

			int scale = 2;
			bool isOnGround = false;
			float velocity = 0.0;
			float acceleration = 0.3;

			void UpdateCollisionBox();
			void UpdateFrame();
			bool CheckCollisionBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t);
			bool CheckCollision(float x, float y);

			void kill();

	};

}

