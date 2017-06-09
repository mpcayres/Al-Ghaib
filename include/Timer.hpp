#ifndef INCLUDE_TIMER_HPP_
#define INCLUDE_TIMER_HPP_

class Timer{
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
	void Set(float t);

private:
	float time;
};

#endif /* INCLUDE_TIMER_HPP_ */
