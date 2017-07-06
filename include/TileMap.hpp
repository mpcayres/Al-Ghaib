#ifndef INCLUDE_TILEMAP_HPP_
#define INCLUDE_TILEMAP_HPP_

#include <string>
#include <vector>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <set>
#include <queue>

#include "TileSet.hpp"
#include "Geometry.hpp"

class TileMap{
public:
	TileMap(std::string file, TileSet* tileSet);
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	void AddObjects();
	int& At(int x, int y, int z=0);
	void Render(int cameraX, int cameraY);
	void RenderLayer(int layer, int cameraX, int cameraY);
	int DetermParallax(int pos, int camera, int layer);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	std::queue<Vec2> GetPath();
	Rect FindLimits();
	std::vector<Rect> GetInnerLimits();
	void PathFind(Vec2 origem, Vec2 destino);

private:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int> > pPair;

	struct cell{
	    int parent_i, parent_j;
	    double f, g, h;
	};

	bool isValid(int row, int col);
	bool isUnBlocked(std::vector<std::vector<int> > grid, int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	void tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest);
	void aStarSearch(std::vector<std::vector<int>> grid, Pair src, Pair dest);


	std::vector<int> tileMatrix;
	std::vector<std::vector<int>> grid;
	std::vector<Rect> limitsVector;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	int mapInsideSquares;

	bool hasPath;
	std::queue<Vec2> path;
};

#endif /* INCLUDE_TILEMAP_HPP_ */
