#pragma once
#include "iostream"
#include "surface.h"
#include "timer.h"

namespace Blobbybouncer
{

	class TutorialPanel
	{

		public:
			TutorialPanel(std::shared_ptr<Tmpl8::Sprite> sprite);
			void Tick();
			std::shared_ptr<Tmpl8::Sprite> GetSprite() { return panelSprite; }

		private:
			Tmpl8::Timer timer = Tmpl8::Timer();
			std::shared_ptr<Tmpl8::Sprite> panelSprite;
			int frameNum = -1;


	};

};

