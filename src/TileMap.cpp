#include <iostream>

#include "TileMap.hpp"
#include "MissionManager.hpp"

TileMap::TileMap(std::string file, TileSet* tileSet){
	this->tileSet = tileSet;
	hasPath = false;
	Load(file);
}

void TileMap::Load(std::string file){
	FILE* fp = fopen(file.c_str(), "r");
	if(fp == nullptr){
		std::cout << "Erro ao abrir o arquivo: " << file << std::endl;
		exit(1);
	}

	fscanf(fp, "%d,%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth, &mapInsideSquares);

	int num;
	int x,y,c,a;
	int wiAux = tileSet->GetTileWidth();
	int heAux = tileSet->GetTileHeight();
	for(int i = 0; i < mapInsideSquares; i++){
		fscanf(fp, "%d,%d,%d,%d,", &x,&y,&c,&a);
		limitsVector.push_back(Rect((x * wiAux), (y*heAux), (c*wiAux), (a*heAux)));
	}

	for (int i = 0; i < mapHeight; i++) {
	    std::vector<int> row;
	    for (int j = 0; j < mapWidth; j++) {
	        row.push_back(0);
	    }
	    grid.push_back(row);
	}

	int m=0,n=0;
	while(!feof(fp)){
		fscanf(fp, " %d,", &num);
		tileMatrix.push_back(num - 1);
		if(num == 1) grid[m][n] = 1;
		n++;
		if(n == mapWidth){
			n = 0;
			m++;
		}
	}

	fclose(fp);
}

void TileMap::Render(int cameraX, int cameraY){
	for(int i = 1; i < mapDepth; i++){
		TileMap::RenderLayer(i, cameraX, cameraY);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	for(int i = 0; i < mapWidth; i++){
		for(int j = 0; j < mapHeight; j++){
			int index = At(i, j, layer);
			if(index >= 0){
				int posX = DetermParallax(i*tileSet->GetTileWidth(), cameraX, layer);
				int posY = DetermParallax(j*tileSet->GetTileHeight(), cameraY, layer);
				tileSet->Render(index, posX, posY);
			}
		}
	}
}

int TileMap::DetermParallax(int pos, int camera, int layer){
	return (pos - camera*(layer+1));
}

void TileMap::SetTileSet(TileSet *tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
	return ( (int&) tileMatrix.at(x + y*mapWidth + z*mapWidth*mapHeight) );
}

int TileMap::GetDepth(){
	return mapDepth;
}
int TileMap::GetHeight(){
	return mapHeight;
}
int TileMap::GetWidth(){
	return mapWidth;
}

Rect TileMap::FindLimits(){
	Rect aux;
	int lastX = 0, lastY = 0 , firstX = 10000000, firstY = 10000000;
	int i;
	int value;

	for(i = 0; i< (mapHeight*mapWidth)-1 ; i++){
		if(tileMatrix[i] == 0){
			value = (i%mapWidth) * tileSet->GetTileWidth();
			if(value < firstX) firstX = value;
			if(value > lastX) lastX = value;

			if(i>mapWidth) value = (i/mapWidth)* tileSet->GetTileHeight();
			else value = 0;
			if(value < firstY) firstY = value;
			if(value > lastY) lastY = value;
		}
	}
	lastX += tileSet->GetTileWidth();
	lastY += tileSet->GetTileHeight();

	aux.x = firstX;
	aux.y = firstY;//firstY - MissionManager::player->box.h/2;//tileSet->GetTileHeight();
	aux.w = lastX; //lastX
	aux.h = lastY; //lastY

	return aux;
}

std::vector<Rect> TileMap::GetInnerLimits(){
	return limitsVector;
}

bool TileMap::isValid(int row, int col){
    return (row >= 0) && (row < mapHeight) &&
           (col >= 0) && (col < mapWidth);
}

bool TileMap::isUnBlocked(std::vector<std::vector<int>> grid, int row, int col){
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}

bool TileMap::isDestination(int row, int col, Pair dest){
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

double TileMap::calculateHValue(int row, int col, Pair dest){
    return ((double)sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

void TileMap::tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest){
   // printf ("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col )){
        Path.push(std::make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(std::make_pair (row, col));

    while (!Path.empty()){
        std::pair<int,int> p = Path.top();
        path.emplace(Vec2((p.second)*tileSet->GetTileWidth() + tileSet->GetTileWidth()/2,
        		(p.first)*tileSet->GetTileHeight() + tileSet->GetTileHeight()/2 ));

        Path.pop();
       // printf("-> (%d,%d) ",p.first,p.second);
    }
    hasPath = true;
}

void TileMap::aStarSearch(std::vector<std::vector<int>> grid, Pair src, Pair dest){

    if (isValid (src.first, src.second) == false){
        printf ("Source is invalid\n");
        return;
    }

    if (isValid (dest.first, dest.second) == false){
        printf ("Destination is invalid\n");
        return;
    }

    if (isUnBlocked(grid, src.first, src.second) == false ||
            isUnBlocked(grid, dest.first, dest.second) == false){
        printf ("Source or the destination is blocked\n");
        return;
    }

    if (isDestination(src.first, src.second, dest) == true){
        printf ("We are already at the destination\n");
        return;
    }

    bool closedList[mapHeight][mapWidth];
    memset(closedList, false, sizeof (closedList));

    std::vector<std::vector<cell>> cellDetails(mapHeight, std::vector<cell>(mapWidth));
    int i, j;
    for (i=0; i<mapHeight; i++){
        for (j=0; j<mapWidth; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    std::set<pPair> openList;

    openList.insert(std::make_pair (0.0, std::make_pair (i, j)));

    bool foundDest = false;

    while (!openList.empty()){
        pPair p = *openList.begin();

        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
        if (isValid(i-1, j) == true){

            if (isDestination(i-1, j, dest) == true){
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
            //    printf ("The destination cell is found\n");
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i-1][j] == false &&
                     isUnBlocked(grid, i-1, j) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i-1][j].f == FLT_MAX ||
                        cellDetails[i-1][j].f > fNew){
                    openList.insert( std::make_pair(fNew,
                                              std::make_pair(i-1, j)));


                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }
        if (isValid(i+1, j) == true){

            if (isDestination(i+1, j, dest) == true){

                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
             //   printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i+1][j] == false &&
                     isUnBlocked(grid, i+1, j) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i+1][j].f == FLT_MAX ||
                        cellDetails[i+1][j].f > fNew){
                    openList.insert( std::make_pair (fNew, std::make_pair (i+1, j)));
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        if (isValid (i, j+1) == true){

            if (isDestination(i, j+1, dest) == true){
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
            //    printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }


            else if (closedList[i][j+1] == false &&
                     isUnBlocked (grid, i, j+1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j+1].f == FLT_MAX ||
                        cellDetails[i][j+1].f > fNew){
                    openList.insert( std::make_pair(fNew,
                                        std::make_pair (i, j+1)));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }




        if (isValid(i, j-1) == true){
            if (isDestination(i, j-1, dest) == true){

                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
           //     printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }


            else if (closedList[i][j-1] == false &&
                     isUnBlocked(grid, i, j-1) == true){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j-1].f == FLT_MAX ||
                        cellDetails[i][j-1].f > fNew){
                    openList.insert( std::make_pair (fNew,
                                         std::make_pair (i, j-1)));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
    }
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}


void TileMap::PathFind(Vec2 origem, Vec2 destino){
	    Pair src = std::make_pair(origem.y/tileSet->GetTileHeight(), origem.x/tileSet->GetTileWidth());
	    Pair dest = std::make_pair(destino.y/tileSet->GetTileHeight(), destino.x/tileSet->GetTileWidth());
	    aStarSearch(grid, src, dest);
}

std::queue<Vec2> TileMap::GetPath(){
	std::queue<Vec2> aux;
	if(hasPath){
		hasPath = false;
		return path;
	}
	else return(aux);
}
