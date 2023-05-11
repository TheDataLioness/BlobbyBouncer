#include "playerstatus.h"
#include "game.h"


namespace Blobbybouncer {

	PlayerStatus::PlayerStatus(Tmpl8::Surface* screen) : 
		screen(screen)
	{}


	void PlayerStatus::TickUpdate() {

		

		const int scale = 4;
		statusPanel->DrawScaled(10, 0, 32 * scale, 64 * scale, screen);

		int xPos = 25;
		for (int i = 1; i <= 3; i++) {
			heart->SetFrame(i>health);
			heart->DrawScaled(xPos, 208, 8 * scale, 7 * scale, screen);
			xPos += 34;
		}

		UpdateEmotionState();
		blobbyStates->DrawScaled(5, 100, 32 * scale, 16 * scale, screen);
		
	}

	void PlayerStatus::UpdateEmotionState() {
		stateTimer.tick();

		if (stateTimer.totalSeconds() > 10 && emotionState == EmotionState::NEUTRAL) {
			stateTimer.reset();
			emotionState = EmotionState::CURIOUS;
		}

		switch (emotionState) {
			case EmotionState::NEUTRAL:
				blobbyStates->SetFrame(completedKonami ? 7 : 0);
				break;
			case EmotionState::CURIOUS:
				if (stateTimer.totalSeconds() >= 4) {
					emotionState = EmotionState::NEUTRAL;
					stateTimer.reset();
				}
				else {
					blobbyStates->SetFrame(stateTimer.totalSeconds());
				}
				break;
			case EmotionState::DAMAGE:
				if (stateTimer.totalSeconds() > 3) {
					emotionState = EmotionState::NEUTRAL;
					stateTimer.reset();
				}
				else {
					blobbyStates->SetFrame(5);
				}
				break;
			case EmotionState::DEAD:
				if (stateTimer.totalSeconds() > 3) {
					emotionState = EmotionState::NEUTRAL;
					stateTimer.reset();
				}
				else {
					blobbyStates->SetFrame(6);
				}
		}
	}

	void PlayerStatus::Damage() {
		health--;
		emotionState = EmotionState::DAMAGE;
		stateTimer.reset();
	}

	void PlayerStatus::Reset() {
		health = maxHealth;
		emotionState = EmotionState::DEAD;
	}

}