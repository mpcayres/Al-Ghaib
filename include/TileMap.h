#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "TileSet.h"
#include <string>
#include <vector>

class TileMap {
public:
	TileMap(std::string file, TileSet* tileSet);

	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z = 0);
	void Render(int cameraX = 0, int cameraY = 0);
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

	int GetWidth();
	int GetHeight();
	int GetDepth();

private:
	int DetermParallax(int pos, int camera, int layer);

	std::vector<int> tileMatrix;
	TileSet* tileSet;

	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif /* TILEMAP_H_ */
