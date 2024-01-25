#pragma once

#include"Vec2.h"
class Object
{
protected:
	Vec2 pos;

	int graph;
public:

	Object() {};
	virtual ~Object() {};

	virtual void Update() = 0;

	virtual void Draw() = 0;

};

