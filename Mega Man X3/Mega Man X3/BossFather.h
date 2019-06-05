#pragma once
#include "Animation.h"
#include "Define.h"
#include "Collision.h"
#include "Bullet.h"
#include "MegaMan.h"
class BossFather: public Object
{
protected:
	int delay;
	Animation *anim;
public:

	virtual void Update(float gameTime, Keyboard* key);
	virtual void Render(Viewport* viewport);
	virtual void OnCollision(Object *obj, D3DXVECTOR2 distance);
	virtual void OnCollision(Object *obj);
	virtual void OnCollision();
	virtual void ChangeAnimation(Keyboard* key); 

	


	BossFather();
	~BossFather();
};

