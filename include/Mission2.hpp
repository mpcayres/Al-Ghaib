#ifndef SRC_MISSION2_HPP_
#define SRC_MISSION2_HPP_

#include "Mission.hpp"

class Mission2 : public Mission {
public:
	Mission2();
	~Mission2();

	void Pause();
	void Resume();

	void Update(float dt);
	void Render();
private:
	void SetObjectStage();
	void SetObjectHall();
};

#endif /* SRC_MISSION2_HPP_ */
