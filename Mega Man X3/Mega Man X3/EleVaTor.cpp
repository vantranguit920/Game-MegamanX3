#include "EleVaTor.h"



EleVaTor::EleVaTor()
{
}

EleVaTor::EleVaTor(MegaMan* man, Sprite* sprite_Elevator, SpriteSheet* spriteSheet_Elevator, D3DXVECTOR2 pos)
{
	this->man = man;
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = sprite_Elevator;
	this->animation = new Animation(spriteSheet_Elevator);
	tag = Tag::Elevator;
	position = positionStart;
	SetBound(95, 44);
	allowDraw = true;
	flipFlag = false;
	state = Standing;
}
void EleVaTor::ChangeAnimation(Keyboard* key) {

	switch (state)
	{
	case EleVaTor::Standing:
		animation->SetFrame(position, flipFlag, 0, 0, 0, false);
		break;
	case EleVaTor::Running:
		animation->SetFrame(position, flipFlag, 1, 0, 1, true);
		break;
	}



}

void EleVaTor::Update(float dt, Keyboard* key) {

	if (!allowDraw)
		return;

	ChangeAnimation(key);
	Object::Update(dt, key);
	animation->Update(dt, key);

	if (position.y > 1600)
	{
		state = Standing;
	}

	if (state == Standing)
	{
		velocity.y = 0.0f;
	}
	else
	{
		velocity.y = 0.3f;
	}

}

void EleVaTor::OnCollision(Object *obj) {
	if (Collision::isCollision(GetBound(), obj->GetBound()))
	{
		man->GetStateMegaman()->isElevator = true;
		state = Running;
	}
	else
	{
		man->GetStateMegaman()->isElevator = false;
	}

}
void EleVaTor::Render(Viewport* viewport) {
	if (viewport->isContains(bound))
	{
		allowDraw = true;

		this->sprite->SetData(
			animation->GetRect(),
			animation->GetCenter(),
			animation->GetPosition(),
			animation->GetScale(),
			animation->GetTransform(),
			animation->GetAngle()
		);
		this->sprite->Render(viewport);
	}
	else
	{
		allowDraw = false;
		man->GetStateMegaman()->isElevator = false;
	}


}
EleVaTor::~EleVaTor()
{
}
