#pragma once
#include "surface.h"
#include "vector2.h"
#include "collisionbox.h"
#include "tutorialpanel.h"

namespace Blobbybouncer
{
	class TileMap
	{
		public:
			TileMap( std::shared_ptr<Tmpl8::Surface> tileSurface, int tileSize);

			void MapTick(Tmpl8::Surface* screen);

			// Member data access
			std::shared_ptr<Tmpl8::Surface> GetSurface() { return tileSurface; }
			int GetTileSize() { return tileSize; }

			// Functionalities of Tilemap
			void DrawTile( vec2 tPos, Tmpl8::Surface* screen, vec2 pos);

			// Check for collision
			bool CheckCharBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t, char tileflag);
			bool TileMap::CheckForChar(int x, int y, char tileflag);

			void SetStage(int level, int stage);
			int GetLevel() { return mapLevel; };
			int GetStage() { return mapStage; };
			vec2 GetSpawn() { return spawnPoint; };
			vec2 GetBRusherSpawn() { return brusherSpawnpoint; };
 

		private:
			std::shared_ptr<Tmpl8::Surface> tileSurface;
			Tmpl8::Sprite iceCream = Tmpl8::Sprite(new Tmpl8::Surface("assets/decoration/icecream.png"), 1);
			Tmpl8::Sprite lolly = Tmpl8::Sprite(new Tmpl8::Surface("assets/decoration/lolly.png"), 1);
			std::unique_ptr<TutorialPanel> moveTutPanel = std::make_unique<TutorialPanel>(std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/tut_move_left_right.png"), 26));
			std::unique_ptr<TutorialPanel> jumpTutPanel = std::make_unique<TutorialPanel>(std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/tut_move_jump.png"), 16));
			std::unique_ptr<TutorialPanel> bounceTutPanel = std::make_unique<TutorialPanel>(std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/tut_move_bounce_pad.png"), 20));
			std::unique_ptr<TutorialPanel> climbTutPanel = std::make_unique<TutorialPanel>(std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/tut_move_climb.png"), 25));
			std::unique_ptr<TutorialPanel> deadTutPanel = std::make_unique<TutorialPanel>(std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/ui/tut_move_death.png"), 21));
			
			vec2 spawnPoint = vec2(0,0);
			vec2 brusherSpawnpoint = vec2(0, 0);
			int mapLevel = 0;
			int mapStage = 0;
			int tileSize;
			
			char map[3][4][17][81] = {
				{
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aoN",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aoN",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX3XX XX XX XX alTaaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX5XX XX XX XX XX XX XX XX XX alTaaS",
						"XX XX XX XX XX XX XX XX XX2XX XX XX XX XX XX XX XX XX XX XX XX XX XX alTaaS",
						"XX XX XX XX1XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX alTaaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX alTaaS",
						"XXPXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSXX XX XX XX XX alTaaS",
						"XX XX XX XX XX XX XX XX XX acSacSXX XX XX XX XX aaSaaSXX XX XX XX XX alTaaS",
						"acSacSacSacSacSacSacSacSacSaaSaaSacSacSacSadBadBaaSaaSacSacSacSacSacSacSacS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					},
					{
						"aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"aaSXX XX XX XX XX XX XX XX XX XX XX acSXX XX XX XX XX XX XX XX XX XX XX aaS",
						"aaSXX XX XX XX XX XX XX XX acSXX XX XX XX XX XX acSXX XX acSacSXX XX XX aaS",
						"aaSXX XX XX XX XX acSacSacSaaSXX XX XX XX XX XX XX XX XX XX aaSaaSXX aaSaaS",
						"aaSXX XX XX acSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSaaSXX aaSaaS",
						"aaSXX XX XX XX adBacSacSXX XX acSacSXX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTaaSXX aaSaaS",
						"aaSXX XX XX XX XX XX XX XX XX4XX XX XX XX XX XX XX akUXX XX alTXX XX XX aoN",
						"aoSXX XX XX acSXX XX XX XX XX XX XX XX XXJXX XX XX XX XX XX alTXX XX XX aoN",
						"aoSXXPXX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"aaSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSaaSacSao acSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaS"
					},
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX acSXX XX acSXX XX acSXX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX acSacSXX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX aaSaaSXX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX acSXX XX XX XX aaSXX XX XX XX acSXX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX aaSXX XX XX XX aaSacSXX XX XX aaSao ao ao ao ao ao aaS",
						"XX XX XX XX XX XX XX aaSadBacSacSacSaaSXX acSXX XX aaSao ao ao ao ao ao aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSao ao ao ao ao ao aaS",
						"XX XX XX acSXX XX XX XX XX XX XX XX XX XX XX XX adBaaSao ao ao ao ao ao aaS",
						"XX XXPXX aaSXX XX XX XX XX XX XX XX XX acSXX XX aaSaaSao ao ao ao ao ao aaS",
						"acSacSadBaaSacSacSacSacSacSacSacSacSacSaaSacSadBaaSaaSaoNaoNaoNaoNaoNaoNaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaoNaoNaoNaoNaoNaoNaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaoNaoNaoNaoNaoNaoNaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaoNaoNaoNaoNaoNaoNaaS"
					},
					{
						"aaSaaSaaSaaSaaSaaSaaSao ao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"ao ao ao ao ao ao ao ao ao ao ao aaSao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao aoPao ao aaSao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao aaSao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao aaSao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao acSacSacSacSaaSao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao aaSao ao ao ao ao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao aaSao ao ao ao ao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao acSacSacSacSaaSao ao ao ao ao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao acSacSacSao ao acSao ao ao ao ao ao ao alTao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao acSacSacSaaSao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao adBao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"amDamDanDamDamDanDamDamDanDamDamDanDamDamDanDamDamDanDamDamDaoNaoNaoNaoNaaS"
					}
				},
				{
					{
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao aoPao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao acSacSao ao ao ao acSacSao ao ao ao acSacSao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao adBao ao ao ao ao adBao ao ao ao ao ao ao ao ao ao ao aoN",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aoN",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao adBao acSacSacSacSacS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"amDamDanDamDamDanDamDamDanDamDamDanDamDamDanDamDamDanDamDamDaoNaoNaoNaoNaaS"
					},
					{
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao aoPao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao adBadBadBao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao adBadBao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao ao aaS",
						"amDamDanDamDamDanDamDamDanDamDamDanDamDamDanDamDamDanDamDamDaoNaoNaoNaoNaaS"
					},
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX acSXX XXIXX XX XX XX XX XX XXJXX XX XX XX XX XX alTXX XX XX aaS",
						"XXPXX XX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"acSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSacSacSacSacSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					},
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX acSXX XXIXX XX XX XX XX XX XXJXX XX XX XX XX XX alTXX XX XX aaS",
						"XXPXX XX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"acSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSacSacSacSacSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					}
				},
				{
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX acSXX XXIXX XX XX XX XX XX XXJXX XX XX XX XX XX alTXX XX XX aaS",
						"XXPXX XX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"acSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSacSacSacSacSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					},
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX aaSXX XX XX aaS",
						"XX XX XX XX acSXX XXIXX XX XX XX XX XX XXJXX XX XX XX XX XX aaSXX XX XX aaS",
						"XXPXX XX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"acSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSacSacSacSacSacS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					},
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX acSXX XXIXX XX XX XX XX XX XXJXX XX XX XX XX XX alTXX XX XX aaS",
						"XXPXX XX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"acSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSacSacSacSacSacS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					},
					{
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX acSacSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSaaSakUXX XX aaSXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX akUXX XX alTXX XX XX aaS",
						"XX XX XX XX acSXX XXIXX XX XX XX XX XX XXJXX XX XX XX XX XX alTXX XX XX aaS",
						"XXPXX XX XX aaSXX XX XX XX XX XX XX XX XX XX XX XX XX XX XX aaSXX XX XX aaS",
						"acSacSacSadBaaSacSacSacSacSao ao ao acSacSacSacSacSacSacSacSacSacSacSacSacS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSao ao ao aaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS",
						"aaSaaSaaSaaSaaSaaSaaSaaSaaSamDamDanDaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaSaaS"
					}
				},
			};
	};
}


