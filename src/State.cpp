#include "State.hpp"

State::State(){
	quitRequested = false;
	popRequested = false;
}

State::~State(){
	objectArray.clear();
}

void State::AddObject(GameObject *object){
	objectArray.emplace_back(object);
}

void State::UpdateArray(float dt){
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i].get()->Update(dt);
		if(objectArray[i].get()->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray(){
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i].get()->Render();
	}
}

bool State::QuitRequested(){
	return quitRequested;
}

bool State::PopRequested(){
	return popRequested;
}

//esta funcionando sem remover, pq e estatico. As formas que achei acabam deletando o proprio player
/*void State::RemovePlayer(std::string s){
	/*std::vector<unique_ptr<GameObject>>::iterator object = 
        find_if(objectArray.begin(), objectArray.end(),
                [&](unique_ptr<GameObject> & obj){ return obj->name() == objName;}
               );
    objectArray.erase(std::remove(objectArray.begin(), objectArray.end(), *object));
    return std::move(*object);/
    /*objectArray.erase(std::remove_if(
        objectArray.begin(), objectArray.end(), [s](const std::unique_ptr<GameObject>& e) 
                                    {   std::cout << s << " " << typeid(*e).name() << std::endl;
                                    	return s == typeid(*e).name(); }), objectArray.end());/
    std::remove_if(
        objectArray.begin(), objectArray.end(), [s](const std::unique_ptr<GameObject>& e) 
                                    { return s == typeid(*e).name(); });
}*/