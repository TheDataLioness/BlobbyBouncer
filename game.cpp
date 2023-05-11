#include "game.h"

#include <cstdio>
#include <iostream>
#include <windows.h>
#include <Audio/sound.hpp>
#include <direct.h>
#include <SDL.h>

#include "surface.h"
#include "TileMap.h"
#include "Timer.h"
#include "vector2.h"
#include "player.h"
#include "button.h"
#include "brusher.h"


namespace Tmpl8
{

	char* tilesPath = "assets/map_tiles.png";
	std::shared_ptr<Blobbybouncer::TileMap> tileMap = std::make_shared<Blobbybouncer::TileMap>(std::make_shared<Surface>(tilesPath), 32);
	std::shared_ptr<Sprite> playerSprite = std::make_shared<Sprite>(new Surface("assets/Blobby/blobby_idle.png"), 8);
	std::shared_ptr<Blobbybouncer::Player> player;
	std::shared_ptr<Sprite> bRusherSprite = std::make_shared<Sprite>(new Surface("assets/B-Rusher/B-Rusher.png"), 8);
	std::shared_ptr<Blobbybouncer::BRusher> bRusher;
	std::shared_ptr<Sprite> title = std::make_shared<Sprite>(new Surface("assets/ui/title.png"), 3);

	Surface background("assets/ui/background.png");

	void Game::Init()
	{

		// Obtain game stats
		/*
		/	Thx Lynn <3 for I/O
		/	https://github.com/NamespaceLynn/Coal-Critters/blob/bae0c5d503d5d22f291bf5222a6d8b6f09a0d244/game.cpp#L79
		*/
		stats.open("stats.txt", fstream::in);
		if (stats.is_open())
		{
			std::string line;
			int lines = 0;
			while (std::getline(stats, line))
			{
				lines++;
				switch (lines) {
					case 1:
						fastestTimeOne = static_cast<float>(::atof(line.c_str()));
						break;
					case 2:
						fastestTimeTwo = static_cast<float>(::atof(line.c_str()));
						break;
					case 3:
						fastestTimeThree = static_cast<float>(::atof(line.c_str()));
						break;
					case 4:
						unlockedLevel = static_cast<float>(::atof(line.c_str()));
						break;
				}
			}
			stats.close();
		}
		stats.open("stats.txt", fstream::out);
		if (stats.is_open())
		{
			stats << fastestTimeOne << std::endl;
			stats << fastestTimeTwo << std::endl;
			stats << fastestTimeThree << std::endl;
			stats << unlockedLevel << std::endl;
			stats.close();
		}

		bRusher = std::make_shared<Blobbybouncer::BRusher>(bRusherSprite, screen, 128, 200);
		bRusher->UpdateMap(tileMap);

		// Initial tick needed for spawnpoint
		tileMap->MapTick(screen);
		player = std::make_shared<Blobbybouncer::Player>(playerSprite, screen, tileMap->GetSpawn().GetX(), tileMap->GetSpawn().GetY());
		player->UpdateMap(tileMap);
	}

	void Game::Shutdown()
	{
		stats.open("stats.txt", fstream::out);
		if (stats.is_open())
		{
			stats << fastestTimeOne;
			stats << fastestTimeTwo;
			stats << fastestTimeThree;
			stats << unlockedLevel;
			stats.close();
		}
	}

	void Game::Quit() {

		mainTheme.stop();

		/* Invoke an event with the type SDL_QUIT */
		SDL_Event user_event;
		user_event.type = SDL_QUIT;
		SDL_PushEvent(&user_event);
	}

