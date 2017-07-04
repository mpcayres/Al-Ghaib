#include "InventoryArame.hpp"
#include "Sound.hpp"

InventoryArame::InventoryArame() : InventoryKey("img/object-arame.png") {
	Sound s = Sound("audio/mola.wav");
	s.Play(0);
}

InventoryArame::~InventoryArame() { }

bool InventoryArame::IsObject(std::string type){
	return (type == "InventoryArame");
}

std::string InventoryArame::GetObject(){
	return "InventoryArame";
}
