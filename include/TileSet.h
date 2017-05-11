#ifndef TILESET_H_
#define TILESET_H_

#include "Sprite.h"
#include <string>

class TileSet {
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

#endif /* TILESET_H_ */