	void Game::Tick(float deltaTime)
	{
		// Clear Screen with blue sky color
		screen->Clear(6420479);
		
		if (gameState == GameState::IN_GAME) {
			if (!mainTheme.isPlaying()) {

				mainTheme.setVolume(0.25);
				mainTheme.setLooping(true);
				mainTheme.play();
				
			}
		}
		else {
			if (mainTheme.isPlaying()) {
				mainTheme.stop();
			}
		}
		

		if (gameState == GameState::MAIN_MENU) 
		{
			// SCREEN TITLE
			titleTimer.tick();
			Blobbybouncer::vec2 titlePos(screen->GetWidth() / 2 - (title->GetWidth() * 2 / 2), 0);
			if (titleTimer.totalSeconds() > 0.5) {
				if (titleBack) {
					titleFrame--;
					if (titleFrame == 0) {
						titleBack = false;
					}
				}
				else {
					titleFrame++;
					if (titleFrame == 2) {
						titleBack = true;
					}
				}
				titleTimer.reset();
			}
			title->SetFrame(titleFrame);
			title->DrawScaled(titlePos.GetFloorX(), titlePos.GetFloorY(), title->GetWidth() * 2, title->GetHeight() * 2, screen);

			int scale = 4;
			Blobbybouncer::vec2 pos = Blobbybouncer::vec2(screen->GetWidth() / 2 - (24 * scale), 280);

			// PLAY BUTTON
			playButton.Init(pos, scale, screen);
			playButton.UpdateMousePos(mousePos);
			if (playButton.click() && justClicked) {
				gameState = GameState::IN_GAME;
			}

			pos.Add(0, (16 * scale) + 10);

			// LEVELS BUTTON
			levelsButton.Init(pos, scale, screen);
			levelsButton.UpdateMousePos(mousePos);
			if (levelsButton.click() && justClicked) {
				gameState = GameState::LEVELS;
			}

			pos.Add(0, (16 * scale) + 10);

			// QUIT BUTTON
			quitButton.Init(pos, scale, screen);
			quitButton.UpdateMousePos(mousePos);
			if (quitButton.click() && justClicked) {
				Game::Quit();
			}

			// Credits BUTTON
			creditsButton.Init(Blobbybouncer::vec2(screen->GetWidth() - 32 * scale, screen->GetHeight() - 16 * scale), 2, screen);
			creditsButton.UpdateMousePos(mousePos);
			if (creditsButton.click() && justClicked) {
				gameState = GameState::CREDITS;
			}
		}
		if (gameState == GameState::IN_GAME) {
			
			background.CopyTo(screen, 0, 0);

			// Tick Map
			tileMap->MapTick(screen);

			// Player ticking logic happens in player class
			player->EntityTick(deltaTime);
			player->UpdateMap(tileMap);

			if (!bRusherSpawned) {
				bRusherSpawned = true;
				bRusher->SetPosition(tileMap->GetBRusherSpawn());
			}

			if (tileMap->GetBRusherSpawn().GetFloorX() > 0 && tileMap->GetBRusherSpawn().GetFloorY() > 0) {
				std::shared_ptr<Blobbybouncer::CollisionBox> bRusherBox = bRusher->getCollisionBox();
				std::shared_ptr<Blobbybouncer::CollisionBox> playerBox = player->getCollisionBox();

				if (playerBox->GetMaxX() - bRusherBox->GetMinX() > 0.0001f && bRusherBox->GetMaxX() - playerBox->GetMinX() > 0.0001f) {
					if (playerBox->GetMaxY() - bRusherBox->GetMinY() > 0.0001f && playerBox->GetMaxY() - playerBox->GetMinY() > 0.00001f) {
						player->Death();
					}
				}


				bRusher->EntityTick(deltaTime);
				bRusher->UpdateMap(tileMap);
			}

			
			elapsedGameTime += gameTimer.elapsedSeconds();
			
			// SAVE HIGHEST SCORE
			if (player->hasLevelCompleted()) {
				player->TimeSubmitted();
				int levelToSave = tileMap->GetLevel() - 1;
				switch (levelToSave) {
					case 0:
						if (fastestTimeOne > elapsedGameTime) {
							fastestTimeOne = elapsedGameTime;
						}
						break;
					case 1:
						if (fastestTimeTwo > elapsedGameTime) {
							fastestTimeTwo = elapsedGameTime;
						}
						break;
					case 2:
						if (fastestTimeThree > elapsedGameTime) {
							fastestTimeThree = elapsedGameTime;
						}
						break;
				}
			}

			// TIME READABLE FOR HUMANS
			int minutes = static_cast<int>(elapsedGameTime / 60);
			int seconds = static_cast<int>(elapsedGameTime) % 60;
			int milliSeconds = (elapsedGameTime - static_cast<int>(elapsedGameTime)) * 1000;

			std::ostringstream time;
			time << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << ":" << std::setw(3) << std::setfill('0') << milliSeconds << " | Level: " << tileMap->GetLevel() << "-" << tileMap->GetStage();

			screen->Print(time.str().c_str(), screen->GetWidth() / 2, 10, 0, 3);


			if (player->GetPlayerStatus()->GetHealth() <= 0) {
				elapsedGameTime = 0;
				bRusherSpawned = false;
				bRusher->SetPosition(Blobbybouncer::vec2(0, 0));
			}

			if (unlockedLevel < tileMap->GetLevel()) {
				unlockedLevel = tileMap->GetLevel();
			}

		}
		if (gameState == GameState::PAUSE) { 
			background.CopyTo(screen, 0, 0);
			tileMap->MapTick(screen);

			int scale = 4;
			Blobbybouncer::vec2 pos = Blobbybouncer::vec2(screen->GetWidth() / 2 - (24 * scale), 150);

			// RETRY BUTTON
			retryButton.Init(pos, scale, screen);
			retryButton.UpdateMousePos(mousePos);
			if (retryButton.click() && justClicked) {
				gameState = GameState::IN_GAME;
				tileMap->SetStage(tileMap->GetLevel(), 0);
				player->Reset();
			}

			pos.Add(0, (16 * scale) + 10);

			// MENU BUTTON
			menuButton.Init(pos, scale, screen);
			menuButton.UpdateMousePos(mousePos);
			if (menuButton.click() && justClicked) {
				gameState = GameState::MAIN_MENU;
				tileMap->SetStage(0, 0);
				player->Reset();
			}

			pos.Add(0, (16 * scale) + 10);

			// BACK BUTTON
			backButton.Init(pos, scale, screen);
			backButton.UpdateMousePos(mousePos);
			if (backButton.click() && justClicked) {
				gameState = GameState::IN_GAME;
			}
		}
		if (gameState == GameState::LEVELS) 
		{

			// BACK BUTTON
			backButton.Init(Blobbybouncer::vec2(10, 10), 2, screen);
			backButton.UpdateMousePos(mousePos);
			if (backButton.click() && justClicked) {
				gameState = GameState::MAIN_MENU;
			}

			int scale = 4;
			Blobbybouncer::vec2 pos = Blobbybouncer::vec2(screen->GetWidth() / 2 - (24 * scale), 150);

			// LEVEL ONE BUTTON
			levelOneButton.Init(pos, scale, screen);
			levelOneButton.UpdateMousePos(mousePos);
			if (levelOneButton.click() && justClicked) {
				gameState = GameState::IN_GAME;
				tileMap->SetStage(0, 0);
			}

			pos.Add(0, (16 * scale) + 10);
			if (unlockedLevel >= 1) {
				// LEVEL TWO BUTTON
				levelTwoButton.Init(pos, scale, screen);
				levelTwoButton.UpdateMousePos(mousePos);
				if (levelTwoButton.click() && justClicked) {
					gameState = GameState::IN_GAME;
					tileMap->SetStage(1, 0);
				}
			}

			pos.Add(0, (16 * scale) + 10);

			if (unlockedLevel >= 2) {
				// LEVEL THREE BUTTON
				levelThreeButton.Init(pos, scale, screen);
				levelThreeButton.UpdateMousePos(mousePos);
				if (levelThreeButton.click() && justClicked) {
					gameState = GameState::IN_GAME;
					tileMap->SetStage(2, 0);
				}
			}

		}
		if (gameState == GameState::CREDITS) {

			creditsScreen.DrawScaled(0, 0, screen->GetWidth(), screen->GetHeight(), screen);

			// BACK BUTTON
			backButton.Init(Blobbybouncer::vec2(10, 10), 2, screen);
			backButton.UpdateMousePos(mousePos);
			if (backButton.click() && justClicked) {
				gameState = GameState::MAIN_MENU;
			}
		}


		justClicked = false;
		gameTimer.tick();
	}

