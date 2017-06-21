#include "Player.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "InventoryKey.hpp"
#include "InventoryClown.hpp"
#include "InventoryBear.hpp"
#include <iostream>

#define MODULO_SPEED		5
#define AUMENTO_VELOCIDADE	2
#define DESACELERA			1

Player::Player(float x, float y, int oldInHand, std::vector<std::string> oldInventory) :
		spKinder("img/sprite-kinder.png", 20, 0.06, 4),
		spKinderRun("img/sprite-kinder-run.png", 15, 0.1, 4),
		spAnimKinder("img/sprite-kinder-run.png", 15, 0.4, 4),
		spKinderPush("img/sprite-kinder-push.png", 6, 0.1, 2) {
	spKinder.SetScaleX(2.5); spKinder.SetScaleY(2.5);
	spKinderRun.SetScaleX(2.5); spKinderRun.SetScaleY(2.5);
	spAnimKinder.SetScaleX(2.5); spAnimKinder.SetScaleY(2.5);
	spKinderPush.SetScaleX(2.5); spKinderPush.SetScaleY(2.5);

	spNoise = Sprite("img/sprite-energia.png", 9, 1 ,1);
	spNoise.SetScaleX(0.5); spNoise.SetScaleY(0.5);

	spInventory = Sprite("img/inventory.png", 1, 1, 1);
	spInventory.SetScaleX(2); spInventory.SetScaleY(2);
	spInventorybox = Sprite("img/box.png", 1, 1, 1);
	spInventorybox.SetScaleX(1.2); spInventorybox.SetScaleY(1.2);
	spInventoryboxSelected = Sprite("img/box-select.png", 1, 1, 1);
	spInventoryboxSelected.SetScaleX(1.2); spInventoryboxSelected.SetScaleY(1.2);

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
	animShowing = false;
	door = false;
	aboveObject = false;
	lastPicked = "";
}

Player::~Player(){
	inventory.clear();
}

/* FUNCOES GERAIS */

