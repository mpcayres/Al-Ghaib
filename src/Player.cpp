#include "Player.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "InventoryKey.hpp"

#define MODULO_SPEED 8
#define AUMENTO_VELOCIDADE 2

Player* Player::player;

Player::Player(float x, float y) :
		timeAnim(0.1), sp("img/kinder.jpg", 20, timeAnim, 4){
	sp.SetScaleX(2.5);
	sp.SetScaleY(2.5);

	spInventory = Sprite("img/inventory.png", 1, 1, 1);
	spInventory.SetScaleX(2); spInventory.SetScaleY(2);
	spInventorybox = Sprite("img/box.png", 1, 1, 1);
	spInventorybox.SetScaleX(1.5); spInventorybox.SetScaleY(1.5);
	spInventoryboxSelected = Sprite("img/box-select.png", 1, 1, 1);
	spInventoryboxSelected.SetScaleX(1.5); spInventoryboxSelected.SetScaleY(1.5);

	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();
	previousPos = Vec2(x,y);
	//time = Timer();

	hp = 30;
	rotation = 0;
	speed.y = speed.x = 0;
	player = this;
	running = false;

	inHandIndex = -1; //dependendo do save pode ser diferente
	showingInventory = false;
	inventoryIndex = inHandIndex;

	direcao = LESTE;
	dirCollision = NONE;
	colliding = false;
}

Player::~Player(){
	player = nullptr;
}

void Player::Update(float dt){
	InputInstance = InputManager::GetInstance();

	//PODE COLOCAR A CONDICAO DE MUDAR A DIRECAO SO QUANDO ESTIVER MOVENDO A CAIXA
	if(showingInventory == false){
		if(InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(!InputManager::GetInstance().IsKeyDown(Z_KEY)) direcao = NORTE;
			speed.y = -MODULO_SPEED;
			speed.x = 0;
			//rotation = -90;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(!InputManager::GetInstance().IsKeyDown(Z_KEY)) direcao = SUL;
			speed.y = MODULO_SPEED;
			speed.x = 0;
			//rotation = 90;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(!InputManager::GetInstance().IsKeyDown(Z_KEY)) direcao = LESTE;
			speed.x = MODULO_SPEED;
			speed.y = 0;
			//rotation = 0;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(!InputManager::GetInstance().IsKeyDown(Z_KEY)) direcao = OESTE;
			speed.x = -MODULO_SPEED;
			speed.y = 0;
			//rotation = 180;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			speed.x = 0;
			speed.y = 0;
		}


		//chato, eu sei, mas isso  aqui em baixo não pode ficar fora assim se não o movimento fica bugado
		/*if(InputInstance.IsKeyDown(LSHIFT_KEY)){
			speed.x *= AUMENTO_VELOCIDADE;
			speed.y *= AUMENTO_VELOCIDADE;
			running = true;
		} else
			running = false;*/

	//Deixei essa parte aqui pra caso preciso em outro caso
	//if(colliding && dirCollision == direcao){
		//Tentei isso de baixo tbm, mas ficou com�dia
		/*if(dirCollision == NORTE || dirCollision == SUL){
			box.y = previousPos.y;
		} else if(dirCollision == LESTE || dirCollision == OESTE){
			box.x = previousPos.x;
		}*/
	//	colliding = false;
	//	dirCollision = NONE;
	//} else{
		if(box.x + speed.x < 1408 - box.w && box.x + speed.x > 0){
			previousPos.x = box.x;
			box.x += speed.x;
		}
		if(box.y + speed.y < 1280 - box.h && box.y + speed.y > 0){
			previousPos.y = box.y;
			box.y += speed.y;
		}
		if(InputInstance.KeyPress(I_KEY)){
			showingInventory = true;
			inventoryIndex = inHandIndex;
		}
	}else{
		/*MOVIMENTACAO DO INVENTARIO*/
		if(InputInstance.KeyPress(I_KEY))
			showingInventory = false;
		if(InputInstance.KeyPress(UP_ARROW_KEY) && inventoryIndex > 3){
			// 3 porcausa da primeira linha de itens 0 1 2 3
			inventoryIndex -= 4;
		}
		if(InputInstance.KeyPress(DOWN_ARROW_KEY) && inventoryIndex < 12){
			// 12 porcausa da ultima linha de itens 12 13 14 15
			if(inventoryIndex + 4 <= (int) inventory.size()-1)
				inventoryIndex += 4;
		}
		if(InputInstance.KeyPress(LEFT_ARROW_KEY) && inventoryIndex%4 != 0){
			// %4 porcausa da primeira coluna de itens 0 4 8 12
			inventoryIndex -= 1;
		}
		if(InputInstance.KeyPress(RIGHT_ARROW_KEY) && (inventoryIndex+1)%4 != 0 && inventory.size() > 1){
			// %index+1 porcausa da ultima coluna 3 7 11 15
			if(inventoryIndex + 1 <= (int) inventory.size()-1 && inventoryIndex + 1 < 16)
				inventoryIndex += 1;
		}
		if(InputInstance.KeyPress(Z_KEY)){
			inHandIndex = inventoryIndex;
			showingInventory = false;
		}
		/* */
	}

	if(speed.x != 0 || speed.y != 0){
		if(running){
			sp.SetFrameTime(timeAnim/20);
		} else{
			sp.SetFrameTime(timeAnim);
		}
		sp.Update(dt, direcao);
	}
}

void Player::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Player::IsDead(){
	return (hp <= 0);
}

void Player::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
	//aux = aux.Rotate(cannonAngle);
}

