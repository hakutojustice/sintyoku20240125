#pragma once
#include <memory>
#include "Rect.h"

class Player;
class Map
{
public:
	Map() {}
	virtual ~Map() {}


	void Update();
	void Draw();


private:
};