void Player::Update(float dt){
	int multiplicador;
	InputInstance = InputManager::GetInstance();
	if(!showingInventory && !hidden && !Camera::GetMoving() && !aboveObject){
		std::shared_ptr<InventoryObject> inHand = GetInHand();
		if(inHand != nullptr){
			if(InputManager::GetInstance().KeyPress(X_KEY) && inHand->IsObject("InventoryMiniGame")){
				animShowing = true;
				timeCooldown.Restart();
				if(inHand->Action(nullptr) == true){
					MissionManager::player->DeleteInventory();
					AddInventory("InventoryKey");
				}
			}
			if(animShowing){
				spAnimKinder.Update(dt);
				timeCooldown.Update(dt);
				if(timeCooldown.Get() > 0.5){
					animShowing = false;
					timeCooldown.Restart();
				}
			}
		}
	}

	if(!showingInventory && !hidden && !Camera::GetMoving() && !animShowing){
		direcaoShift = false;
		if(InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(MissionManager::missionManager->movingBox && (direcao == NORTE || direcao == SUL)){
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
			if(MissionManager::missionManager->movingBox && (direcao == NORTE || direcao == SUL)){
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
			if(MissionManager::missionManager->movingBox && (direcao == LESTE || direcao == OESTE)){
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
			if(MissionManager::missionManager->movingBox && (direcao == LESTE || direcao == OESTE)){
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

		if(!aboveObject){
			if(speed.x != 0 || speed.y != 0){
				spKinder.Update(dt, direcao, direcaoShift);
				spKinderRun.Update(dt, direcao, direcaoShift);
				spKinderPush.Update(dt, direcao - 2, direcaoShift);

				if(running) multiplicador = 10;
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
		} else {
			spKinder.Update(0, direcao, direcaoShift);
			multiplicador = 0.5;
		}

		AddRuido(0.2 * multiplicador);

		if(multiplicador == 0 && ruido > 0){
			timeRuido.Update(dt);
			if (timeRuido.Get() > 0.3){
				timeRuido.Restart();
				ruido -= (ruido*0.2);
				//std::cout << ruido << std::endl;
			}
		}

		if(!aboveObject){
			//printf("%f\n", ruido);
			bool bloqMov = false;
			Rect boxAux = box;
			boxAux.x += speed.x; boxAux.y += speed.y;
			for(unsigned int i = 0; i < wallLimits.size(); i++){
				bloqMov = boxAux.Collide(wallLimits[i]);
				if(bloqMov == true) break;
			}

			if(boxAux.x < limits.w - box.w && boxAux.x > limits.x && !bloqMov){
				previousPos.x = box.x;
				box.x += speed.x;
			}
			if(boxAux.y < limits.h - box.h && boxAux.y > limits.y && !bloqMov){
				previousPos.y = box.y;
				box.y += speed.y;
			}
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

	//Ajustar quando puxa apos empurrar
	MissionManager::missionManager->movingBox = false;

}

bool Player::NotifyCollision(GameObject& other){
	/*if(other.Is("Enemy")){
		//hp = 0;
		//Camera::Unfollow();
		//printf("CAUGHT YOU!");
	}*/
	return false;
}

void Player::Render(){
	if(!hidden && !animShowing){
		if(MissionManager::missionManager->movingBox && (direcao == LESTE || direcao == OESTE)){
			spKinderPush.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else if(running){
			spKinderRun.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else{
			spKinder.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		}
	} else if(animShowing){
		spAnimKinder.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
	}
}

bool Player::IsDead(){
	return (hp <= 0);
}

bool Player::Is(std::string type){
	return (type == "Player");
}

/* FUNCOES ESPECIFICAS */

void Player::SetPosition(int x, int y){
	box.x = x; box.y = y;
}

void Player::SetDirecao(int dir){
	direcao = (InvBox) dir;
	spKinder.SetFrame(1, direcao);
	spKinderRun.SetFrame(1, direcao);
}

bool Player::CollidingPlayer(Rect boxCol, int offset){
	/*if(MissionManager::player->box.x < box.x + box.w ||
			MissionManager::player->box.x + MissionManager::player->box.w > box.x){
		MissionManager::player->box.x = MissionManager::player->previousPos.x;
	}
	if(MissionManager::player->box.y < box.y + box.h ||
			MissionManager::player->box.y + MissionManager::player->box.h > box.y){
		MissionManager::player->box.y = MissionManager::player->previousPos.y;
	}*/
	bool invert = false;
	if(!aboveObject && (box.y + box.h - offset < boxCol.y + boxCol.h)){

		if(box.y + offset < boxCol.y){
			//std::cout << "HIDDING" << std::endl;
			invert = true;
		} else if((box.x < boxCol.x + boxCol.w && box.x + box.w > boxCol.x + boxCol.w) ||
				(boxCol.InsideX(box) && box.CenterX() >= boxCol.CenterX())){
			if(GetDirecao() == Player::SUL || GetDirecao() == Player::NORTE){
				if(GetDirecao() == Player::SUL) invert = true;
				box.x = previousPos.x;
				box.y = previousPos.y;
			} else{
				box.x = previousPos.x;//boxCol.x + boxCol.w + 1; -> dava problema em borda
			}
		} else if((box.x + box.w > boxCol.x && box.x < boxCol.x) ||
					(boxCol.InsideX(box) && box.CenterX() < boxCol.CenterX())){
			if(GetDirecao() == Player::SUL || GetDirecao() == Player::NORTE){
				if(GetDirecao() == Player::SUL) invert = true;
				box.x = previousPos.x;
				box.y = previousPos.y;
			} else{
				box.x =  previousPos.x;//boxCol.x - box.w - 1;
			}
		}

	}

	return invert;
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

void Player::SetMovementLimits(Rect limits){
	this->limits = limits;
}

void Player::AddWallLimits(Rect limits){
	wallLimits.emplace_back(limits);
}

void Player::ResetWallLimits(){
	wallLimits.clear();
}

void Player::ChangeHiddenState(){
	hidden = !hidden;
	timeCooldown.Restart();
}

void Player::ChangeAboveObject(){
	aboveObject = !aboveObject;
}

bool Player::GetAboveObject(){
	return aboveObject;
}

int Player::GetDirecao(){
	return direcao;
}

Vec2 Player::GetSpeed(){
	return speed;
}

void Player::SetDoor(bool value){
	door = value;
}

bool Player::GetDoor(){
	return door;
}

void Player::AddRuido(float add){
	ruido += add;
	if (ruido > 96) ruido = 96; // impedir bug na mostra -> quando for 10 sera 108
}

float Player::GetRuido(){
	return ruido;
}

void Player::AddInventory(std::string obj){
	// Coloquei os parametros como as strings e nao o objeto, pq estava dando erro comigo
	// Coloquei a string da imagem comentada caso seja necessario

	lastPicked = obj;
	if(inHandIndex < 0) inHandIndex = 0;
	if(obj == "InventoryKey"){
		inventory.emplace_back(new InventoryKey());
	} else if(obj == "InventoryClown"){
		inventory.emplace_back(new InventoryClown());
	}else if(obj == "InventoryBear"){
		inventory.emplace_back(new InventoryBear());
	}
}

std::vector<std::shared_ptr<InventoryObject>> Player::GetInventory(){
	return inventory;
}

std::vector<std::string> Player::GetStringInventory(){
	std::vector<std::string> oldInventory;
	for(unsigned int i = 0; i < inventory.size(); i++){
		std::string aux = std::move(inventory[i]->GetObject());
		oldInventory.emplace_back(aux);
	}
	return oldInventory;
}

bool Player::GetShowingInventory(){
	return showingInventory;
}

std::shared_ptr<InventoryObject> Player::GetInHand(){
	if(inHandIndex >= 0) return inventory[inHandIndex];
	else return nullptr;
}

int Player::GetInHandIndex(){
	return inHandIndex;
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
	int posX, posY, aux;
	int offset = 10;
	posX = SCREEN_SIZE_W - 18*offset;
	posY = offset;

	aux = (ruido/12) + 1;
	spNoise.SetFrame(aux);
	spNoise.Render(posX, posY, 0);

}
