#include "OngChua.h"



OngChua::OngChua()
{
}

OngChua::OngChua(MegaMan *mega, Sprite *ongchuaSprite, SpriteSheet *OngchuaSheet, D3DXVECTOR2 pos)
{
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = ongchuaSprite;
	this->anim = new Animation(OngchuaSheet);
	tag = Tag::Enemys;
	this->mega = mega;
	position = positionStart;
	posStartSwoop = D3DXVECTOR2(0, 0);
	laun = false;
	SetBound(60, 84);
	SetVelocity(0, 0);
	allowDraw = false;
	flipFlag = false;
	state = Bay;
	delay = 50;
	HP = 20;
	damage = 4;
	numRound = 0;

	numBee = 0;
	for (int i = 0; i < 5; i++)
		List[i] = new ConOng(ongchuaSprite, OngchuaSheet);

	kysinh = new Kysinh(ongchuaSprite, OngchuaSheet);

}

void OngChua::OnCollision(Object *obj, D3DXVECTOR2 distance) {

	RECT board = this->GetBoard(distance);

	if (Collision::isCollision(board, obj->GetBound()))
	{
		
		D3DXVECTOR2 sideCollision;

		
		float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

		
		if (time < 1.0f)
		{
			if (sideCollision.x != 0)
				position.x += distance.x * time;
			else if (sideCollision.y != 0)
				position.y += distance.y * time;

			if (sideCollision.x == -1)
			{
				numRound++;
				velocity.x = 0;
				lefts = false;
			}

			if (sideCollision.x == 1)
			{
				numRound++;
				velocity.x = 0;
				lefts = true;
			}

			if (sideCollision.y == -1) 
			{
				velocity.x = 0;
				velocity.y = 0;

				if (state == Bay)
				{
					if (laun)
					{
						laun = false;
						state = Phun;
					}
					else
					{
						laun = true;
						state = Chich;
					}
				}
			}

			if (sideCollision.y == 1) 
			{
				velocity.x = 0;
				state = Bay;
			}
		}
	}

}

void OngChua::OnCollision(Object *obj) {
	if (obj->tag == Object::Bullets)
	{
		HP -= obj->GetDamage();

		if (HP <= 0)
		{
			HP = 0;
			state = Chet;
		}
	}
}


void OngChua::Render(Viewport *view) {



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

	for (int i = 0; i < 5; i++)
		List[i]->Render(view);

	if (kysinh->GetAllowDraw())
		kysinh->Render(view);

}
void OngChua::Update(float dt, Keyboard* key) {


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
		case OngChua::Bay:
		{
			if (position.x < mega->GetPosition().x)
				flipFlag = true;
			else
				flipFlag = false;

			if (posStartSwoop.x != 0)
			{
				if (position.x < posStartSwoop.x)
					velocity.x = 0.5;
				else
					velocity.x = -0.5;
			}

			AddVelocity(0, 0.05f);
			break;
		}
		case OngChua::BayVong:
		{
			if (position.x < mega->GetPosition().x)
				flipFlag = true;
			else
				flipFlag = false;

			if (velocity.y >= 1)
				up = false;
			else if (velocity.y <= -1)
				up = true;

			if (up)
				AddVelocity(0, 0.05f);
			else
				AddVelocity(0, -0.05f);

			if (lefts)
				AddVelocity(-0.01f, 0);
			else
				AddVelocity(0.01f, 0);

			if (HP <= 10)
			{
				if (!kysinh->appear)
					kysinh->New(position);

				if (kysinh->isCling)
				{
					if (delay <= 0)
						delay = 100;
					delay--;

					if (delay <= 0)
					{
						if (!List[numBee]->GetAllowDraw())
						{
							List[numBee]->New(position, !flipFlag);
							numBee++;
							if (numBee > 2)
							{
								numBee = 0;
							}
						}
					}
				}
			}
			else
			{
				if (numRound == 4)
				{
					if (velocity.y <= -1)
					{
						numRound = 0;
						state = Bay;
					}
				}
			}
			break;
		}
		case OngChua::Chich:
		{
			if (delay <= 0)
				delay = 50;
			delay--;
			if (delay <= 0)
			{
				velocity.y = -1.5f;
				posStartSwoop = position;
				state = TanCong;
			}
			break;
		}
		case OngChua::TanCong:
		{
			if (position.x < mega->GetPosition().x)
				AddVelocity(0.05f, 0);
			else
				AddVelocity(-0.05f, 0);
			break;
		}
		case OngChua::Phun:
		{
			if (delay <= 0)
				delay = 20;
			delay--;

			if (delay <= 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (!List[i]->GetAllowDraw())
					{
						List[i]->New(position, !flipFlag);
						if (flipFlag)
							List[i]->SetVelocity(1, 0.5 - 0.4*i);
						else
							List[i]->SetVelocity(-1, 0.5 - 0.4*i);
					}
				}
				state = BayVong;
			}
			break;
		}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (List[i]->GetAllowDraw())
		{
			List[i]->Update(dt, key);

			if (kysinh->isCling)
			{
				if (List[i]->GetPosition().x < mega->GetPosition().x)
				{
					List[i]->SetVelocityX(1.5f);
					List[i]->SetFlipFlag(false);
				}
				else
				{
					List[i]->SetVelocityX(-1.5f);
					List[i]->SetFlipFlag(true);
				}

				if (List[i]->GetPosition().y < mega->GetPosition().y)
					List[i]->SetVelocityY(1.0f);
				else
					List[i]->SetVelocityY(-1.0f);
			}
		}
	}

	if (kysinh->appear)
	{
		kysinh->Update(dt, key);

		if (kysinh->isCling)
		{
		  kysinh->SetPosition(mega->GetPosition());
		}
		else
		{
			if (kysinh->GetPosition().x < mega->GetPosition().x)
				kysinh->SetVelocityX(1.0f);
			else
				kysinh->SetVelocityX(-1.0f);

			if (kysinh->GetPosition().y < mega->GetPosition().y)
				kysinh->SetVelocityY(1.0f);
			else
				kysinh->SetVelocityY(-1.0f);

			if (Collision::isCollision(kysinh->GetBound(), mega->GetBound()))
			{
				kysinh->isCling = true;
			}
		}
	}

}


void OngChua::ChangeAnimation(Keyboard *key) {

	SetBound(50, 80);
	switch (state)
	{
	case OngChua::Bay:
	case OngChua::BayVong:
		anim->SetFrame(position, flipFlag, 0.5, 0, 3, true);
		break;
	case OngChua::Chich:
		anim->SetFrame(position, flipFlag, 0.5, 7, 45, false);
		break;
	case OngChua::TanCong:
		anim->SetFrame(position, flipFlag, 0.5, 4, 6, true);
		break;
	case OngChua::Phun:
		anim->SetFrame(position, flipFlag, 0.5, 46, 63, false);
		break;
	case OngChua::Chet:
		break;
	default:
		break;
	}

}




OngChua::~OngChua()
{
}
