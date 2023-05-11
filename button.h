#pragma once
#include <Audio/Sound.hpp>
#include <Audio/Device.hpp>

#include <iostream>
#include "surface.h"
#include "vector2.h"
#include "collisionbox.h"

namespace Blobbybouncer
{

	enum class ButtonType
	{
		PLAY,
		LEVELS,
		RETRY,
		MENU,
		BACK,
		CREDITS,
		QUIT,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3
	};

	class Button
	{
		public:
			Button(ButtonType buttonType);
			void UpdateMousePos(vec2 pos);
			bool click();
			void Init(vec2 pos, int scale, Tmpl8::Surface* screen);
		private:
			std::shared_ptr<Tmpl8::Sprite> playSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_play.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> levelsSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_levels.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> retrySprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_retry.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> menuSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_menu.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> backSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_back.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> quitSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_quit.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> creditsSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_credits.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> levelOneSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_level_one.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> levelTwoSprite= std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_level_two.png"), 2);
			std::shared_ptr<Tmpl8::Sprite> levelThreeSprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/button_level_three.png"), 2);
			
			Audio::Sound buttonPlop = Audio::Device::loadSound("assets/audio/sfx/ui/button_plop.wav");

			ButtonType type;
			vec2 position = vec2(0, 0);
			int scale = 1;
			Tmpl8::Surface* screen = nullptr;
			CollisionBox collisionBox;
			int currentFrame = 0;

			vec2 mousePos = vec2(0,0);

	};
}

