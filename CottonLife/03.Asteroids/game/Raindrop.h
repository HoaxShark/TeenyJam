#pragma once
#include "BaseObject.h"

class Raindrop : public BaseObject
{
public:
	void Init(float direction);
	Vector2 startPosition;
	int Delay;
	void Update();
	void Draw();
	Vector2 GetStartPosition();
	int GetDelay();

	std::vector<Vector2> GetLineList();
};
