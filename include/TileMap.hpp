#ifndef INCLUDE_TILEMAP_HPP_
#define INCLUDE_TILEMAP_HPP_

#include <string>
#include <vector>

#include "TileSet.hpp"
#include "Geometry.hpp"

class TileMap{
public:
	TileMap(std::string file, TileSet* tileSet);
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z=0);
	void Render(int cameraX, int cameraY);
	void RenderLayer(int layer, int cameraX, int cameraY);
	int DetermParallax(int pos, int camera, int layer);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	Rect FindLimits();
	std::vector<Rect> GetInnerLimits();

private:
	std::vector<int> tileMatrix;
	std::vector<Rect> limitsVector;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	int mapInsideSquares;
};

#endif /* INCLUDE_TILEMAP_HPP_ */
