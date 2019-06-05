#include "NguoiMay.h"



NguoiMay::NguoiMay()
{
}


NguoiMay::NguoiMay(Sprite *nguoimaysprite,Sprite *smokesprite,Sprite *explosionsprite,SpriteSheet *nguoimaysheet,SpriteSheet *smokesheet,SpriteSheet *explosionsheet,D3DXVECTOR2 pos)
{
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = nguoimaysprite;
	this->anim = new Animation(nguoimaysheet);
	tag = Tag::Enemys;
	position = positionStart;
	SetBound(60, 84);
	allowDraw = false;
	flipFlag = false;
	state = dung;
	delay = 200;
	HP = 20;
	damage = 4;
	bulet = new Bullet(nguoimaysprite, nguoimaysheet);
	for (int i = 0; i < 6; i++)
	{
		smoke[i] = new Smoke(smokesprite, smokesheet);
	}
	num = 0;
	explosion = new Explosion(explosionsprite, explosionsheet);

}

void NguoiMay::ChangeAnimation(Keyboard *key) {

	SetBound(60, 84);
	switch (state)
	{
	case NguoiMay::dung:
		anim->SetFrame(position, flipFlag, 10, 0, 1, true);
		break;
	case NguoiMay::ban:
		anim->SetFrame(position, flipFlag, 5, 2, 5, false);
		break;
	case NguoiMay::luot:
		anim->SetFrame(position, flipFlag, 10, 6, 8, false);
		break;
	case NguoiMay::chet:
		break;
	default:
		break;
	}

}

void NguoiMay::Update(float dt, Keyboard *key) {
	if (!allowDraw)
		return;

	ChangeAnimation(key);
	Object::Update(dt, key);
	anim->Update(dt, key);

	if (state == chet)
	{
		allowDraw = false;
	}
	else
	{
		switch (state)
		{
		case NguoiMay::dung:
		{
			if (delay <= 0)
				delay = 150;
			delay--;
			if (delay <= 0)
			{
				if (!bulet->GetAllowDraw())
				{
					state = ban;
				}
				else
				{
					if (flipFlag)
						velocity.x = 2;
					else
						velocity.x = -2;
					state = luot;
				}
			}
			break;
		}
		case NguoiMay::ban:
		{
			if (delay <= 0)
				delay = 20;
			delay--;
			if (delay <= 0)
			{
				if (!bulet->GetAllowDraw())
				{
					bulet->NewBullet(position + anim->GetGun(anim->GetIndex()), false, Bullet::BulletByte);
					if (flipFlag) bulet->SetVelocity(2, 0);
					else bulet->SetVelocity(-2, 0);
					state = dung;
				}
			}
			break;
		}
		case NguoiMay::luot:
		{
			if (velocity.x == 0)
			{
				delay--;
				if (delay <= 0)
				{
					flipFlag = !flipFlag;
					state = dung;
				}
			}
			else
			{
				if (delay <= 0)
					delay = 5;
				delay--;
				if (delay <= 0)
				{
					smoke[num]->NewSmoke(position + anim->Getsmoke(anim->GetIndex()), flipFlag);
					num++;
					if (num > 5)
						num = 0;
				}
			}
			break;
		}
		}
	}

	if (bulet->GetAllowDraw())
		bulet->Update(dt, key);

	for (int i = 0; i < 6; i++)
	{
		smoke[i]->Update(dt, key);
	}

	explosion->Update(dt, key);
}


void NguoiMay::OnCollision(Object *obj, D3DXVECTOR2 distance) {

	RECT board = this->GetBoard(distance);

	if (Collision::isCollision(board, obj->GetBound()))
	{
		//Lấy cạnh va chạm
		D3DXVECTOR2 sideCollision;

		//lấy thời gian va chạm
		float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

		//bé hơn 1 thì có va chạm
		if (time < 1.0f)
		{
			if (sideCollision.x != 0)
				position.x += distance.x * time;
			else if (sideCollision.y != 0)
				position.y += distance.y * time;

			if (sideCollision.x != 0)
			{
				velocity.x = 0;
				explosion->NewExplosion(bulet->GetPosition());
				bulet->SetAllowDraw(false);
				delay = 100;
			}
		}
	}

}
void NguoiMay::OnCollision(Object *obj) {

	if (obj->tag == Object::Bullets)
	{
		HP -= obj->GetDamage();

		if (HP <= 0)
		{
			HP = 0;
			state = chet;
		}
	}

}
void NguoiMay::Render(Viewport *view) {

	if (!allowDraw)
		return;

	this->sprite->SetData(
		anim->GetRect(),
		anim->GetCenter(),
		anim->GetPosition(),
		anim->GetScale(),
		anim->GetTransform(),
		anim->GetAngle()
	);
	this->sprite->Render(view);

	if (bulet->GetAllowDraw())
		bulet->Render(view);

	for (int i = 0; i < 6; i++)
	{
		smoke[i]->Render(view);
	}

	explosion->Render(view);

}


NguoiMay::~NguoiMay()
{
}
