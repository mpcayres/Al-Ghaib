#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
		tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight) {
	if(tileSet.IsOpen()){
		rows = tileSet.GetHeight()/tileHeight;
		columns = tileSet.GetWidth()/tileWidth;
	}
}

void TileSet::Render(unsigned index, float x, float y){
	if(index < (unsigned) (rows*columns)-1) {
		int linhas = index/columns;
		int restLinhas = index % columns;

		int clipX, clipY;
		if(index >= (unsigned) columns){
			clipX = restLinhas * tileWidth;
			clipY = linhas * tileHeight;
		} else{
			clipX = index * tileWidth;
			clipY = 0;
		}

		tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
		tileSet.Render(x, y);
	}
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}
