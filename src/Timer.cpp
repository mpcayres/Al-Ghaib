#include "Timer.hpp"

Timer::Timer(){
	time = 0;
}

void Timer::Update(float dt){
	time += dt;
}

void Timer::Restart(){
	time = 0;
}

float Timer::Get(){
	return time;
}

void Timer::Set(float t){
	time = t;
}
