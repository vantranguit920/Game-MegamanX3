#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
#include "Collision.h"
using namespace Define;

class Kysinh:public Object
{
protected:
	Animation * anim;
	float time;
public:
	Kysinh();

	enum State
	{
		Flying,
		Cling
	};
	
	State sate;
	bool isCling;
	bool appear;
	Kysinh(Sprite *Kysinh,SpriteSheet *KysinhSheet);

	void New(D3DXVECTOR2 position);

	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);

	~Kysinh();
};

