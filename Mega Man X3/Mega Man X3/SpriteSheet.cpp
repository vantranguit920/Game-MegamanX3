﻿#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char* path)
{
	ReadXML(path);
}

SpriteSheet::~SpriteSheet()
{
}


void SpriteSheet::ReadXML(const char* path)
{
	
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load Sprite xml file", "Error", MB_OK);
		return;
	}
	

	TiXmlElement *Animations = doc.RootElement();
	TiXmlElement* Animation = Animations->FirstChildElement();
	Animation->QueryFloatAttribute("width", &this->width);
	Animation->QueryFloatAttribute("height", &this->height);
	int n = 0;
	while (Animation)
	{
		TiXmlElement *sprite = Animation->FirstChildElement();
		while (sprite)
		{
			sprite->QueryFloatAttribute("x", &this->tile[n].x);
			sprite->QueryFloatAttribute("y", &this->tile[n].y);
			sprite->QueryFloatAttribute("w", &this->tile[n].w);
			sprite->QueryFloatAttribute("h", &this->tile[n].h);
			sprite->QueryFloatAttribute("pX", &this->tile[n].px);
			sprite->QueryFloatAttribute("pY", &this->tile[n].py);
			sprite->QueryFloatAttribute("gX", &this->tile[n].gx);
			sprite->QueryFloatAttribute("gY", &this->tile[n].gy);
			sprite->QueryFloatAttribute("sX", &this->tile[n].sx);
			sprite->QueryFloatAttribute("sY", &this->tile[n].sy);
			//next
			n++;
			sprite = sprite->NextSiblingElement();
		}
		Animation = Animation->NextSiblingElement();
	}
}

float SpriteSheet::GetWidth()
{
	return this->width;
}

float SpriteSheet::GetHeight()
{
	return this->height;
}


RECT SpriteSheet::GetRect(int index)
{
	RECT rect;
	rect.left = tile[index].x;		
	rect.top = tile[index].y;		
	rect.right = rect.left + tile[index].w;
	rect.bottom = rect.top + tile[index].h;
	return rect;
}

D3DXVECTOR2 SpriteSheet::GetGun(int index)
{
	D3DXVECTOR2 pGun;
	pGun.x = tile[index].w * (tile[index].gx - 0.5);
	pGun.y = tile[index].h * (tile[index].gy - 0.5);
	return pGun;
}

D3DXVECTOR2 SpriteSheet::GetSpark(int index)
{
	D3DXVECTOR2 pSpark;
	pSpark.x = tile[index].w * (tile[index].sx - 0.5);
	pSpark.y = tile[index].h * (tile[index].sy - 0.5);
	return pSpark;
}

D3DXVECTOR2 SpriteSheet::Getsmoke(int index) {
	D3DXVECTOR2 pSmoke;
	pSmoke.x = tile[index].w * (tile[index].sx - 0.5);
	pSmoke.y = tile[index].h * (tile[index].sy - 0.5);
	return pSmoke;
}