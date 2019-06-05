#include "Animation.h"


Animation::Animation(SpriteSheet* spriteSheet)
{
	this->spriteSheet = spriteSheet;
	delay = 0;
	start = 0;
	end = 0;
	repeat = true;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	flipFlag = false;
	angle = 0;
	pause = false;
}

Animation::Animation(SpriteSheet* spriteSheet, int start, int end, int delay, bool repeat)
{
	this->spriteSheet = spriteSheet;
	this->delay = delay;
	this->index = 0;
	this->start = start;
	this->end = end;
	this->repeat = repeat;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	flipFlag = false;
	angle = 0;
	pause = false;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::SetFrame(D3DXVECTOR2 position, bool flip, int delay, int start, int end)
{
	this->position = position;
	this->flipFlag = flip;
	this->delay = delay;
	this->start = start;
	this->end = end;
}

void Animation::Animation::SetFrame(D3DXVECTOR2 position, bool flip, int delay, int start, int end, bool repeat)
{
	this->position = position;
	this->flipFlag = flip;
	this->delay = delay;
	this->start = start;
	this->end = end;
	this->repeat = repeat;
}

int Animation::GetIndex()
{
	return index;
}

void Animation::SetIndex(int index)
{
	this->index = index;
}

RECT Animation::GetRect()
{
	return spriteSheet->GetRect(index);
}


bool Animation::GetFlipFlag()
{
	return flipFlag;
}

int Animation::GetDelay()
{
	return delay;
}

int Animation::GetStart()
{
	return start;
}

int Animation::GetEnd()
{
	return end;
}

void Animation::SetPause(bool pause)
{
	this->pause = pause;
}
void Animation::SetPause(bool pause, int index)
{
	this->indexPause = index;
	this->pause = pause;
}

void Animation::Update(float dt, Keyboard* keyboard)
{
	if ( index == end && repeat == false)
	{
		
	}
	else
	{
		
		if (timeCurrent * 100 >= delay)
		{
			timeCurrent = 0;
			index++;
		}
		else timeCurrent += dt;

		
		if (index < start || index > end)
		{
			index = start;
		}
	}

	
	if (pause)
	{
		index = indexPause;
	}
	
	Flip(flipFlag);

	
	this->rect = GetRect();

	
	center.x = (rect.right - rect.left) * 0.5;
	center.y = (rect.bottom - rect.top) * 0.5;
	
}


D3DXVECTOR2 Animation::GetGun(int index)
{
	D3DXVECTOR2 pGun;
	if (flipFlag)
		pGun.x = -spriteSheet->GetGun(index).x;
	else
		pGun.x = spriteSheet->GetGun(index).x;

	pGun.y = spriteSheet->GetGun(index).y;

	return pGun;
}

D3DXVECTOR2 Animation::Getsmoke(int index) {
	D3DXVECTOR2 pSmoke;
	if (flipFlag)
		pSmoke.x = -spriteSheet->Getsmoke(index).x;
	else
		pSmoke.x = spriteSheet->Getsmoke(index).x;

	pSmoke.y = spriteSheet->Getsmoke(index).y;

	return pSmoke;
}
