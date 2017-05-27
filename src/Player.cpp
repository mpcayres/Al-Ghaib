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
	spInventory.SetScaleX(2);
	spInventory.SetScaleY(2);
	spInventorybox = Sprite("img/box.png", 1, 1, 1);
	spInventorybox.SetScaleX(1.5);
	spInventorybox.SetScaleY(1.5);
	spInventoryboxSelected = Sprite("img/box-select.png", 1, 1, 1);

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
		if(InputInstance.KeyPress(I_KEY))
			showingInventory = true;
	}else{
		if(InputInstance.KeyPress(I_KEY))
			showingInventory = false;
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
		printf("CAUGHT YOU!");

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
	int posX, posY, posXCaixa, posYCaixa;
	int bordaX, bordaY;
	int widthMinorSquare, heightMinorSquare;

	bordaX = spInventory.GetScaledWidth()/9;
	bordaY = spInventory.GetScaledHeight()/8;

	posXCaixa = Game::GetInstance().GetWidth()/2 - (spInventory.GetScaledWidth()/2);
	posYCaixa = Game::GetInstance().GetHeight()/2 - (spInventory.GetScaledHeight()/2);
	spInventory.Render(posXCaixa,posYCaixa, 0);

	posX = posXCaixa + bordaX;
	posY = posYCaixa + bordaY + 40;

	widthMinorSquare = spInventorybox.GetScaledWidth()/2;
	heightMinorSquare = spInventorybox.GetScaledHeight()/2;
	for(unsigned i = 0; i < inventory.size() && i < 16 ;i++) {
		spInventorybox.Render(posX, posY, 0);
		inventory[i]->Render(posX, posY);

		posX += bordaX*2;
		if(posX >= posXCaixa + bordaX*8){
			posX = posXCaixa + bordaX;
			posY += bordaY*1.5;
		}
	}
}

void Player::AddInventory(std::string obj/*, std::string objSp*/){
	// Coloquei os parametros como as strings e nao o objeto, pq estava dando erro comigo
	// Coloquei a string da imagem comentada caso seja necessario
	if(obj == "KeyObject"){
		inventory.emplace_back(new InventoryKey(/*objSp*/));
	}
}

int Player::GetDirecao(){
	return direcao;
}

Vec2 Player::GetSpeed(){
	return speed;
}
