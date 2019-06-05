#pragma once
#include "Enemy.h"
class Frog: public Enemy 
{
protected:
	int delay;
	bool jump, shoot;
public:

	enum Action
	{
		Standing,
		TargetSkew,
		TargetVertical,
		ShootingSkew,
		ShootingVertical,
		BackShootingSkew,
		BackShootingVertical,
		Moving

	};
	Action FrogAction;

	Frog();
	Frog(MegaMan *megaman,Sprite *frog_sprite,Sprite *item,Sprite *explosion,SpriteSheet *frog_sheet,SpriteSheet *item_sheet,SpriteSheet *explosion_sheet);

	//overide
	void New(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);

	~Frog();
};

