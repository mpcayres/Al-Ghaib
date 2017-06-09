#include "Player.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "InventoryKey.hpp"

#define MODULO_SPEED		5
#define AUMENTO_VELOCIDADE	2
#define DESACELERA			1


Player::Player(float x, float y, int oldInHand, std::vector<std::string> oldInventory) :
		spKinder("img/kinder.png", 20, 0.06, 4),
		spKinderRun("img/kinder-run.png", 15, 0.1, 4) {
	spKinder.SetScaleX(2.5); spKinder.SetScaleY(2.5);
	spKinderRun.SetScaleX(2.5); spKinderRun.SetScaleY(2.5);

	spNoise = Sprite("img/sprite-energia.png", 8 , 1 ,1);
	spNoise.SetScaleX(0.6); spNoise.SetScaleY(0.6);

	spInventory = Sprite("img/inventory.png", 1, 1, 1);
	spInventory.SetScaleX(2); spInventory.SetScaleY(2);
	spInventorybox = Sprite("img/box.png", 1, 1, 1);
	spInventorybox.SetScaleX(1.5); spInventorybox.SetScaleY(1.5);
	spInventoryboxSelected = Sprite("img/box-select.png", 1, 1, 1);
	spInventoryboxSelected.SetScaleX(1.5); spInventoryboxSelected.SetScaleY(1.5);

	box.x = x; box.y = y;
	box.w = spKinder.GetScaledWidth();
	box.h = spKinder.GetScaledHeight();
	previousPos = Vec2(x,y);
	timeRuido = Timer();
	timeCooldown = Timer();

	hp = 30;
	rotation = 0;
	speed.y = speed.x = 0;
	running = false;

	for(unsigned int i = 0; i < oldInventory.size(); i++){
		AddInventory(oldInventory[i]);
	}
	oldInventory.clear();

	inHandIndex = oldInHand; //dependendo do save pode ser diferente
	showingInventory = false;
	inventoryIndex = inHandIndex;

	direcao = LESTE;
	direcaoShift = false;

	ruido = 0;
	hidden = false;

	door = false;
}

Player::~Player(){
	inventory.clear();
}


/* Update - Movimentacao */
void Player::Update(float dt){
	int multiplicador;
	InputInstance = InputManager::GetInstance();

	//PODE COLOCAR A CONDICAO DE MUDAR A DIRECAO SO QUANDO ESTIVER MOVENDO A CAIXA
	if(!showingInventory && !hidden && !Camera::GetMoving()){
		direcaoShift = false;
		if(InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(InputInstance.IsKeyDown(Z_KEY) && (direcao == NORTE || direcao == SUL)){
				if(direcao == SUL) direcaoShift = true;
			} else{
				direcao = NORTE;
			}
			speed.y = -MODULO_SPEED;
			speed.x = 0;
			//rotation = -90;
			//nao pode ficar fora, senao o movimento fica bugado
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(InputInstance.IsKeyDown(Z_KEY) && (direcao == NORTE || direcao == SUL)){
				if(direcao == NORTE) direcaoShift = true;
			} else{
				direcao = SUL;
			}
			speed.y = MODULO_SPEED;
			speed.x = 0;
			//rotation = 90;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(InputInstance.IsKeyDown(Z_KEY) && (direcao == LESTE || direcao == OESTE)){
				if(direcao == OESTE) direcaoShift = true;
			} else{
				direcao = LESTE;
			}
			speed.x = MODULO_SPEED;
			speed.y = 0;
			//rotation = 0;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(InputInstance.IsKeyDown(Z_KEY) && (direcao == LESTE || direcao == OESTE)){
				if(direcao == LESTE) direcaoShift = true;
			} else{
				direcao = OESTE;
			}
			speed.x = -MODULO_SPEED;
			speed.y = 0;
			//rotation = 180;
			Running(InputInstance);
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			speed.x = 0;
			speed.y = 0;
			running = false;
		}

		if(speed.x != 0 || speed.y != 0){
			spKinder.Update(dt, direcao, direcaoShift);
			spKinderRun.Update(dt, direcao, direcaoShift);

			if(running == true) multiplicador = 10;
			else multiplicador = 1;
		} else{
			if((spKinder.GetCurrentFrame() > 1 && spKinder.GetCurrentFrame() < 12) ||
					(spKinder.GetCurrentFrame() > 12 && spKinder.GetCurrentFrame() <= 20)){
				if(direcao == NORTE) speed.y = -DESACELERA;
				if(direcao == SUL) speed.y = DESACELERA;
				if(direcao == LESTE) speed.x = DESACELERA;
				if(direcao == OESTE) speed.x = -DESACELERA;

				spKinder.Update(dt, direcao, direcaoShift);
			}

			multiplicador = 0;
		}
		ruido += 0.2 * multiplicador;
		if (ruido > 84) ruido = 84; // impedir bug na mostra

		if(multiplicador == 0 && ruido > 0){
			timeRuido.Update(dt);
			if (timeRuido.Get() > 0.3){
				timeRuido.Restart();
				ruido -= (ruido*0.2);
			}
		}

		//printf("%f\n", ruido);

		if(box.x + speed.x < limits.w - box.w && box.x + speed.x > limits.x){
			previousPos.x = box.x;
			box.x += speed.x;
		}
		if(box.y + speed.y < limits.h - box.h && box.y + speed.y > limits.y){
			previousPos.y = box.y;
			box.y += speed.y;
		}
		if(InputInstance.KeyPress(I_KEY)){
			showingInventory = true;
			inventoryIndex = inHandIndex;
		}
		if(InputInstance.KeyPress(G_KEY)){
			Camera::Move(box.x+100, box.y+100, 3);
		}

	} else if(showingInventory){
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
	} else if(hidden){
		multiplicador = 0;
		if(ruido > 0){
			timeRuido.Update(dt);
			if(timeRuido.Get() > 0.3){
				timeRuido.Restart();
				ruido -= (ruido*0.2); //pode colocar um fator diferente ja que esta escondido
			}
		}

		timeCooldown.Update(dt);
		if(timeCooldown.Get() > 1.5){
			ChangeHiddenState();
		}
	}

}

