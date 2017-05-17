#include "Penguins.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"

Penguins* Penguins::player;

Penguins::Penguins(float x, float y): bodySp("img/penguin.png"), cannonSp("img/cubngun.png"){
	box.h = bodySp.GetHeight();
	box.w = bodySp.GetWidth();
	AuxCannon.w = cannonSp.GetWidth();
	AuxCannon.h = cannonSp.GetHeight();

	box.x = x;
	box.y = y;

	time = Timer();

	hp = 30;
	cannonAngle = 0;
	linearSpeed = 0;
	rotation = 0;
	speed.y = speed.x = 0;
	player = this;

	deltaX = (box.w - AuxCannon.w)/2;
	deltaY = (AuxCannon.h - box.h)/2;
	AuxCannon.x = box.x - deltaX;
	AuxCannon.y = box.y + deltaY;
}

Penguins::~Penguins(){
	player = nullptr;
}

void Penguins::Update(float dt){
	Vec2 CannonAuxCamera;
	Vec2 mouseAux;
	InputManager InputInstance = InputManager::GetInstance();
	int aceleracaoLinear = 5;
	float velocidadeAngular = 5;
	int limite = 15;

	if(InputInstance.IsKeyDown(W_KEY)){
		if(linearSpeed < limite){
			linearSpeed += aceleracaoLinear*dt;
		}
	} else if(InputInstance.IsKeyDown(S_KEY)){
		if(linearSpeed > -1*limite){
			linearSpeed -= aceleracaoLinear*dt;
		}
	}else if(abs(linearSpeed) > 0){
		if(linearSpeed < 0){
			linearSpeed += (aceleracaoLinear*dt*3);
			if (linearSpeed > 0) linearSpeed = 0;
		}else{
			linearSpeed -= (aceleracaoLinear*dt*3);
			if (linearSpeed < 0) linearSpeed = 0;
		}
	}

	if(InputInstance.IsKeyDown(A_KEY)){
		rotation -= velocidadeAngular;
	} else if(InputInstance.IsKeyDown(D_KEY)){
		rotation += velocidadeAngular;
	}

	speed.y = 0;
	speed.x = linearSpeed;
	speed = speed.Rotate(rotation * 0.017);

	if(box.y + speed.y < 1280 - box.h && box.y + speed.y > 0){
		box.y += speed.y;
	}
	if(box.x + speed.x < 1408 - box.w && box.x + speed.x > 0){
		box.x += speed.x;
	}
	AuxCannon.x = box.x + deltaX;
	AuxCannon.y = box.y - deltaY;

	mouseAux.x = InputInstance.GetMouseX();
	mouseAux.y = InputInstance.GetMouseY();
	CannonAuxCamera.x = AuxCannon.x + Camera::pos.x;
	CannonAuxCamera.y = AuxCannon.y+ Camera::pos.y;

	cannonAngle = mouseAux.Sub(CannonAuxCamera).Angle();

	if(InputInstance.MousePress(LEFT_MOUSE_BUTTON && time.Get() >= 0.3)) {
		time.Restart();
		Shoot();
	}

	time.Update(dt);
}

void Penguins::Render(){
	bodySp.Render(box.x + Camera::pos.x, box.y + Camera::pos.y, rotation);
	cannonSp.Render(AuxCannon.x + Camera::pos.x, AuxCannon.y+ Camera::pos.y, cannonAngle * 58);
}

bool Penguins::IsDead(){
	return (hp <= 0);
}


void Penguins::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
	aux = aux.Rotate(cannonAngle);
	Game::GetInstance().GetCurrentState().AddObject(new Bullet(AuxCannon.x + aux.x + AuxCannon.w/2,
			AuxCannon.y + aux.y + AuxCannon.h/2, cannonAngle,300,700,"img/penguinbullet.png", 4, 0.5, true));
}

void Penguins::NotifyCollision(GameObject& other){
	Sound sound = Sound("audio/boom.wav");
	if(other.Is("Bullet")){
		if(((Bullet&) other).targetsPlayer)
			hp -= 8;
	 }
	if(other.Is("Alien")){
		hp = 0;
	}
	if(hp <= 0){
		sound.Play(0);
		Camera::Unfollow();
		Game::GetInstance().GetCurrentState().AddObject(
				new Animation(box.Center().x, box.Center().y, rotation,
						"img/penguindeath.png", 5, 0.18, true));
	}
}

bool Penguins::Is(std::string type){
	return (type == "Penguins");
}
