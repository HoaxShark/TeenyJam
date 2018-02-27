#include "GameStates.h"
#include "../engine/Input.h"

void GameState_Attract::Init()
{
	CottonGame::Get()->Init();
}

bool GameState_Attract::Update()
{	
	if (Input::Get()->GetKeyState('P') == KeyState_Pressed)
	{
		// go into pause mode ....
	}

	if (Input::Get()->GetKeyState(VK_SPACE) == KeyState_Pressed)
	{
		CottonGame::Get()->stateMachine.SetState(GameState_StartGame::Label);
	}
	else
	{
		CottonGame::Get()->Update();
	}
	return State::Update();
}

void GameState_Attract::Draw()
{
	CottonGame::Get()->Draw();

	//CottonGame::Get()->GUIPrint(400,50,"CottonLife\nGame Attract"); 

	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Centre);
	Renderer::Get()->debugPrinter->SetScale(1, 1);
	Renderer::Get()->debugPrinter->Print(50, 5, RGBTOCOLOR(255, 255, 255), "CottonLife");
	Renderer::Get()->debugPrinter->SetScale(1, 1);
	Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Left);


	/**Renderer::Get()->DrawRect(315,255,130,100,RGBTOCOLOR(255,255,255));
	Renderer::Get()->DrawRect(320,260,120,90,RGBTOCOLOR(0,0,0));

	Renderer::Get()->debugPrinter->Print(325,270,RGBTOCOLOR(255,255,255),"LEFT - MOVE LEFT");
	Renderer::Get()->debugPrinter->Print(325,290, RGBTOCOLOR(255, 255, 255), "RIGHT - MOVE RIGHT");
	Renderer::Get()->debugPrinter->Print(325,310, RGBTOCOLOR(255, 255, 255), "UP - MOVE UP");
	Renderer::Get()->debugPrinter->Print(325,330, RGBTOCOLOR(255, 255, 255), "DOWN - MOVE DOWN");*/

	if(frameCount%20 > 10)
	{
		Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Centre);
		Renderer::Get()->debugPrinter->SetScale(1, 1);
		Renderer::Get()->debugPrinter->Print(50, 40, RGBTOCOLOR(255, 255, 255), "SPACE");
		Renderer::Get()->debugPrinter->Print(50, 50, RGBTOCOLOR(255, 255, 255), "to play");
		Renderer::Get()->debugPrinter->SetJustification(DebugPrinter::Justify_Left);
	}
}

void GameState_Attract::Exit()
{

}

/***********************************************************************

************************************************************************/

void GameState_StartGame::Init()
{
	CottonGame::Get()->ResetScore();
}

bool GameState_StartGame::Update()
{
	CottonGame::Get()->stateMachine.SetState(GameState_PlacePlayer::Label);
	return true;
}
void GameState_StartGame::Draw()
{
	CottonGame::Get()->Draw();
}

void GameState_StartGame::Exit()
{

}


/***********************************************************************

************************************************************************/

void GameState_CreateRain::Init()
{
	CottonGame::Get()->CreateRain();
}

bool GameState_CreateRain::Update()
{
	if(CottonGame::Get()->IsPlayerActive() == false)
	{
		CottonGame::Get()->stateMachine.SetState(GameState_PlacePlayer::Label);
	}
	else
	{
		CottonGame::Get()->stateMachine.SetState(GameState_Play::Label);
	}
	return true;
}
void GameState_CreateRain::Draw()
{
	CottonGame::Get()->Draw();
}

void GameState_CreateRain::Exit()
{

}


/***********************************************************************

************************************************************************/

void GameState_PlacePlayer::Init()
{
	State::Init();
}

bool GameState_PlacePlayer::Update()
{
	/**if(CottonGame::Get()->explosionManager.ActiveCount() != 0)
	{
		frameCount = 0;
	}**/

	if(frameCount > 30) 
	{
		CottonGame::Get()->PlacePlayer();
		CottonGame::Get()->stateMachine.SetState(GameState_Play::Label);
		CottonGame::Get()->SetInvincible();
	}

	CottonGame::Get()->Update();
	
	return State::Update();
}
void GameState_PlacePlayer::Draw()
{
	CottonGame::Get()->Draw();
}

