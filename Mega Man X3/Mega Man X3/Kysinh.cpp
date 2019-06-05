#include "Kysinh.h"



Kysinh::Kysinh()
{
}
Kysinh::Kysinh(Sprite *Kysinhs,SpriteSheet *KysinhSheet) {

	sprite = Kysinhs;
	anim = new Animation(KysinhSheet);


	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	tag = Object::None;
	allowDraw = false;
	SetBound(6, 6);
	damage = 0;

}

void Kysinh::New(D3DXVECTOR2 positi) {

	allowDraw = true;
	appear = true;
	position = positi;
	sate = Flying;
	isCling = false;

}
void Kysinh::OnCollision(Object *obj, D3DXVECTOR2 distance){


}
void Kysinh::ChangeAnimation(Keyboard *key) {

	SetBound(6, 6);
	switch (sate)
	{
	case State::Flying:
	{
		anim->SetFrame(position, flipFlag, 5, 75, 76, true);
		break;
	}
	case State::Cling:
	{
		anim->SetFrame(position, flipFlag, 5, 77, 78, true);
		break;
	}
	}

}

void Kysinh::Update(float dt, Keyboard* key) {

	ChangeAnimation(key);
	Object::Update(dt, key);
	anim->Update(dt, key);

	if (appear)
	{
		if (!allowDraw)
		{
			SetAllowDraw(true);
		}
		else
		{
			SetAllowDraw(false);
		}
	}

	if (isCling)
	{
		sate = Cling;
		time += dt;
		if (time > 5.0f)
		{
			bound = { 0, 0, 0, 0 };
			time = 0.0f;
			allowDraw = false;
			appear = false;
		}
	}

}
void Kysinh::Render(Viewport *view) {

	if (!appear) return;

	sprite->SetData(
		anim->GetRect(),
		anim->GetCenter(),
		anim->GetPosition(),
		anim->GetScale(),
		anim->GetTransform(),
		anim->GetAngle()
	);
	sprite->Render(view);

}


Kysinh::~Kysinh()
{
}