	void Game::MouseMove(int x, int y) 
	{
		mousePos.Add(x, y);
	}

	void Game::MouseUp(int button) 
	{
		if (button != 1) return;
		justClicked = true;
		mouseDown = false;
	}

	void Game::MouseDown(int button) 
	{
		if (button != 1) return;
		mouseDown = true;
	}

	void Game::KeyDown(int key) 
	{
		int escKey = 41;
		if (key == escKey) {
			switch (gameState) {
				case GameState::IN_GAME:
					gameState = GameState::PAUSE;
					break;
				case GameState::PAUSE:
					gameState = GameState::IN_GAME;
					break;
			}
		}
	}

	void Game::KeyUp(int key) 
	{
		// EASTEREGG KONAMI CODE!!!! UP UP DOWN DOWN LEFT RIGHT LEFT RIGHT B A
		if (gameState != GameState::MAIN_MENU) return;
		switch (konamiProg) {
			case 10:
				if (key == 82) konamiProg--;
				else konamiProg = 10;
				break;
			case 9:
				if (key == 82) konamiProg--;
				else konamiProg = 10;
				break;
			case 8:
				if (key == 81) konamiProg--;
				else konamiProg = 10;
				break;
			case 7:
				if (key == 81) konamiProg--;
				else konamiProg = 10;
				break;
			case 6:
				if (key == 80) konamiProg--;
				else konamiProg = 10;
				break;
			case 5:
				if (key == 79) konamiProg--;
				else konamiProg = 10;
				break;
			case 4:
				if (key == 80) konamiProg--;
				else konamiProg = 10;
				break;
			case 3:
				if (key == 79) konamiProg--;
				else konamiProg = 10;
				break;
			case 2:
				if (key == 5) konamiProg--;
				else konamiProg = 10;
				break;
			case 1:
				if (key == 4) { 
					konamiProg--; 
					player->CompleteKonami();
				}
				else konamiProg = 10;
				break;
		}
	}
};