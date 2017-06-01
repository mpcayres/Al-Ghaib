#ifndef SRC_MISSION1_HPP_
#define SRC_MISSION1_HPP_

#include "Mission.hpp"

class Mission1 : public Mission {
public:
	Mission1();
	~Mission1();

protected:
	void SetObjectStage();
	void SetObjectHall();
};

#endif /* SRC_MISSION1_HPP_ */
