#pragma once
#include "Animation.h"
#include "Define.h"
#include "Collision.h"
#include "MegaMan.h"
using namespace Define;
class EleVaTor:public Object
{
protected:
	int delay;
	Animation *animation;
	MegaMan* man;
public:
	enum ElevatorState
	{
		Standing,
		Running
	};
	ElevatorState state;



	EleVaTor();
	~EleVaTor();
	EleVaTor(MegaMan* man, Sprite* sprite_Elevator, SpriteSheet* spriteSheet_Elevator,D3DXVECTOR2 pos);

	void ChangeAnimation(Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj);


};

