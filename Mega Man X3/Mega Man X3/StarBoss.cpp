#include "StarBoss.h"



StarBoss::StarBoss()
{
}



StarBoss::StarBoss(MegaMan *mega, Sprite *starSprite, SpriteSheet *starSheet, D3DXVECTOR2 pos)
{
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = starSprite;
	this->anim = new Animation(starSheet);
	tag = Tag::Enemys;
	New();

}

void StarBoss::New() {
	position = positionStart;
	SetBound(50, 50);

	allowDraw = false;
	flipFlag = false;
	state = XuatHien;
	delay = 200;
	SetVelocity(-2, 0);
	HP = 20;
	damage = 4;
}

void StarBoss::ChangeAnimation(Keyboard *key) {
	SetBound(50, 50);
	switch (state)
	{
	case StarBoss::XuatHien:
		anim->SetFrame(position, flipFlag, 5 , 1, 5, true);
		break;
	case StarBoss::TanCongI:
		anim->SetFrame(position, flipFlag, 0.5, 58, 67, true);
		break;
	case StarBoss::XuyenThau:
		anim->SetFrame(position, flipFlag, 2, 58, 67, true);
		break;
	case StarBoss::TanCongII:
		anim->SetFrame(position, flipFlag, 0.3, 58, 67, true);
		break;
	case StarBoss::TanCongIII:
		anim->SetFrame(position, flipFlag, 0.2, 68, 84, true);
		break;
	case StarBoss::Chet:
		break;
	default:
		break;
	}
}

void StarBoss::Update(float dt,Keyboard *key) {

	if (!allowDraw)
		return;

	ChangeAnimation(key);
	Object::Update(dt, key);
	anim->Update(dt, key);

	if (state == Chet)
	{
		allowDraw = false;
	}
	else
	{
		switch (state)
		{
		case StarBoss::XuatHien:
		{
			state = TanCongI;
			break;
		}
		case StarBoss::TanCongI:
		{
			if (velocity.y != 0)
				AddVelocity(0, -0.05f);

			if (HP < 15)
			{
				state = XuyenThau;
			}
			break;
		}
		case StarBoss::XuyenThau:
		{
			if (position.x < 2328) {
				SetVelocity(2, 0);
			}
			else if(position.x>2526)
			{
				SetVelocity(-2, 0);
			}
			if (velocity.x == 0 && velocity.y == 0)
			{
				if (delay <= 0)
					delay = 200;
				delay--;

				if (delay <= 0)
				{
					SetVelocity(-2, 0);
					state = TanCongII;
				}
			}
			break;
		}
		case StarBoss::TanCongII:
		{
			if (velocity.x == 0 && velocity.y == 0)
			{
				if (delay <= 0)
					delay = 200;
				delay--;

				if (delay <= 0)
				{
					SetVelocity(-2, 2);
					state = TanCongIII;
				}
			}
			break;
		}
		case StarBoss::TanCongIII:
		{
			if (velocity.y != 0)
				AddVelocity(0, -0.05f);
			break;
		}
		}
	}

}

void StarBoss::OnCollision(Object *obj,D3DXVECTOR2 distance) {

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

			if (sideCollision.x == -1)	//trái
			{
				if (state == TanCongI || state == XuyenThau || state == TanCongIII)
				{
					velocity.x = 2;
				}
				else if (state == TanCongII)
				{
					velocity.x = 0;
					velocity.y = 2;
				}
			}
			else if (sideCollision.x == 1)	//phải
			{
				if (state == TanCongI || state == TanCongIII)
				{
					velocity.x = -2;
				}
				else if (state == XuyenThau)
				{
					velocity.x = 0;
					velocity.y = -2;
				}
				else
				{
					velocity.x = 0;
					velocity.y = -2;
				}
			}
			else if (sideCollision.y == 1)	//dưới
			{
				if (state == TanCongI)
				{
					velocity.y = 0;
				}
				else if (state == XuyenThau)
				{
					velocity.y = 0;
				}
				else if (state == TanCongII)
				{
					velocity.y = 0;
				}
				else if (state == TanCongIII)
				{
					velocity.y = 2;
				}

			}
			else if (sideCollision.y == -1)	//trên
			{
				velocity.x = 2;
				velocity.y = 0;
			}

		}
	}

}

void StarBoss::OnCollision(Object *obj) {
	if (obj->tag == Object::Bullets)
	{
		if (state == TanCongI)
		{
			if (velocity.y == 0)
				velocity.y = 2;
		}

		HP -= obj->GetDamage();

		if (HP <= 0)
		{
			HP = 0;
			state = Chet;
		}
	}
}



void StarBoss::Render(Viewport *view) {
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
}

StarBoss::~StarBoss()
{
}
