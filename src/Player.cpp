#include "Player.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "InventoryKey.hpp"
#include "InventoryArame.hpp"
#include "InventoryClown.hpp"
#include "InventoryBear.hpp"
#include "InventoryWool.hpp"
#include "InventoryScissors.hpp"
#include "InventoryNeedle.hpp"
#include "InventoryControl.hpp"
#include "InventoryLine.hpp"
#include "Sound.hpp"
#include <iostream>

#define MODULO_SPEED			5
#define AUMENTO_VELOCIDADE		2
#define DESACELERA				1
#define MODULO_SPEED_DROGADO	2


Player::Player(float x, float y, int oldInHand, std::vector<std::string> oldInventory) :
		spKinder("img/sprite-kinder.png", 20, 0.06, 4),
		spKinderRun("img/sprite-kinder-run.png", 15, 0.1, 4),
		spAnimKinder("img/sprite-kinder-breaking.png", 6, 0.4, 1),
		spKinderPush("img/sprite-kinder-push.png", 6, 0.1, 4),
		spKinderClimbing("img/sprite-kinder-climb.png", 12, 0.13, 4),
		spKinderDown("img/sprite-kinder-down.png", 6, 0.13, 4) {
	spKinder.SetScaleX(2.5); spKinder.SetScaleY(2.5);
	spKinderRun.SetScaleX(2.5); spKinderRun.SetScaleY(2.5);
	spAnimKinder.SetScaleX(2.5); spAnimKinder.SetScaleY(2.5);
	spKinderPush.SetScaleX(2.5); spKinderPush.SetScaleY(2.5);
	spKinderClimbing.SetScaleX(2.5); spKinderClimbing.SetScaleY(2.5);
	spKinderDown.SetScaleX(2.5); spKinderDown.SetScaleY(2.5);

	spNoise = Sprite("img/sprite-energia.png", 9, 1 ,1);
	spNoise.SetScaleX(0.5); spNoise.SetScaleY(0.5);

	spInventory = Sprite("img/inventory.png", 1, 1, 1);
	spInventory.SetScaleX(2); spInventory.SetScaleY(2);
	spInventorybox = Sprite("img/box.png", 1, 1, 1);
	spInventorybox.SetScaleX(1.6); spInventorybox.SetScaleY(1.6);
	spInventoryboxSelected = Sprite("img/box-select.png", 1, 1, 1);
	spInventoryboxSelected.SetScaleX(1.6); spInventoryboxSelected.SetScaleY(1.6);

	box.x = x; box.y = y;
	box.w = spKinder.GetScaledWidth();
	box.h = spKinder.GetScaledHeight();
	previousPos = Vec2(x,y);
	timeRuido = Timer();
	timeCooldown = Timer();
	timeSound = Timer();
	timePicked = Timer();

	rotation = 0;
	speed.y = speed.x = 0;
	running = false;

	for(unsigned int i = 0; i < oldInventory.size(); i++){
		AddInventory(oldInventory[i]);
	}
	oldInventory.clear();

	inHandIndex = oldInHand; //dependendo do save pode ser diferente
	showingInventory = false;
	showPicked = false;
	inventoryIndex = inHandIndex;

	direcao = LESTE;
	direcaoShift = false;

	ruido = 0;
	dirDown = 0;
	centerMX = centerMY = 0;

	drogado = false;
	hidden = false;
	animShowing = false;
	door = false;
	aboveObject = false;
	blocked = false;
	lastPicked = "";
	bloqHUD = false;
	bloqInv = false;
	climbing = false;
	climbingDown = false;
}

Player::~Player(){
	inventory.clear();
}

/* FUNCOES GERAIS */

