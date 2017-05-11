#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include "GameObject.h"
#include <vector>
#include <memory>

class State {
public:
	State();
	virtual ~State();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void AddObject(GameObject *ptr);

	bool PopRequested();
	bool QuitRequested();

protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool popRequested;
	bool quitRequested;

	std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif /* SRC_STATE_H_ */
