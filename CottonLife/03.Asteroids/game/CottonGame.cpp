#include "CottonGame.h"
#include "GameStates.h"
#include <assert.h>

/**void CottonGame::ExplodeRock(Rock& rock)
{
	explosionManager.Add(rock.GetPosition(),rock.GetLineList());

	switch(rock.size)
	{
	case Rock::Size_big:
	{
		for(int i=0;i<4;i++)
		{
			Rock *pNewRock = new Rock();
			rockList.push_back(pNewRock);
			
			pNewRock->Init(rock);						
		}

		Score += 10;
	}
	break;

	case Rock::Size_medium:
	{				
		for(int i=0;i<3;i++)
		{
			Rock *pNewRock = new Rock();
			rockList.push_back(pNewRock);

			pNewRock->Init(rock);
		}

		Score += 50;
	}
	break;

	case Rock::Size_small:
		Score += 100;
		break;

	default:
		assert(0);
		break;
	}
	rock.SetInUse(false);
}**/

void CottonGame::Init()
{
	ThePlayer.Init();
	bPlayerActive = false;

	CreateRain();
	ResetScore();	

	//explosionManager.Clear();
}
bool CottonGame::OnOneTimeInit()
{	
	Init();

	stateMachine.AddState(GameState_Attract::Label, new GameState_Attract());
	stateMachine.AddState(GameState_StartGame::Label, new GameState_StartGame());
	stateMachine.AddState(GameState_CreateRain::Label, new GameState_CreateRain());
	stateMachine.AddState(GameState_PlacePlayer::Label, new GameState_PlacePlayer());
	stateMachine.AddState(GameState_Play::Label, new GameState_Play());
	//stateMachine.AddState(GameState_EndOfWave::Label, new GameState_EndOfWave());
	stateMachine.AddState(GameState_GameOver::Label, new GameState_GameOver());
	stateMachine.AddState(PauseGameState::Label, new PauseGameState());

	stateMachine.SetState(GameState_Attract::Label);
	stateMachine.SetPauseMode(PauseGameState::Label);

	return true;
}

void CottonGame::Update()
{
	if(IsPlayerActive() == true)
	{
		ThePlayer.Update();
	}
		
	ThePlayer.SetCollided(false);
	
	for (std::list<Raindrop*>::iterator Raindrop = RaindropList.begin(); Raindrop != RaindropList.end(); Raindrop++)
	{
		if((*Raindrop)->IsInUse() == true)
		{			
			if(IsPlayerActive() == true)
			{
				if(((*Raindrop)->IsInUse() == true) && (ThePlayer.CollidesWith((*Raindrop) ) == true))
				{
					if (ThePlayer.canCollide() == true)
					{
						ThePlayer.SetCollided(true);
						(*Raindrop)->SetInUse(false);
					}					
				}
			}
		}
	}

	if(ThePlayer.GetCollided() == true)
	{
		ThePlayer.OnCollided();
		int oldScale = ThePlayer.GetPlayerScale(); // on colide reduce scale of player
		oldScale -= 1;
		ThePlayer.SetPlayerScale(oldScale);
		//explosionManager.Add(ThePlayer.GetPosition(),ThePlayer.GetLineList());

		bPlayerActive = false;
		//Players--;
	}
	std::list<Raindrop*>::iterator Raindrop = RaindropList.begin();
	while (Raindrop != RaindropList.end())
	{
		if ((*Raindrop)->IsInUse() == true)
		{
			(*Raindrop)->Update();
			Raindrop++;
		}
		else
		{
			delete (*Raindrop);
			Raindrop = RaindropList.erase(Raindrop);
		}
	}
}

void CottonGame::Draw()
{
	SDL_SetRenderDrawColor(Renderer::Get()->renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer::Get()->renderer);

	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	Renderer::Get()->DrawRect(0,0,(float)vp.Width, (float)vp.Height,RGBTOCOLOR(0,0,0));
	
	if(IsPlayerActive() == true)
	{
		ThePlayer.Draw();
	}

	for (std::list<Raindrop*>::iterator Raindrop = RaindropList.begin(); Raindrop != RaindropList.end(); Raindrop++)
	{
		if ((*Raindrop)->IsInUse() == true)
		{
			(*Raindrop)->Draw();
		}
	}
	

	Renderer::Get()->debugPrinter->Print(700,20,RGBTOCOLOR(255,255,255),"Score: %d",Score);

	char text[32] = "";

	/**for(int i=0;i<Players;i++)
	{
		strcat(text,"A");
	}*/


	//Renderer::Get()->debugPrinter->Print(700,50,RGBTOCOLOR(255,255,255), text);
}


void CottonGame::CreateRain()
{	
	Raindrop *pDrop = new Raindrop();
	RaindropList.push_back(pDrop);
	pDrop->Init(0);


	/**pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(150, 0), Rock::Size_big, Vector2(0, 1));

	pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(550, 0), Rock::Size_big, Vector2(0, -1));

	pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(500, 0), Rock::Size_big, Vector2(0, 1));*/
}

bool CottonGame::IsPlayerActive()
{
	return bPlayerActive;
}

void CottonGame::PlacePlayer()
{
	ThePlayer.Init();
	bPlayerActive = true;
}

void CottonGame::ResetScore()
{
	Score = 0;
	ThePlayer.playerScale = 40; // reset player scale back to normal
}

void CottonGame::GUIPrint(int x, int y,char* fmt)
{
	Renderer::Get()->debugPrinter->Print(x, y, RGBTOCOLOR(255, 255, 255), fmt);
}

void CottonGame::SetInvincible()
{
	ThePlayer.SetInvincible();
}