#pragma once
#include "BaseObject.h"
#include "Bullet.h"
#include <list>

class Player : public BaseObject
{
public:
	Player();

	void Init();
	void Update();
	void UpdateBullets();

	void Draw();
	//void DrawBullets();

	void OnCollided();

	std::vector<Vector2> GetLineList();
	
	bool canCollide();
	void SetInvincible();

	int playerVelocityX;
	int playerVelocityY;
	int playerSpeed;

private:
	bool bDisplayThrust;
	//int lastShotTime;	
	int invincibleTicker;
};
