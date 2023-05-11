#include "tutorialpanel.h"



namespace Blobbybouncer
{

	TutorialPanel::TutorialPanel(std::shared_ptr<Tmpl8::Sprite> sprite):
		panelSprite(sprite)
	{}

	void TutorialPanel::Tick()
	{
		int numFrames = panelSprite->Frames();

		timer.tick();
		if (timer.totalMilliseconds() >= 100) {
			frameNum++;
			if (frameNum >= numFrames) frameNum = 0;
			panelSprite->SetFrame(frameNum);
			timer.reset();
		}
	}

}