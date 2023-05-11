#include "TileMap.h"

#include <iostream>

#include "algorithm"
#include "template.h"



namespace Blobbybouncer
{
	TileMap::TileMap(std::shared_ptr<Tmpl8::Surface> tileSurface, int t_Size) :
		tileSurface(tileSurface),
		tileSize(t_Size)
	{}

	void TileMap::MapTick(Tmpl8::Surface* screen) {
		bool hasBRusher = false;
		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				int tx = map[mapLevel][mapStage][y][x * 3] - 'a';
				int ty = map[mapLevel][mapStage][y][x * 3 + 1] - 'a';
				
				// Place extra's
				switch (map[mapLevel][mapStage][y][x * 3 + 2])
				{
					case 'I':
						iceCream.Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case 'J':
						lolly.Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case '1':
						moveTutPanel->Tick();
						moveTutPanel->GetSprite()->Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case '2':
						jumpTutPanel->Tick();
						jumpTutPanel->GetSprite()->Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case '3':
						climbTutPanel->Tick();
						climbTutPanel->GetSprite()->Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case '4':
						deadTutPanel->Tick();
						deadTutPanel->GetSprite()->Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case '5':
						bounceTutPanel->Tick();
						bounceTutPanel->GetSprite()->Draw(screen, x * GetTileSize(), y * GetTileSize());
						break;
					case 'P':
						spawnPoint.SetX(x * GetTileSize());
						spawnPoint.SetY(y * GetTileSize());
						break;
					case 'Y': 
						brusherSpawnpoint.SetX(x * GetTileSize());
						brusherSpawnpoint.SetY(y * GetTileSize());
						hasBRusher = true;
						break;
				}

				

				if (map[mapLevel][mapStage][y][x * 3] == 'X' && map[mapLevel][mapStage][y][x * 3 + 1] == 'X') continue;

				DrawTile(Blobbybouncer::vec2(tx, ty), screen, Blobbybouncer::vec2(x * GetTileSize(), y * GetTileSize()));
			}
		}
		if (!hasBRusher) {
			brusherSpawnpoint.SetX(0);
			brusherSpawnpoint.SetY(0);
		}
	}

	/**
	 * Source: Noua via 3dgep.com Discord
	 * https://discord.com/channels/515453022097244160/686661689894240277/1033258419827773460
	 */
	void TileMap::DrawTile(vec2 tPos, Tmpl8::Surface* screen, vec2 pos)
	{
		int maxX = pos.GetFloorX() + tileSize;
		int maxY = pos.GetFloorY() + tileSize;
		
		//determine if the tile is offscreen
		if (maxX < 0 || pos.GetFloorX() >= ScreenWidth || maxY < 0 || pos.GetY() >= ScreenHeight)
			return;
		
		//determine the clipping amount
		int minCX = std::max(0, pos.GetFloorX());
		int maxCX = std::min(ScreenWidth - 1, maxX);
		
		int minCY = std::max(0, pos.GetFloorY());
		int maxCY = std::min(ScreenHeight - 1, maxY);
		
		//difference of the clipped amount and the actual amount
		int addOffsetMinX = abs(minCX - pos.GetFloorX());
		
		int addOffsetMaxX = abs(maxCX - maxX);
		
		int addOffsetMinY = abs(minCY - pos.GetFloorY());
		
		int addOffsetMaxY = abs(maxCY - maxY);
		
		//add offset to the origin

		tPos.Add(addOffsetMinX, addOffsetMinY);
		pos.Add(addOffsetMinX, addOffsetMinY);
		
		//substract the clipped amount from the tile
		int height = tileSize - addOffsetMaxY - addOffsetMinY;
		int width = tileSize - addOffsetMaxX - addOffsetMinX;

		// draw tile
		Tmpl8::Pixel* src = tileSurface->GetBuffer() + tPos.GetFloorX() + tPos.GetFloorY() * tileSize;
		Tmpl8::Pixel* dst = screen->GetBuffer() + pos.GetFloorX() + pos.GetFloorY() * screen->GetPitch();
		
		for (int i = 0; i < height; i++)
		{
			memcpy(dst, src, sizeof(Tmpl8::Pixel) * width);
			src += tileSurface->GetPitch();
			dst += screen->GetPitch();
		}
	}

	bool TileMap::CheckForChar(int x, int y, char tileflag)
	{
		int tx = x / 32, ty = y / 32;
		return map[mapLevel][mapStage][ty][tx * 3 + 2] == tileflag;
	}

	bool TileMap::CheckCharBetween(Blobbybouncer::vec2 pos, Blobbybouncer::vec2 pos_t, char tileflag)
	{
		int minX = std::min(pos.GetFloorX(), pos_t.GetFloorX());
		int minY = std::min(pos.GetFloorY(), pos_t.GetFloorY());
		int maxX = std::max(pos.GetFloorX(), pos_t.GetFloorX());
		int maxY = std::max(pos.GetFloorY(), pos_t.GetFloorY());

		if (minY == maxY) {
			for (int x = minX + 2; x < maxX -1; x++) {
				if (CheckForChar(x, minY, tileflag)) return true;
			}
		}
		if (minX == maxX) {
			for (int y = minY + 2; y < maxY -1; y++) {
				if (CheckForChar(minX, y, tileflag)) return true;
			}
		}
		return false;
	}

	void TileMap::SetStage(int level, int stage)
	{
		mapLevel = level;
		mapStage = stage;
	}
}