void Player::Running(InputManager InputInstance){
	if(InputInstance.IsKeyDown(LSHIFT_KEY)){
		speed.x *= AUMENTO_VELOCIDADE;
		speed.y *= AUMENTO_VELOCIDADE;
		running = true;
	} else
		running = false;


}
void Player::NotifyCollision(GameObject& other){
	if(other.Is("SceneObject")){
		colliding = true;
		dirCollision = direcao;
	}

	if(other.Is("Enemy")){
		//hp = 0;
		//Camera::Unfollow();
		//printf("CAUGHT YOU!");

	}
}

bool Player::Is(std::string type){
	return (type == "Player");
}

bool Player::getRunning(){
	return running;
}

bool Player::GetShowingInventory(){return showingInventory;}

void Player::RenderInventory(){
	int posX, posY, posXCenter, posYCenter, posXCaixa, posYCaixa;
	int bordaX, bordaY;
	float scaleX = 1, scaleY = 1;
	int widthMinorSquare, heightMinorSquare;

	bordaX = spInventory.GetScaledWidth()/9;
	bordaY = spInventory.GetScaledHeight()/8;
	widthMinorSquare = spInventorybox.GetScaledWidth();
	heightMinorSquare = spInventorybox.GetScaledHeight();

	posXCaixa = Game::GetInstance().GetWidth()/2 - (spInventory.GetScaledWidth()/2);
	posYCaixa = Game::GetInstance().GetHeight()/2 - (spInventory.GetScaledHeight()/2);
	spInventory.Render(posXCaixa,posYCaixa, 0);

	posX = posXCaixa + bordaX;
	posY = posYCaixa + bordaY + 40;

	if(inventoryIndex < 0) inventoryIndex = 0;
	for(unsigned i = 0; i < inventory.size() && i < 16 ;i++) {
		if((int) i == inventoryIndex) spInventoryboxSelected.Render(posX, posY, 0);
		else spInventorybox.Render(posX, posY, 0);


		if(inventory[i]->GetWidth()> widthMinorSquare){
			scaleX = float(widthMinorSquare)/float(inventory[i]->GetWidth());
			inventory[i]->SetScaleX(scaleX);
			posXCenter = posX;
		}else{
			posXCenter = posX + (widthMinorSquare - inventory[i]->GetWidth())/2;
		}
		if(inventory[i]->GetHeight()> heightMinorSquare){
			scaleY = float(heightMinorSquare)/float(inventory[i]->GetHeight());
			inventory[i]->SetScaleY(scaleY);
			posYCenter = posY;
		}else{
			posYCenter = posY + (heightMinorSquare - inventory[i]->GetHeight())/2;
		}

		inventory[i]->Render(posXCenter, posYCenter);

		posX += bordaX*2;
		if(posX >= posXCaixa + bordaX*8){
			posX = posXCaixa + bordaX;
			posY += bordaY*1.5;
		}

		scaleX = scaleY = 1;
	}
}

void Player::RenderInHand(){
	int posX, posY, scaleX, scaleY;
	int offset = 10, widthMinorSquare, heightMinorSquare;
	int posXCenter, posYCenter;
	posX = SCREEN_SIZE_W - 8*offset;
	posY = offset;
	widthMinorSquare = spInventorybox.GetScaledWidth();
	heightMinorSquare = spInventorybox.GetScaledHeight();

	spInventoryboxSelected.Render(posX,posY, 0);
	if(inHandIndex >= 0){
		if(inventory[inHandIndex]->GetWidth()> widthMinorSquare){
			scaleX = float(widthMinorSquare)/float(inventory[inHandIndex]->GetWidth());
			inventory[inHandIndex]->SetScaleX(scaleX);
			posXCenter = posX;
		}else{
			posXCenter = posX + (widthMinorSquare - inventory[inHandIndex]->GetWidth())/2;
		}
		if(inventory[inHandIndex]->GetHeight()> heightMinorSquare){
			scaleY = float(heightMinorSquare)/float(inventory[inHandIndex]->GetHeight());
			inventory[inHandIndex]->SetScaleY(scaleY);
			posYCenter = posY;
		}else{
			posYCenter = posY + (heightMinorSquare - inventory[inHandIndex]->GetHeight())/2;
		}
		inventory[inHandIndex]->Render(posXCenter, posYCenter);
	}
}

void Player::AddInventory(std::string obj/*, std::string objSp*/){
	// Coloquei os parametros como as strings e nao o objeto, pq estava dando erro comigo
	// Coloquei a string da imagem comentada caso seja necessario
	if(inHandIndex < 0) inHandIndex = 0;
	if(obj == "KeyObject"){
		inventory.emplace_back(new InventoryKey(/*objSp*/));
		inventory.emplace_back(new InventoryKey(/*objSp*/));
		inventory.emplace_back(new InventoryKey(/*objSp*/));
		inventory.emplace_back(new InventoryKey(/*objSp*/));
		inventory.emplace_back(new InventoryKey(/*objSp*/));
		inventory.emplace_back(new InventoryKey(/*objSp*/));
	}
}

InventoryObject* Player::GetInHand(){
	if(inHandIndex >= 0) return inventory[inHandIndex];
	else return nullptr;
}

int Player::GetDirecao(){
	return direcao;
}

Vec2 Player::GetSpeed(){
	return speed;
}

void Player::DeleteInventory(){
	if(inventory.size() == 1){
		inventory.erase(inventory.begin() + inHandIndex);
		inHandIndex = -1;
	}else{
		inventory.erase(inventory.begin() + inHandIndex);
		inHandIndex = 0 ;
	}
}
