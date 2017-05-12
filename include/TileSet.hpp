#ifndef INCLUDE_TILESET_HPP_
#define INCLUDE_TILESET_HPP_

#include <string>

#include "Sprite.hpp"

class TileSet{
public:
	TileSet(int tileWidth, int tileHeight, std::string file);
	void Render(unsigned index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();

private:
	Sprite tileSet;
	int rows;
	int columns;

	int tileWidth;
	int tileHeight;
};

#endif /* INCLUDE_TILESET_HPP_ */
