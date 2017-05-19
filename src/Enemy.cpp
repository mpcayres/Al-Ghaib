#include "Enemy.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"

#define MODULO_SPEED 8
#define AUMENTO_VELOCIDADE 2


Enemy* Enemy::enemy;

Enemy::Enemy(float x, float y): bodySp("img/alien.png"){
	box.h = bodySp.GetHeight();
	box.w = bodySp.GetWidth();

	box.x = x;
	box.y = y;

	time = Timer();

	hp = 30;
	rotation = 0;
	speed.y = speed.x = 0;
	enemy = this;
}

Enemy::~Enemy(){
	enemy = nullptr;
}

void Enemy::Update(float dt){
	/* dinamica de percepcao de ruido vindo do jogador*/
	//printf("\n Distancia para jogador");

	float dist = 0;
	//int running = 1;
	dist = box.DistanceRect(Player::player->box);
	//printf("%f", dist);
	//if(dist < 250)
		//printf("VISTO!");

	//printf("\nQuantidade de percepção de ruído acrescentada:");
	if(Player::player->getRunning() == true)
		running = 10;
	else
		running = 1;
	//float noise = ((1/dist)*10)*running;
	//printf("%f", noise);
	/*InputManager InputInstance = InputManager::GetInstance();

	if(InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		speed.y = -MODULO_SPEED;
		speed.x = 0;
		rotation = -90;
		if(InputInstance.IsKeyDown(LSHIFT_KEY)){
			speed.x *= AUMENTO_VELOCIDADE;
			speed.y *= AUMENTO_VELOCIDADE;
			running = true;
		}
		else
			running = false;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		speed.y = MODULO_SPEED;
		speed.x = 0;
		rotation = 90;
		if(InputInstance.IsKeyDown(LSHIFT_KEY)){
			speed.x *= AUMENTO_VELOCIDADE;
			speed.y *= AUMENTO_VELOCIDADE;
			running = true;
		}
		else
			running = false;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		speed.x = MODULO_SPEED;
		speed.y = 0;
		rotation = 0;
		if(InputInstance.IsKeyDown(LSHIFT_KEY)){
			speed.x *= AUMENTO_VELOCIDADE;
			speed.y *= AUMENTO_VELOCIDADE;
			running = true;
		}
		else
			running = false;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		speed.x = -MODULO_SPEED;
		speed.y = 0;
		rotation = 180;
		if(InputInstance.IsKeyDown(LSHIFT_KEY)){
			speed.x *= AUMENTO_VELOCIDADE;
			speed.y *= AUMENTO_VELOCIDADE;
			running = true;
		}
		else
			running = false;
	} else if(!InputInstance.IsKeyDown(UP_ARROW_KEY) && !InputInstance.IsKeyDown(DOWN_ARROW_KEY) &&
			!InputInstance.IsKeyDown(RIGHT_ARROW_KEY) && !InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		speed.x = 0;
		speed.y = 0;
	}


	if(InputInstance.IsKeyDown(LEFT_ARROW_KEY)){
		//rotation -= velocidadeAngular;
	} else if(InputInstance.IsKeyDown(RIGHT_ARROW_KEY)){
		//rotation += velocidadeAngular;
	}*/

	if(box.y + speed.y < 1280 - box.h && box.y + speed.y > 0){
		box.y += speed.y;
	}
	if(box.x + speed.x < 1408 - box.w && box.x + speed.x > 0){
		box.x += speed.x;
	}
	
	//if(InputInstance.MousePress(LEFT_MOUSE_BUTTON && time.Get() >= 0.3)) {
	//	time.Restart();
		//Shoot();
	//}

	time.Update(dt);
}

void Enemy::Render(){
	bodySp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Enemy::IsDead(){
	return (hp <= 0);
}


void Enemy::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
	//aux = aux.Rotate(cannonAngle);
}

void Enemy::NotifyCollision(GameObject& other){
	/*Sound sound = Sound("audio/boom.wav");
	if(other.Is("Bullet")){
		if(((Bullet&) other).targetsEnemy)
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
*/

}

bool Enemy::Is(std::string type){
	return (type == "Enemy");
}
