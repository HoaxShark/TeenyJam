#pragma once
#include "CottonGame.h"
#include "Player.h"
#include "../engine/Timer.h"
#include "../engine/StateMachine.h"

class GameState_Attract: public StateMachine::State
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Attract";
	virtual const char* Name() { return Label;}
};

class GameState_StartGame: public StateMachine::PausibleState
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Start";
	virtual const char* Name() { return Label;}
};

class GameState_CreateRain: public StateMachine::PausibleState
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Create Rain";
	virtual const char* Name() { return Label;}
};

class GameState_PlacePlayer: public StateMachine::PausibleState
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Place Player";
	virtual const char* Name() { return Label; }
};

class GameState_Play: public StateMachine::PausibleState
{
public:
	Player* ThePlayer;
	Timer TheTimer;
	Raindrop TheRaindrop;
	int t1;
	int t2;
	void Init();
	bool Update();
	void Draw();
	void Exit();
	
	static constexpr const char* Label = "Play";
	virtual const char* Name() { return Label; }

};

/**class GameState_EndOfWave: public StateMachine::PausibleState
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "End Of Wave";
	virtual const char* Name() { return Label; }

};*/

class GameState_GameOver: public StateMachine::PausibleState
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();
	
	static constexpr const char* Label = "Game over";
	virtual const char* Name() { return Label; }

};


class PauseGameState: public StateMachine::State
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Pause Mode";
	virtual const char* Name() { return Label; }
};