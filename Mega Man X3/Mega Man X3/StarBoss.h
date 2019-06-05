#pragma once
#include "BossFather.h"
class StarBoss:public BossFather
{
public:
	enum State
	{
		XuatHien,
		TanCongI,
		XuyenThau,
		TanCongII,
		TanCongIII,
		Chet

	};

	State state;


	StarBoss();
	StarBoss(MegaMan *mega,Sprite *starSprite,SpriteSheet *starSheet,D3DXVECTOR2 pos);



	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
	
	void ChangeAnimation(Keyboard* key);
	void New();

	~StarBoss();
};

