#include "Player.hpp"
#include "InputManager.hpp"
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
	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();
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
	InputManager InputInstance = InputManager::GetInstance();

	if(InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		direcao = NORTE;
		speed.y = -MODULO_SPEED;
		speed.x = 0;
		//rotation = -90;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		direcao = SUL;
		speed.y = MODULO_SPEED;
		speed.x = 0;
		//rotation = 90;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		direcao = LESTE;
		speed.x = MODULO_SPEED;
		speed.y = 0;
		//rotation = 0;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		direcao = OESTE;
		speed.x = -MODULO_SPEED;
		speed.y = 0;
		//rotation = 180;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		speed.x = 0;
		speed.y = 0;
	}

	if(InputInstance.IsKeyDown(LSHIFT_KEY)){
		speed.x *= AUMENTO_VELOCIDADE;
		speed.y *= AUMENTO_VELOCIDADE;
		running = true;
	} else
		running = false;

	//Deixei essa parte aqui pra caso preciso em outro caso
	//if(colliding && dirCollision == direcao){
		//Tentei isso de baixo tbm, mas ficou comédia
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
	//}

	/*if(InputInstance.MousePress(LEFT_MOUSE_BUTTON && time.Get() >= 0.3)) {
		time.Restart();
		//Shoot();
	}

	time.Update(dt);*/

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

void Player::NotifyCollision(GameObject& other){
	if(other.Is("SceneObject")){
		colliding = true;
		dirCollision = direcao;
	}
	if(other.Is("Bullet")){
		if(((Bullet&) other).targetsPlayer)
			hp -= 8;
	}
	if(other.Is("Alien")){
		hp = 0;
	}
	if(hp <= 0){
		Sound sound = Sound("audio/boom.wav");
		sound.Play(0);
		Camera::Unfollow();
		Game::GetInstance().GetCurrentState().AddObject(
				new Animation(box.Center().x, box.Center().y, rotation,
						"img/penguindeath.png", 5, 0.18, true));
	}
}

bool Player::Is(std::string type){
	return (type == "Player");
}

bool Player::getRunning(){
	return running;
}

bool Player::GetShowingInventory(){
	return showingInventory;
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
// Causava erro na compilacao, pq e unique_ptr
/*std::vector<std::unique_ptr<InventoryObject>> Player::GetInventory(){
	return inventory;
}*/
