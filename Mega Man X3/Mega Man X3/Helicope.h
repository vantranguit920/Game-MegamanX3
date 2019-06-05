#pragma once
#include "Enemy.h"
class Helicope: public Enemy
{
protected:
	int delay;
	bool shoot;

public:
	enum Action
	{
		Fly,
		Shoot

	};
	Action action;

	Helicope();
	~Helicope();
	Helicope(MegaMan *megaman, Sprite *HelicSprite,Sprite *ItemSprite,Sprite *ExplosionSprite,SpriteSheet *HelicSheet,
										SpriteSheet *ItemSheet,SpriteSheet *ExplosionSheet );


	void Newhelic(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
};

