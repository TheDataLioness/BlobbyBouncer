#include "player.h"
#include <windows.h>
#include <iostream>
#include <xinput.h>
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")


namespace Blobbybouncer {

	Player::Player(std::shared_ptr<Tmpl8::Sprite> playerSprite, Tmpl8::Surface* screen, float x, float y) :
		playerSprite(playerSprite),
		screen(screen),
		position(vec2(x, y))
	{
		vec2* maxVector = new vec2(position.GetX() + (playerSprite->GetWidth() * scale), position.GetY() + (playerSprite->GetHeight() * scale));
		collisionBox = std::make_shared<CollisionBox>(&position, maxVector);
		delete(maxVector);

		// Sprite size is a bit bigger than actual Blobby
		collisionBox->Contract(12, 0);
		collisionBox->Contract(5, 1);
		collisionBox->Contract(8, 2);
		collisionBox->Contract(8, 3);
	}

	void Player::UpdateMap(std::shared_ptr<TileMap> map) {
		tileMap = map;
	}

	void Player::EntityTick(float deltaTime)
	{
		bool instantFrameUpdate = false;
		if (motion.GetX() != 0) {
			facing = motion.GetX() > 0;
			instantFrameUpdate = true;
			if (velocity > 0 && isOnGround) 
			{
				velocity = -2;

				if (!blobbyJump.isPlaying() && bounce == 0) {
					blobbyJump.setPitch(2);
					blobbyJump.setVolume(0.05);
					blobbyJump.replay();
				}

			}
		}

		UpdateFrame(instantFrameUpdate);

		// Apply motion to position
		position = position + motion;
		
		// Making Sure player can't get out of the screen
		if (position.GetY() < 0) {
			position.SetY(0);
		}
		if (position.GetFloorX() < 0) position.SetX(0);

		lastMotion = motion;
		motion.SetX(0);
		motion.SetY(0);

		playerSprite->DrawScaled(position.GetFloorX(), position.GetFloorY(), playerSprite->GetWidth() * scale, playerSprite->GetHeight() * scale, screen);

		// Controller support
		// SOURCE: Microsoft Documents
		// https://learn.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput?source=recommendations
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		XInputGetState(0, &state);
		float LX = state.Gamepad.sThumbLX;
		float LY = state.Gamepad.sThumbLY;
		bool jumpButton = state.Gamepad.wButtons == XINPUT_GAMEPAD_A;

		UpdateCollisionBox();

		//determine how far the controller is pushed
		float magnitude = sqrt(LX * LX + LY * LY);

		//determine the direction the controller is pushed
		float normalizedLX = LX / magnitude;

		float m_X = 0;
		float m_Y = 0;
		if (!bounceOffWall) {
			if (!hasSpaceClicked) {
				if (GetAsyncKeyState(VK_LEFT) || (normalizedLX < 0 && normalizedLX != false)) {
					float moveSpeed = justJumped ? 3.0f : 2.0f;
					if (normalizedLX < 0 && normalizedLX != false && !GetAsyncKeyState(VK_LEFT)) moveSpeed *= magnitude / 32767;

					m_X -= moveSpeed;
				}

				if (GetAsyncKeyState(VK_RIGHT) || normalizedLX > 0) {
					float moveSpeed = justJumped ? 3.0f : 2.0f;
					if (normalizedLX > 0) moveSpeed *= magnitude / 32767;

					m_X += moveSpeed;
				}
			}
		}
		else {
			motion.SetX(lastMotion.GetX());
		}
		
		// Jump key handling
		if(!hasSpaceClicked && (GetAsyncKeyState(VK_SPACE) && (isOnGround || stickToWall) || jumpButton)){
			hasSpaceClicked = true;
		}

		if (isOnGround && bounce > 0) {
			velocity = static_cast<float>(-bounce);
			bounce--;
			if (!blobbyJump.isPlaying()) {
				blobbyJump.setPitch(1.5);
				blobbyJump.setVolume(0.1);
				blobbyJump.replay();
			}
		}

		if (hasSpaceClicked && (!GetAsyncKeyState(VK_SPACE) && !jumpButton && (isOnGround || stickToWall))) {

			velocity = -5;
			bounce = 4;
			
			justJumped = true;
			hasSpaceClicked = false;

			blobbyJump.setPitch(1);
			blobbyJump.setVolume(0.1);
			blobbyJump.replay();
		}

		// Gravity magic
		if (velocity < 8 && !isOnGround && !stickToWall) velocity += acceleration;

		m_Y += velocity;
		motion = motion.Add(m_X, m_Y);

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

		stickToWall = false;

		while (CheckCollisionBetween(l_t, l_b) && motion.GetX() < 0) {
			
			if (tileMap->CheckCharBetween(l_t, l_b, 'H')) {
				// BOUNCY LEFT WALL
				float wallBounce = static_cast<float>(std::abs(lastMotion.GetX()) * 1.5 + 1);
				motion.Add(wallBounce);
				l_t.Add(wallBounce);
				l_b.Add(wallBounce);
				bounce = 3;
				bounceOffWall = true;
				velocity = static_cast<float>(lastMotion.GetY() * 1.5);
			}
			else if (tileMap->CheckCharBetween(l_t, l_b, 'U')) {
				// STICKY WALL LEFT
				bounce = 0;
				if (motion.GetX() < 0) velocity = -1;
				stickToWall = true;
				justJumped = false;
				motion.Add(1, 0);
				l_t.Add(1, 0);
				l_b.Add(1, 0);

				if (!blobbyClimb.isPlaying()) {
					blobbyClimb.setVolume(0.1);
					blobbyClimb.replay();
				}
			}
			else{
				motion.Add(1, 0);
				l_t.Add(1, 0);
				l_b.Add(1, 0);
			}
			
		}

		while (CheckCollisionBetween(r_t, r_b) && motion.GetX() > 0) {
			if (tileMap->CheckCharBetween(r_t, r_b, 'L')) 
			{
				// BOUNCY RIGHT WALL
				float wallBounce = static_cast<float>(std::abs(lastMotion.GetX()) * 1.5 + 1);
				motion.Subtract(wallBounce);
				l_t.Subtract(wallBounce);
				l_b.Subtract(wallBounce);
				bounce = 3;
				bounceOffWall = true;
				velocity = static_cast<float>(lastMotion.GetY() * 1.5);
			}
			else if (tileMap->CheckCharBetween(r_t, r_b, 'T')) {
				// STICKY WALL RIGHT
				bounce = 0;
				if (motion.GetX() > 0) velocity = -1;
				stickToWall = true;
				justJumped = false;
				motion.Subtract(1, 0);
				r_t.Subtract(1, 0);
				r_b.Subtract(1, 0);
				if (!blobbyClimb.isPlaying()) {
					blobbyClimb.setVolume(0.1);
					blobbyClimb.replay();
				}
			}
			else {
				motion.Subtract(1, 0);
				r_t.Subtract(1, 0);
				r_b.Subtract(1, 0);
			}
			
		}

		// Collision for top of Blobby so it will stop at ceilings
		if(CheckCollisionBetween(l_t, r_t) && motion.GetY() < 0) {
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
			justJumped = false;
			bounceOffWall = false;
		}
		else {
			if (velocity >= 10 && isOnGround) velocity = 0;
			isOnGround = false;
		}

		// BOUNCE ON FLOOR
		if (tileMap->CheckCharBetween(l_b, r_b, 'B') && isOnGround && (bounce > 0 || velocity > 3)) {
			bounce = 7;
			justJumped = true;


			blobbyJump.setPitch(0.5);
			blobbyJump.setVolume(0.1);
			blobbyJump.replay();
		}

		// DEATH
		if (tileMap->CheckCharBetween(l_b, r_b, 'D')) {
			Death();

			blobbyDead.setPitch(1.5);
			blobbyDead.setVolume(0.5);
			blobbyDead.replay();
		}
		
		// NEW LEVEL
		if (tileMap->CheckCharBetween(l_b, r_b, 'N')) {
			// NEXT LEVEL CALCULATION
			int level = tileMap->GetLevel();
			int stage = tileMap->GetStage();
			if (stage <= 3) { stage++; }
			if (stage > 3) { stage = 0; level++; levelCompleted = true; }
			if (level >= 4) { level = 0; stage = 0; }
			tileMap->SetStage(level, stage);

			Reset();
		}

		// KONAMI UPDATE
		if (konamiCompleted) status->CompleteKonami();
		status->TickUpdate();

	}

