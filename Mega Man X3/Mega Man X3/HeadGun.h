#pragma once
#include "Enemy.h"
class HeadGun :public Enemy
{
protected:
	int delay;
	bool isShoot;
public:

	enum HeadGunnerAction
	{
		Standing,
		Shooting
	};

	HeadGunnerAction action;

	HeadGun(MegaMan *megaMan, Sprite* sprite_HeadGunner, Sprite* sprite_Item, Sprite* sprite_Explosion,
		SpriteSheet* spriteSheet_HeadGunner, SpriteSheet* spriteSheet_Item, SpriteSheet* spriteSheet_Explosion);

	void NewII(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);


	HeadGun();
	~HeadGun();
};

