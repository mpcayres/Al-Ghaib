/*
 * InventaryKey.hpp
 *
 *  Created on: 18 de mai de 2017
 *      Author: renne
 */

#ifndef INCLUDE_INVENTARYKEY_HPP_
#define INCLUDE_INVENTARYKEY_HPP_

#include "InventaryObject.hpp"

class InventaryKey : public InventaryObject{
public:
	InventaryKey(std::string file);
	~InventaryKey();

	void Render();
	bool IsObject(std::string type);
	void Action();

private:
	Sprite sp;
};



#endif /* INCLUDE_INVENTARYKEY_HPP_ */