	void Player::Death()
	{
		position = vec2(tileMap->GetSpawn().GetX(), tileMap->GetSpawn().GetY());
		motion = vec2(0, 0);
		status->Damage();

		if (status->GetHealth() == 0) {
			int level = tileMap->GetLevel();
			tileMap->SetStage(level, 0);
			status->Reset();

			Reset();
		}
	}

	void Player::Reset()
	{
		// First map tick to find spawnpoint
		tileMap->MapTick(screen);
		position = vec2(tileMap->GetSpawn().GetX(), tileMap->GetSpawn().GetY());
		motion = vec2(0, 0);
		lastMotion = vec2(0, 0);

		hasSpaceClicked = false;
		isOnGround = false;
		justJumped = false;
		bounce = 0;
		velocity = 0.0;
		acceleration = 0.3;
		bounceOffWall = false;
		stickToWall = false;
	}

	void Player::UpdateCollisionBox()
	{
		// Because we move the CollisionBox around we need to reset it real quick to the original sizes and set the position agian properly every tick
		collisionBox->Expand(5, 1);
		collisionBox->Expand(12, 0);
		collisionBox->Expand(8, 2);
		collisionBox->Expand(8, 3);
		collisionBox->Offset(position.GetX() - collisionBox->GetMinX(), position.GetY() - collisionBox->GetMinY());
		collisionBox->Contract(12, 0);
		collisionBox->Contract(5, 1);
		collisionBox->Contract(8, 2);
		collisionBox->Contract(8, 3);
	}

