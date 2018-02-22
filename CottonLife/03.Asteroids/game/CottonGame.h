#pragma once
#include "Rock.h"
#include "Player.h"
//#include "ExplosionManager.h"
#include "../engine/StateMachine.h"
#include "../engine/Singleton.h"

#include <list>

class CottonGame : public Singleton<CottonGame>
{
public:	
	std::list<Rock*> rockList;
	std::list<Bullet*> bulletList;

	Player ThePlayer;
	bool bPlayerActive;
	int Score;
	int Players;
	

	//ExplosionManager explosionManager;

	void CreateRocks();
	//void ExplodeRock(Rock& rock);

	bool IsPlayerActive();
	void PlacePlayer();
	void SetInvincible();

	void ResetScore();

	void Init();

	bool OnOneTimeInit();
	void Update();
	void Draw();

	void GUIPrint(int x, int y,char* fmt);

	StateMachine stateMachine;
private:
};