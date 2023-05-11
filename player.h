#pragma once


#include <Audio/Sound.hpp>
#include <Audio/Device.hpp>

#include <iostream>
#include <windows.h>

#include "collisionbox.h"
#include "surface.h"
#include "timer.h"
#include "TileMap.h"
#include "playerstatus.h"


namespace Blobbybouncer
{

	class Player
	{
		public:
			Player(std::shared_ptr<Tmpl8::Sprite> playerSprite, Tmpl8::Surface* screen, float x, float y);

			vec2 GetPosition() { return position; }
			std::shared_ptr<CollisionBox> getCollisionBox() { return collisionBox; }

			vec2 GetMotion() { return motion; }
			std::shared_ptr <Tmpl8::Sprite> GetSprite() { return playerSprite; }
			void SetMotion(float x, float y) { motion.SetX(x); motion.SetY(y); }
			void EntityTick(float deltaTime);
			void UpdateMap(std::shared_ptr<TileMap> map);
			void Death();
			void Reset();
			std::shared_ptr<PlayerStatus> GetPlayerStatus() { return status; };

			void CompleteKonami() { konamiCompleted = true; };

			void TimeSubmitted() { levelCompleted = false; };
			bool hasLevelCompleted() { return levelCompleted; };

		private:
			
			std::shared_ptr<Tmpl8::Sprite> playerSprite;
			vec2 position;
			std::shared_ptr<TileMap> tileMap;
			Tmpl8::Surface* screen;
			std::shared_ptr<CollisionBox> collisionBox;

			vec2 motion = vec2(0, 0);
			vec2 lastMotion = vec2(0, 0);

			Tmpl8::Timer frameTimer = Tmpl8::Timer();

			int facing = 0;
			int currentFrame = 0;

			int scale = 2;

			bool hasSpaceClicked = false;
			bool isOnGround = false;
			bool justJumped = false;
			int bounce = 0;
			float velocity = 0.0;
			float acceleration = 0.3;
			bool bounceOffWall = false;
			bool stickToWall = false;
			bool levelCompleted = false;

			std::shared_ptr<PlayerStatus> status = std::make_shared<PlayerStatus>(screen);
			Audio::Sound blobbyJump = Audio::Device::loadSound("assets/audio/sfx/blobby_jump.wav");
			Audio::Sound blobbyDead = Audio::Device::loadSound("assets/audio/sfx/blobby_dead.wav");
			Audio::Sound blobbyClimb = Audio::Device::loadSound("assets/audio/sfx/blobby_climb.wav");

			bool konamiCompleted = false;

			void UpdateCollisionBox();
			void UpdateFrame(bool instantFrameUpdate);
			bool CheckCollisionBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t);
			bool CheckCollision(int x, int y);
 	};

}
