#include "Raindrop.h"
#include "../engine/Matrix.h"
#include "../engine/Renderer.h"

void Raindrop::Init(float direction)
{
	bInUse = true;
	Position = Raindrop::GetStartPosition();
	angle = direction;
	Velocity = Vector2::Transform(Vector2(0,1),Matrix::CreateRotationZ(direction));

	collider.Set(Position,3);
}

void Raindrop::Update()
{
	if(IsInUse() == false) return;

	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	if( ((Position.x + Velocity.x) < 0)
		||((Position.x + Velocity.x) > vp.Width)
		)
	{
		SetInUse(false);
		return;
	}

	if( ((Position.y + Velocity.y) < 0)
		||((Position.y + Velocity.y) > vp.Height)
		)
	{
		SetInUse(false);
		return;
	}

	Position += Velocity;


	BaseObject::Update();
}

void Raindrop::Draw()
{
	if(IsInUse() == false)	return;
	Renderer::Get()->DrawRect(Position.x-2,Position.y-2,2,2,RGBTOCOLOR(0,0,255));
	BaseObject::Draw();
}

Vector2 Raindrop::GetStartPosition()
{
	startPosition.x = rand() % 60;
	return startPosition;
}

int Raindrop::GetDelay()
{
	Delay = rand() % 60;
	return 0;
}

std::vector<Vector2> Raindrop::GetLineList()
{
	std::vector<Vector2> vertList;

	return vertList;
}
