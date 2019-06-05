#include "ConOng.h"



ConOng::ConOng()
{
}
ConOng::ConOng(Sprite *Blas, SpriteSheet *BlasSheet)
{
	sprite = Blas;
	anim = new Animation(BlasSheet);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	tag = Object::Bullets;
	allowDraw = false;
	SetBound(20, 20);
	damage = 4;

}

void ConOng::New(D3DXVECTOR2 posit, bool flipflag) {
	allowDraw = true;
	position = posit;
	this->flipFlag = flipflag;
	SetBound(20, 20);
	isColl = false;
	timeExit = 0;
	timeBurt = 0;
	state = Aliving;

}

void ConOng::OnCollision(Object *obj, D3DXVECTOR2 distance) {

	RECT board = this->GetBoard(distance);

	
	if (Collision::isCollision(board, obj->GetBound()))
	{
		
		D3DXVECTOR2 sideCollision;

	
		float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

		
		if (time < 1.0f)
		{
			this->SetVelocity(0, 0);
			isColl = true;
			bound = { 0, 0, 0, 0 };
		}
	}


}

void ConOng::OnCollision(Object *obj) {
	this->SetVelocity(0, 0);
	state = Dying;
}
void ConOng::ChangeAnimation(Keyboard *key) {
	switch (state)
	{
	case State::Aliving:
	{
		anim->SetFrame(position, flipFlag, 1, 64, 66, true);
		break;
	}
	case State::Dying:
	{
		anim->SetFrame(position, flipFlag, 1, 67, 72, false);
		break;
	}
	}
}

void ConOng::Update(float dt, Keyboard* key) {
	ChangeAnimation(key);
	Object::Update(dt, key);
	anim->Update(dt, key);

	if (isColl)
	{
		timeExit += dt;
		if (timeExit > 5.0f)
		{
			state = Dying;
		}
	}

	if (state == Dying)
	{
		timeBurt += dt;
		if (timeBurt > 0.3f)
		{
			bound = { 0, 0, 0, 0 };
			timeBurt = 0.0f;
			timeExit = 0.0f;
			allowDraw = false;
		}
	}
}

void ConOng::Render(Viewport *view) {
	if (!allowDraw) return;

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


ConOng::~ConOng()
{
}
