#include "button.h"

namespace Blobbybouncer
{

	Button::Button(ButtonType buttonType) :
		type(buttonType)
	{}

	void Button::Init(vec2 pos, int initScale, Tmpl8::Surface* initScreen)
	{
		collisionBox = CollisionBox(&pos, &(pos + vec2(48 * initScale, 16 * initScale)));
		position = pos;
		scale = initScale;
		screen = initScreen;
	}

	void Button::UpdateMousePos(vec2 pos) 
	{
		mousePos = pos;
		Tmpl8::Sprite* sprite = playSprite.get();
		switch (type) {
			case ButtonType::LEVELS:
				sprite = levelsSprite.get();
				break;
			case ButtonType::RETRY:
				sprite = retrySprite.get();
				break;
			case ButtonType::MENU:
				sprite = menuSprite.get();
				break;
			case ButtonType::BACK:
				sprite = backSprite.get();
				break;
			case ButtonType::QUIT:
				sprite = quitSprite.get();
				break;
			case ButtonType::CREDITS:
				sprite = creditsSprite.get();
				break;
			case ButtonType::LEVEL_1:
				sprite = levelOneSprite.get();
				break;
			case ButtonType::LEVEL_2:
				sprite = levelTwoSprite.get();
				break;
			case ButtonType::LEVEL_3:
				sprite = levelThreeSprite.get();
				break;
		}

		bool colliding = collisionBox.IsColliding(pos);
		if (currentFrame != colliding && colliding) {
			buttonPlop.setVolume(0.25);
			buttonPlop.replay();
		}

		currentFrame = colliding;
		sprite->SetFrame(colliding);
		sprite->DrawScaled(position.GetFloorX(), position.GetFloorY(), 48 * scale, 16 * scale, screen);
	}

	bool Button::click()
	{
		return collisionBox.IsColliding(mousePos);
	}

}
