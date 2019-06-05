#pragma once
#include "BossFather.h"
#include "ConOng.h"
#include "Kysinh.h"
class OngChua:public BossFather
{
protected:
	MegaMan * mega;
	bool up;
	bool lefts;
	bool laun;
	D3DXVECTOR2 posStartSwoop;
	int numRound;
	int numBee;
public:
	ConOng * List[5];
	Kysinh *kysinh;
	enum State
	{
		Bay,
		BayVong,
		Chich,
		TanCong,
		Phun,
		Chet

	};
	State state;
	OngChua(MegaMan *mega,Sprite *ongchuaSprite,SpriteSheet *OngchuaSheet,D3DXVECTOR2 pos);

	OngChua();
	~OngChua();


	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
	//void OnCollision();
	void ChangeAnimation(Keyboard* key);
};