void Player::Update(float dt){
	int multiplicador;
	InputInstance = InputManager::GetInstance();
	if(!showingInventory && !hidden && !Camera::GetMoving() && !aboveObject && !blocked && !climbing && !climbingDown){
		std::shared_ptr<InventoryObject> inHand = GetInHand();
		if(inHand != nullptr){
			if(InputManager::GetInstance().KeyPress(X_KEY) && inHand->IsObject("InventoryClown")){
				animShowing = true;
				timeCooldown.Restart();
				if(inHand->Action(nullptr) == true){
					MissionManager::player->DeleteInventory();
					AddInventory("InventoryArame");
				}
			} else if(InputManager::GetInstance().KeyPress(X_KEY) && inHand->IsObject("InventoryControl")){
				inHand->Action(nullptr);
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
	if(!showingInventory && !hidden && !Camera::GetMoving() && !animShowing && !blocked && climbing){
		spKinderClimbing.Update(dt, dirDown, false);
		timeCooldown.Update(dt);
		if(timeCooldown.Get() >= 1.56){
			box.x = centerMX;
			box.y = centerMY - 18;
			spKinderClimbing.SetFrame(0, dirDown);
			spKinder.SetFrame(10, dirDown);

			climbing = false;
			timeCooldown.Restart();
		}
	} else if(!showingInventory && !hidden && !Camera::GetMoving() && !animShowing && !blocked && climbingDown){
		spKinderDown.Update(dt, dirDown > 1 ? dirDown - 2 : dirDown + 2, false);
		timeCooldown.Update(dt);
		if(timeCooldown.Get() >= 0.78){
			if(dirDown == LESTE){
				box.x -= 16;
				box.y += 24;
			} else if(dirDown == OESTE){
				box.x += 36;
				box.y += 24;
			} else if(dirDown == NORTE){
				box.x = centerMX;
				box.y += 40;
			}
			spKinderDown.SetFrame(0, dirDown > 1 ? dirDown - 2 : dirDown + 2);

			ChangeAboveObject();
			climbingDown = false;
			timeCooldown.Restart();
		}
	}

	if(!showingInventory && !hidden && !Camera::GetMoving() && !animShowing && !blocked && !climbing && !climbingDown){
		direcaoShift = false;

		//SETA PARA CIMA//
		if((InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY))){
			if(MissionManager::missionManager->movingBox && (direcao == NORTE || direcao == SUL)){
				if(direcao == SUL) direcaoShift = true;
			} else{
				direcao = NORTE;
				if(drogado)
					direcao = SUL;
			}
			speed.y = -MODULO_SPEED;
			if(drogado)
				speed.y = MODULO_SPEED/2;
			speed.x = 0;
			//rotation = -90;
			//nao pode ficar fora, senao o movimento fica bugado
			Running(InputInstance);

		//SETA PARA BAIXO //
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(MissionManager::missionManager->movingBox && (direcao == NORTE || direcao == SUL)){
				if(direcao == NORTE) direcaoShift = true;
			} else{
				direcao = SUL;
				if(drogado)
					direcao = NORTE;
			}
			speed.y = MODULO_SPEED;
			if(drogado)
				speed.y = -MODULO_SPEED/2;
			speed.x = 0;
			//rotation = 90;
			Running(InputInstance);

			//SETA PARA DIREITA //
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(MissionManager::missionManager->movingBox && (direcao == LESTE || direcao == OESTE)){
				if(direcao == OESTE) direcaoShift = true;
			} else{
				direcao = LESTE;
				if(drogado)
					direcao = OESTE;
			}
			speed.x = MODULO_SPEED;
			if(drogado)
				speed.x = -MODULO_SPEED/2;
			speed.y = 0;
			//rotation = 0;
			Running(InputInstance);

			//SETA PARA DIREITA//
		} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
				!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
			if(MissionManager::missionManager->movingBox && (direcao == LESTE || direcao == OESTE)){
				if(direcao == LESTE) direcaoShift = true;
			} else{
				direcao = OESTE;
				if(drogado)
					direcao = LESTE;
			}
			speed.x = -MODULO_SPEED;
			if(drogado)
				speed.x = MODULO_SPEED/2;
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
				spKinderPush.Update(dt, direcao, direcaoShift);

				if(running) multiplicador = 6;
				else multiplicador = 1;

				if(MissionManager::missionManager->movingBox) multiplicador += 2;
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

		if(!bloqHUD){
			if(InputInstance.KeyPress(I_KEY) && !bloqInv){
				showingInventory = true;
				inventoryIndex = inHandIndex;
			}
			if(InputInstance.KeyPress(G_KEY)){
				Camera::Move(box.x+100, box.y+100, 3);
			}
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
		if(InputInstance.KeyPress(X_KEY) || InputInstance.KeyPress(ENTER_KEY)){
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
		if(timeCooldown.Get() > 3){
			ChangeHiddenState();
		}
	}

	if(MissionManager::missionManager->movingBox){
		if(timeSound.Get() == 0){
			Sound s = Sound("audio/arrastando.wav");
			s.Play(0);
			timeSound.Update(dt);
		} else if(timeSound.Get() > 0.8){
			timeSound.Restart();
		} else timeSound.Update(dt);
	}

	if(hidden){
		if(timeSound.Get() == 0){
			Sound s = Sound("audio/one-beat.wav");
			s.Play(0);
			timeSound.Update(dt);
		} else if(timeSound.Get() > 1){
			timeSound.Restart();
		} else timeSound.Update(dt);
	}

	MissionManager::missionManager->movingBox = false;
	if(showPicked){
		timePicked.Update(dt);
		if(timePicked.Get() > 2) showPicked = false;
	}

}

bool Player::NotifyCollision(GameObject& other){
	return false;
}

void Player::Render(){
	if(!hidden && !animShowing){
		if(climbing){
			spKinderClimbing.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else if(climbingDown){
			spKinderDown.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else if(MissionManager::missionManager->movingBox){
			spKinderPush.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else if(running){
			spKinderRun.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		} else{
			spKinder.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
		}
	} else if(animShowing && !climbing && !climbingDown){
		spAnimKinder.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
	}
}

bool Player::IsDead(){
	return false;
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

void Player::SetBlocked(bool b){
	blocked = b;
}

bool Player::CollidingPlayer(Rect boxCol, float offset){
	/*if(MissionManager::player->box.x < box.x + box.w ||
			MissionManager::player->box.x + MissionManager::player->box.w > box.x){
		MissionManager::player->box.x = MissionManager::player->previousPos.x;
	}
	if(MissionManager::player->box.y < box.y + box.h ||
			MissionManager::player->box.y + MissionManager::player->box.h > box.y){
		MissionManager::player->box.y = MissionManager::player->previousPos.y;
	}*/
	//std::cout << "OFFSET " << offset << std::endl;
	bool invert = false;
	if(!aboveObject && (box.y + offset < boxCol.y + boxCol.h)){

		if(box.y + box.h - offset < boxCol.y){
			//std::cout << "HIDDING " << std::endl;
			invert = true;
		} else if((box.x < boxCol.x + boxCol.w && box.x + box.w > boxCol.x + boxCol.w) ||
					(boxCol.InsideX(box) && box.CenterX() >= boxCol.CenterX())){
			//if(boxCol.InsideX(box) && box.CenterX() >= boxCol.CenterX()) std::cout << "11" << std::endl;
			//if(box.x < boxCol.x + boxCol.w && box.x + box.w > boxCol.x + boxCol.w) std::cout << "22" << std::endl;
			if(GetDirecao() == Player::SUL) invert = true;

			box.x = previousPos.x;
			box.y = previousPos.y;
		} else if((box.x + box.w > boxCol.x && box.x < boxCol.x) ||
					(boxCol.InsideX(box) && box.CenterX() < boxCol.CenterX())){
			//if(boxCol.InsideX(box) && box.CenterX() < boxCol.CenterX()) std::cout << "33" << std::endl;
			//if(box.x + box.w > boxCol.x && box.x < boxCol.x) std::cout << "44" << std::endl;
			if(GetDirecao() == Player::SUL) invert = true;

			box.x = previousPos.x;
			box.y = previousPos.y;
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

void Player::SetBloqHUD(bool value){
	bloqHUD = value;
}

bool Player::GetBloqHUD(){
	return bloqHUD;
}

void Player::SetBloqInv(bool value){
	bloqInv = value;
}

bool Player::GetBloqInv(){
	return bloqInv;
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

	if(obj == "InventoryKey"){
		spPicked = Sprite("img/object-key.png");
		spPicked.SetScaleX(6); spPicked.SetScaleY(6);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryKey());
	} else if(obj == "InventoryArame"){
		spPicked = Sprite("img/object-arame.png");
		spPicked.SetScaleX(4); spPicked.SetScaleY(4);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryArame());
	} else if(obj == "InventoryClown"){
		spPicked = Sprite("img/object-caixa-sem-palhaco.png");
		spPicked.SetScaleX(4); spPicked.SetScaleY(4);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryClown());
	} else if(obj == "InventoryBear"){
		/*spPicked = Sprite("img/object-bear.png");
		spPicked.SetScaleX(10); spPicked.SetScaleY(10);
		timePicked.Restart(); showPicked = true;*/
		inventory.emplace_back(new InventoryBear());
	} else if(obj == "InventoryWool"){
		spPicked = Sprite("img/obj_novelo.png");
		spPicked.SetScaleX(5); spPicked.SetScaleY(5);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryWool());
	} else if(obj == "InventoryNeedle"){
		spPicked = Sprite("img/object-needle.png");
		spPicked.SetScaleX(5); spPicked.SetScaleY(5);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryNeedle());
	} else if(obj == "InventoryScissors"){
		spPicked = Sprite("img/object-scissors.png");
		spPicked.SetScaleX(5); spPicked.SetScaleY(5);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryScissors());
	} else if(obj == "InventoryControl"){
		spPicked = Sprite("img/object-control.png");
		spPicked.SetScaleX(5); spPicked.SetScaleY(5);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryControl());
	}else if(obj == "InventoryLine"){
		spPicked = Sprite("img/object-carretel.png");
		spPicked.SetScaleX(5); spPicked.SetScaleY(5);
		timePicked.Restart(); showPicked = true;
		inventory.emplace_back(new InventoryLine());
	}

	lastPicked = obj;
	inHandIndex = inventory.size() - 1;
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

bool Player::HaveObject(std::string obj){
	for(unsigned int i = 0; i < inventory.size(); i++){
		if(inventory[i]->GetObject() == obj) return true;
	}
	return false;
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
		inHandIndex = 0;
	}
}

void Player::RenderInventory(){
	if(!bloqHUD){
		int posX, posY, posXCenter, posYCenter, posXCaixa, posYCaixa;
		int bordaX, bordaY;
		int widthMinorSquare, heightMinorSquare;

		bordaX = spInventory.GetScaledWidth()/9;
		bordaY = spInventory.GetScaledHeight()/8;
		widthMinorSquare = spInventorybox.GetScaledWidth() - 10;
		heightMinorSquare = spInventorybox.GetScaledHeight() - 10;

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
				float scaleX = (float) ((float) widthMinorSquare)/((float) inventory[i]->GetWidth());
				inventory[i]->SetScaleX(scaleX);
			}
			if(inventory[i]->GetHeight() > heightMinorSquare){
				float scaleY = (float) ((float) heightMinorSquare)/((float) inventory[i]->GetHeight());
				inventory[i]->SetScaleY(scaleY);
			}
			posXCenter = posX + 5 + (widthMinorSquare - inventory[i]->GetWidth())/2;
			posYCenter = posY + 5 + (heightMinorSquare - inventory[i]->GetHeight())/2;
			inventory[i]->Render(posXCenter, posYCenter);

			posX += bordaX*2;
			if(posX >= posXCaixa + bordaX*8){
				posX = posXCaixa + bordaX;
				posY += bordaY*1.5;
			}

		}
	}
}

void Player::RenderInHand(){
	if(!bloqHUD){
		int posX, posY;
		int offset = 10, widthMinorSquare, heightMinorSquare;
		int posXCenter, posYCenter;
		posX = SCREEN_SIZE_W - 8*offset;
		posY = offset;
		widthMinorSquare = spInventorybox.GetScaledWidth() - 10;
		heightMinorSquare = spInventorybox.GetScaledHeight() - 10;

		spInventoryboxSelected.Render(posX, posY, 0);
		if(inHandIndex >= 0){
			if(inventory[inHandIndex]->GetWidth() > widthMinorSquare){
				float scaleX = (float) ((float) widthMinorSquare)/((float) inventory[inHandIndex]->GetWidth());
				inventory[inHandIndex]->SetScaleX(scaleX);
			}
			if(inventory[inHandIndex]->GetHeight() > heightMinorSquare){
				float scaleY = (float) ((float) heightMinorSquare)/((float) inventory[inHandIndex]->GetHeight());
				inventory[inHandIndex]->SetScaleY(scaleY);
			}
			posXCenter = posX + 5 + (widthMinorSquare - inventory[inHandIndex]->GetWidth())/2;
			posYCenter = posY + 5 + (heightMinorSquare - inventory[inHandIndex]->GetHeight())/2;
			inventory[inHandIndex]->Render(posXCenter, posYCenter);
		}

		if(spPicked.IsOpen() && showPicked){
			spPicked.Render(Game::GetInstance().GetWidth()/2 - spPicked.GetScaledWidth()/2,
					Game::GetInstance().GetHeight()/2 - spPicked.GetScaledHeight()/2, 0);
		}
	}
}

void Player::RenderNoise(){
	if(!bloqHUD){
		int posX, posY, aux;
		int offset = 10;
		posX = SCREEN_SIZE_W - 18*offset;
		posY = offset;

		aux = (ruido/12) + 1;
		spNoise.SetFrame(aux);
		spNoise.Render(posX, posY, 0);
	}
}
