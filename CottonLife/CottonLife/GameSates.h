#pragma once
#include "../engine/StateMachine.h"

class GameState_Attract : public StateMachine::State
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Attract";
	virtual const char* Name() { return Label; }
};

class GameState_StartGame : public StateMachine::PausibleState
{
public:
	void Init();
	bool Update();
	void Draw();
	void Exit();

	static constexpr const char* Label = "Start";
	virtual const char* Name() { return Label; }
};

class GameState_Rain : public StateMachine::PausibleState
{
public:

	static constexpr const char* Label = "Rain";
	virtual const char* Name() { return Label; }
};

class GameState_Torrential : public StateMachine::PausibleState
{
public:

	static constexpr const char* Label = "Torrential";
	virtual const char* Name() { return Label; }
};

class GameState_Sprinkler : public StateMachine::PausibleState
{
public:

	static constexpr const char* Label = "Sprinkler";
	virtual const char* Name() { return Label; }

};

class GameState_Storm : public StateMachine::PausibleState
{
public:

	static constexpr const char* Label = "Storm";
	virtual const char* Name() { return Label; }

};

class GameState_GameOver : public StateMachine::PausibleState
{
public:

	static constexpr const char* Label = "Game over";
	virtual const char* Name() { return Label; }

};


class PauseGameState : public StateMachine::State
{
public:

	static constexpr const char* Label = "Pause Mode";
	virtual const char* Name() { return Label; }
};