void GameState_PlacePlayer::Exit()
{

}



/***********************************************************************

************************************************************************/

void GameState_Play::Init()
{
	TheTimer.Start();
	int t1 = TheTimer.GetTime();
	ThePlayer = new Player;
}

bool GameState_Play::Update()
{	
	int playerScale = ThePlayer->GetPlayerScale();
	if (playerScale <= 4) // if player is too small move to end game
	{
		CottonGame::Get()->stateMachine.SetState(GameState_GameOver::Label);
	}

	CottonGame::Get()->Update();
	t2 = TheTimer.GetTime();

	

	if (TheRaindrop.GetDelay() <= (t1 + t2))
	{
		CottonGame::Get()->CreateRain();
		t1 = t2;

	}

	/**else
	{
		if(CottonGame::Get()->IsPlayerActive() == false)
		{
			if(CottonGame::Get()->Players > 0)
			{
				CottonGame::Get()->stateMachine.SetState(GameState_PlacePlayer::Label);
			}
			else
			{
				CottonGame::Get()->stateMachine.SetState(GameState_GameOver::Label);
			}
		}
	}*/


	return true;
}
void GameState_Play::Draw()
{
	CottonGame::Get()->Draw();
}

void GameState_Play::Exit()
{

}


/***********************************************************************

************************************************************************/

/**void GameState_EndOfWave::Init()
{
	CottonGame::Get()->CreateRain();
}

bool GameState_EndOfWave::Update()
{
	CottonGame::Get()->stateMachine.SetState(GameState_Play::Label);
	CottonGame::Get()->Update();

	return true;
}
void GameState_EndOfWave::Draw()
{
	CottonGame::Get()->Draw();
}

void GameState_EndOfWave::Exit()
{

}*/

/***********************************************************************

************************************************************************/

void GameState_GameOver::Init()
{
	State::Init();
}

bool GameState_GameOver::Update()
{
	if((frameCount > (8*30) ) /**&& (CottonGame::Get()->explosionManager.ActiveCount() == 0)**/)
	{
		CottonGame::Get()->stateMachine.SetState(GameState_Attract::Label);
	}
	else
	{
		CottonGame::Get()->Update();
	}
	return State::Update();
}
void GameState_GameOver::Draw()
{
	CottonGame::Get()->Draw();

	if(/**(CottonGame::Get()->explosionManager.ActiveCount() == 0) && **/(frameCount > (2*30)))
	{
		CottonGame::Get()->GUIPrint(25,10,"Game Over\n");
	}
}

void GameState_GameOver::Exit()
{

}



/***********************************************************************

************************************************************************/
void PauseGameState::Init()
{
	StateMachine::State::Init();
}
bool PauseGameState::Update() 
{		
	StateMachine::State::Update();
	
	if (frameCount > 10)
	{
		if (Input::Get()->GetKeyState(VK_ESCAPE) == KeyState_Pressed)
		{
			// quit game and return to attract mode
			CottonGame::Get()->stateMachine.RestartGameFromPauseMode(GameState_Attract::Label);
		}
		else
		{
			if (Input::Get()->GetKeyState('P') == KeyState_Pressed)
			{
				//leave the pause mode ...
				CottonGame::Get()->stateMachine.ReturnToGameFromPauseMode();
			}
		}
	}

	return true;
}

void PauseGameState::Draw()
{
	Renderer::Get()->DrawRect(315,255,150,110,RGBTOCOLOR(255,255,255));
	Renderer::Get()->DrawRect(320,260,140,100,RGBTOCOLOR(0,0,0));

	Renderer::Get()->debugPrinter->Print(325,270, RGBTOCOLOR(255,255,255),"PAUSE");
	Renderer::Get()->debugPrinter->Print(325,290, RGBTOCOLOR(255, 255, 255), "P - Return to game");
	Renderer::Get()->debugPrinter->Print(325,310, RGBTOCOLOR(255, 255, 255), "ESC - Quit Game");
}

void PauseGameState::Exit()
{	
}