	void Player::UpdateFrame(bool instantFrameUpdate)
	{

		// Idle Frames
		frameTimer.tick();
		if ((frameTimer.totalSeconds() > 0.5 || instantFrameUpdate) && !justJumped) {
			if (facing == 1) {
				playerSprite->SetFrame(currentFrame == 1 ? 0 : 1);
			}
			else if (facing == 0) {
				playerSprite->SetFrame(currentFrame == 1 ? 4 : 5);
			}

			if (!instantFrameUpdate || frameTimer.totalSeconds() > 0.5) {
				currentFrame = currentFrame == 1 ? 0 : 1;
				frameTimer.reset();
			}
		}

		// Jump in the air frame
		if (justJumped) {
			playerSprite->SetFrame(facing == 1 ? 2 : 6);
			
		}

		// Jump "charge" frame
		if (hasSpaceClicked && bounce == 0) {
			playerSprite->SetFrame(facing == 1 ? 3 : 7);
		}
	}

	bool Player::CheckCollision(int x, int y)
	{

		// These tiles are all solid
		char solids[8] = { 'B', 'S', 'D', 'L', 'H', 'T', 'U'};
		bool collision = false;
		for (int i=0;i<7;i++) 
		{
			if (tileMap->CheckForChar(x, y, solids[i])) 
			{
				collision = true; 
				break;
			}
			
		}

		return collision;
	} 

	bool Player::CheckCollisionBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t) {

		// These tiles are all solid
		char solids[8] = { 'B', 'S', 'D', 'L', 'H', 'T', 'U'};
		bool collision = false;
		for (int i=0;i<7;i++) 
		{
			if (tileMap->CheckCharBetween(pos, pos_t, solids[i])) { 
				collision = true; 
				break; 
			}
		}

		return collision;
	}
};