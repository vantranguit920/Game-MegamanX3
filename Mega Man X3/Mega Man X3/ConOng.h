#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
#include "Collision.h"
using namespace Define;
class ConOng:public Object
{
protected:
	Animation * anim;
	bool isColl;
	float timeBurt; 
	float timeExit;
public:
	enum State {
		Aliving,
		Dying
	};
	State state;
	

	ConOng();
	ConOng(Sprite *Blas,SpriteSheet *BlasSheet);

	void New(D3DXVECTOR2 position, bool flipflag);

	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);

	~ConOng();
};

