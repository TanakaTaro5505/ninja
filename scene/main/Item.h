#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item() : GameObject()
	{
	}
	virtual ~Item() {}

	void update();
	// �����I��
	void erase();
private:
	
};
