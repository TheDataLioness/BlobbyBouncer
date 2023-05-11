#pragma once


#include <fstream>
#include <Audio/Sound.hpp>
#include <Audio/Device.hpp>

#include "vector2.h"
#include "timer.h"
#include "button.h"

using std::fstream;

namespace Tmpl8 {


	enum class GameState
	{
		MAIN_MENU,
		IN_GAME,
		PAUSE,
		LEVELS, 
		CREDITS
	};


	class Surface;
	class Game
	{
		public:
			void SetTarget( Surface* surface ) { screen = surface; }
			void Init();
			void Shutdown();
			void Quit();
			void Tick( float deltaTime );
			void MouseUp(int button);
			void MouseDown(int button);
			void MouseMove(int x, int y);
			void KeyUp(int key);
			void KeyDown(int key);
			bool CheckPos(int x, int y);
			bool CheckBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t);
		private:
			Surface* screen;
			
			// All stats data
			fstream stats;
			float fastestTimeOne = 0;
			float fastestTimeTwo = 0;
			float fastestTimeThree = 0;
			int unlockedLevel = 0;


			bool justClicked = false;
			bool mouseDown = false;
			bool bRusherSpawned = false;
			int titleFrame = 0;
			bool titleBack = false;
			int konamiProg = 10;

			Timer titleTimer = Timer();

			// To keep track of time of game
			Timer gameTimer = Timer();
			float elapsedGameTime = 0;

			GameState gameState = GameState::MAIN_MENU;

			Audio::Sound mainTheme = Audio::Sound{ "assets/audio/music/main_track.wav", Audio::Sound::Type::Sound };
		
			Blobbybouncer::vec2 mousePos = Blobbybouncer::vec2(0, 0);

			// Credits for credit screen
			Sprite creditsScreen = Sprite(new Surface("assets/ui/credits.png"), 1);

			// All Menu buttons
			Blobbybouncer::Button retryButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::RETRY);
			Blobbybouncer::Button playButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::PLAY);
			Blobbybouncer::Button levelsButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::LEVELS);
			Blobbybouncer::Button menuButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::MENU);
			Blobbybouncer::Button backButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::BACK);
			Blobbybouncer::Button quitButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::QUIT);
			Blobbybouncer::Button creditsButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::CREDITS);
			Blobbybouncer::Button levelOneButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::LEVEL_1);
			Blobbybouncer::Button levelTwoButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::LEVEL_2);
			Blobbybouncer::Button levelThreeButton = Blobbybouncer::Button(Blobbybouncer::ButtonType::LEVEL_3);

	};

}; // namespace Tmpl8