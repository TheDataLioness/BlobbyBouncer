#pragma once

#include "surface.h"
#include <iostream>
#include "timer.h"

namespace Blobbybouncer {

	enum class EmotionState {
		NEUTRAL = 0,
		CURIOUS = 1,
		HAPPY = 2,
		DAMAGE = 3,
		DEAD = 4
	};

	class PlayerStatus
	{

		public:
			PlayerStatus(Tmpl8::Surface* screen);
			void TickUpdate();
			void Damage();
			void Reset();
			int GetHealth() { return health; };

			void CompleteKonami() { completedKonami = true; }

		private:
			Tmpl8::Surface* screen;
			Tmpl8::Timer stateTimer = Tmpl8::Timer();

			const int maxHealth = 3;
			int health = maxHealth;
			EmotionState emotionState = EmotionState::NEUTRAL;

			bool completedKonami = false;

			std::unique_ptr<Tmpl8::Sprite> statusPanel = std::make_unique<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/health_indicator_panel.png"), 1);
			std::unique_ptr<Tmpl8::Sprite> heart = std::make_unique<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/hearts.png"), 2);
			std::unique_ptr<Tmpl8::Sprite> blobbyStates = std::make_unique<Tmpl8::Sprite>(new Tmpl8::Surface("assets/Blobby/BlobbyStates.png"),8);

			void UpdateEmotionState();

	};
}