void Player::SetMovementLimits(Rect limits){
	this->limits.x = limits.x;
	this->limits.y = limits.y;
	this->limits.w = limits.w;
	this->limits.h = limits.h;
}

int Player::GetDirecao(){
	return direcao;
}

Vec2 Player::GetSpeed(){
	return speed;
}

void Player::SetPosition(int x, int y){
	box.x = x; box.y = y;
}

void Player::Running(InputManager InputInstance){
	if(InputInstance.IsKeyDown(LSHIFT_KEY)){
		speed.x *= AUMENTO_VELOCIDADE;
		speed.y *= AUMENTO_VELOCIDADE;
		running = true;
	} else{
		running = false;
	}
}


float Player::GetRuido(){
	return ruido;
}

bool Player::GetShowingInventory(){
	return showingInventory;
}

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
	spInventory.Render(posXCaixa, posYCaixa, 0);

	posX = posXCaixa + bordaX;
	posY = posYCaixa + bordaY + 40;

	if(inventoryIndex < 0) inventoryIndex = 0;
	for(unsigned i = 0; i < inventory.size() && i < 16 ;i++) {
		if((int) i == inventoryIndex) spInventoryboxSelected.Render(posX, posY, 0);
		else spInventorybox.Render(posX, posY, 0);


		if(inventory[i]->GetWidth() > widthMinorSquare){
			scaleX = float(widthMinorSquare)/float(inventory[i]->GetWidth());
			inventory[i]->SetScaleX(scaleX);
			posXCenter = posX;
		} else{
			posXCenter = posX + (widthMinorSquare - inventory[i]->GetWidth())/2;
		}
		if(inventory[i]->GetHeight() > heightMinorSquare){
			scaleY = float(heightMinorSquare)/float(inventory[i]->GetHeight());
			inventory[i]->SetScaleY(scaleY);
			posYCenter = posY;
		} else{
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
		} else{
			posXCenter = posX + (widthMinorSquare - inventory[inHandIndex]->GetWidth())/2;
		}
		if(inventory[inHandIndex]->GetHeight()> heightMinorSquare){
			scaleY = float(heightMinorSquare)/float(inventory[inHandIndex]->GetHeight());
			inventory[inHandIndex]->SetScaleY(scaleY);
			posYCenter = posY;
		} else{
			posYCenter = posY + (heightMinorSquare - inventory[inHandIndex]->GetHeight())/2;
		}
		inventory[inHandIndex]->Render(posXCenter, posYCenter);
	}
}

void Player::RenderNoise(){
	int posX, posY;
	int offset = 10;
	int aux;
	posX = SCREEN_SIZE_W - 17*offset;
	posY = offset;

	aux = (ruido/12) + 1;
	spNoise.SetFrame(aux);
	spNoise.Render(posX, posY, 0);

}

int Player::GetInHandIndex(){
	return inHandIndex;
}

InventoryObject* Player::GetInHand(){
	if(inHandIndex >= 0) return inventory[inHandIndex];
	else return nullptr;
}

void Player::AddInventory(std::string obj/*, std::string objSp*/){
	// Coloquei os parametros como as strings e nao o objeto, pq estava dando erro comigo
	// Coloquei a string da imagem comentada caso seja necessario
	if(inHandIndex < 0) inHandIndex = 0;
	if(obj == "InventoryKey"){
		inventory.emplace_back(new InventoryKey(/*objSp*/));
	}
}

std::vector<InventoryObject*> Player::GetInventory(){
	return inventory;
}

void Player::DeleteInventory(){
	if(inventory.size() == 1){
		inventory.erase(inventory.begin() + inHandIndex);
		inHandIndex = -1;
	} else{
		inventory.erase(inventory.begin() + inHandIndex);
		inHandIndex = 0 ;
	}
}

void Player::ChangeHiddenState(){
	hidden = !hidden;
	timeCooldown.Restart();
}


/* FUNCOES GERAIS */

void Player::NotifyCollision(GameObject& other){
	/*if(other.Is("Enemy")){
		//hp = 0;
		//Camera::Unfollow();
		//printf("CAUGHT YOU!");
	}*/
}

bool Player::Is(std::string type){
	return (type == "Player");
}

void Player::Render(){
	if(!hidden){
		if(running){
			spKinderRun.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else{
			spKinder.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		}
	}
}

bool Player::IsDead(){
	return (hp <= 0);
}

bool Player::GetDoor(){
	return door;
}

void Player::SetDoor(bool value){
	door = value;
}
