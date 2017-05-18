/*
 * InventaryKey.cpp
 *
 *  Created on: 18 de mai de 2017
 *      Author: renne
 */

#include "InventaryKey.hpp"

InventaryKey::InventaryKey(std::string file){
	sp = Sprite(file);
}

InventaryKey::~InventaryKey(){
}

void InventaryKey::Render(){
	sp.Render(0,0,0);
}

void InventaryKey::Action(){ }

bool InventaryKey::IsObject(std::string type){
	return (type == "KeyObject");
}
