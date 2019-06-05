#pragma once
#include "BossFather.h"
#include "Explosion.h"
class NguoiMay:public BossFather
{
protected:
	int num;

public:
	enum State
	{
		dung,
		ban,
		luot,
		chet

	};
	State state;
	Bullet *bulet;
	Smoke *smoke[6];
	Explosion *explosion;

	NguoiMay();

	NguoiMay(Sprite *Nguoimaysprite,Sprite *smokesprite,Sprite *explosionsprite,SpriteSheet *Nguoimaysheet,SpriteSheet *smokesheet,SpriteSheet *explosionsheet,D3DXVECTOR2 pos);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
	//void OnCollision();
	void ChangeAnimation(Keyboard* key);

	~NguoiMay();
};