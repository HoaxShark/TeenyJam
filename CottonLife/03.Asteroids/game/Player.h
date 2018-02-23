#pragma once
#include "BaseObject.h"
#include "Raindrop.h"
#include "SDL.h"

#include <list>

class Player : public BaseObject
{
public:
	Player();

	void Init();
	void Update();
	//void UpdateRaindrops();

	void Draw();
	//void DrawRaindrops();

	void OnCollided();

	std::vector<Vector2> GetLineList();
	
	bool canCollide();
	void SetInvincible();

	int GetPlayerScale();
	void SetPlayerScale(int newScale);

	int playerVelocityX;
	int playerVelocityY;
	int playerSpeed;
	int playerScale;

private:
	bool bDisplayThrust;
	//int lastShotTime;	
	int invincibleTicker;
	SDL_Renderer* mainRenderer;
};
