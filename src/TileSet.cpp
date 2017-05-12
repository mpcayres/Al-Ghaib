#include "TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tileSet.Open(file);
	rows = (tileSet.GetHeight()/tileHeight);
	columns = (tileSet.GetWidth()/tileWidth);
}

void TileSet::Render(unsigned index,float x, float y){
	if (index < (unsigned)(rows*columns)-1){
		int valoresClipx, valoresClipy;
		if(index >= (unsigned) columns){
			int auxLinhas = index/columns;
			int auxRestoLinhas = index % columns;

			valoresClipx = auxRestoLinhas * tileWidth;
			valoresClipy = auxLinhas * tileHeight;
		} else {
			valoresClipx = index * tileWidth;
			valoresClipy = 0;
		}
		tileSet.SetClip(valoresClipx, valoresClipy, tileWidth, tileHeight);
		tileSet.Render(x ,y, 0);
	}
}

int TileSet::GetTileHeight(){
	return tileHeight;
}

int TileSet::GetTileWidth(){
	return tileWidth;
}
