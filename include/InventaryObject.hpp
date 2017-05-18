/*
 * InventaryObject.hpp
 *
 *  Created on: 18 de mai de 2017
 *      Author: renne
 */

#ifndef INCLUDE_INVENTARYOBJECT_HPP_
#define INCLUDE_INVENTARYOBJECT_HPP_

#include <string>

#include "Geometry.hpp"
#include "Sprite.hpp"

class InventaryObject{

public:
	virtual ~InventaryObject(){};

	virtual void Render() = 0;
	virtual void Action() = 0;
	virtual bool IsObject(std::string type) = 0;
};


#endif /* INCLUDE_INVENTARYOBJECT_HPP_ */
