#include "Helicope.h"



Helicope::Helicope()
{
}


Helicope::~Helicope()
{
}
Helicope::Helicope(MegaMan *megaman, Sprite *HelicSprite, Sprite *ItemSprite, Sprite *ExplosionSprite, SpriteSheet *HelicSheet,
	SpriteSheet *ItemSheet, SpriteSheet *ExplosionSheet) 
{
	tag = Tag::Enemys;
	this->megaMan = megaman;
	this->sprite = HelicSprite;
	shoot = false;
	animationEnemy = new Animation(HelicSheet);
	for (int i = 0; i < 4; i++) {
		bullets[i] = new Bullet(HelicSprite,HelicSheet);

	}
	numBullet = 0;
	item = new Item(megaman,ItemSprite,ItemSheet);
	explosion = new Explosion(ExplosionSprite,ExplosionSheet);
	collapse = new Collapse(HelicSprite,HelicSheet);

}
void Helicope::Newhelic(D3DXVECTOR2 pos) {

	Enemy::New(pos);
	action = Helicope::Fly;
	shoot = false;
	damage = 2;
	HP = 3;


}
void Helicope::ChangeAnimation(Keyboard* key) {
	SetBound(40, 30);
	/*switch (action)
	{
	case Action::Fly:
		animationEnemy->SetFrame(position, flipFlag, 5, 0, 4, true);
		break;
	case Action::Shoot:
		animationEnemy->SetFrame(position, flipFlag, 15, 1, 4, true);
		break;
	}*/
	animationEnemy->SetFrame(position,flipFlag,5,0,4,true);


}
void Helicope::Update(float dt, Keyboard* key) {
	Enemy::Update(dt, key);
	if (enemyState != Dying)
	{
		if (delay <= 0)
			delay = 40;
		delay--;

		if (delay <= 0)
		{
			switch (action)
			{
			case Helicope::Fly:
			{
				if (abs(megaMan->GetPosition().x - position.x) < 150 && !shoot)
				{
					shoot = true;
					action = Shoot;
				}
				break;
			}
			case Helicope::Shoot:
			{
				action = Fly;
				if (!bullets[numBullet]->GetAllowDraw())
				{
					bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), false, Bullet::BulletHelit);
					if (flipFlag) bullets[numBullet]->SetVelocity(2, 0);
					else bullets[numBullet]->SetVelocity(-2, 0);
					numBullet++;
					if (numBullet > 0)
					{
						numBullet = 0;
						action = Fly;
						shoot = false;
					}
				}
				break;
			}
			}
		}

		if (position.y < megaMan->GetPosition().y + 17)
		{
			//SetVelocity(0, 0.5f);
		}
		else
		{
			//SetVelocity(0, -0.5f);
		}
	}

	//Update đạn
	for (int i = 0; i < 3; i++)
	{
		if (bullets[i]->GetAllowDraw())
		{
			bullets[i]->Update(dt, key);

			if (Collision::isCollision(bullets[i]->GetBound(), megaMan->GetBound()))
			{
				int side;
				if (position.x > megaMan->GetPosition().x)
					side = 1;
				else
					side = -1;
				
				megaMan->GetStateMegaman()->BleedState(side,damage);
				bullets[i]->OnCollision();
			}
		}
	}

}



void Helicope::OnCollision(Object *obj, D3DXVECTOR2 distance) {
	item->OnCollision(obj);

}

void Helicope::OnCollision(Object *obj) {
	HP -= obj->GetDamage();

	if (HP <= 0)
	{
		HP = 0;

		enemyState = Dying;

		//nổ
		explosion->NewExplosion(position);

		//tan rã
		collapse->NewCollapse(position, Collapse::CollapseHelit);

		//item
		item->NewItem(position);
	}
}


void Helicope::Render(Viewport *viewport) {
	if (viewport->isContains(bound))
	{
		if (allowDraw)
		{
			sprite->SetData(
				animationEnemy->GetRect(),
				animationEnemy->GetCenter(),
				animationEnemy->GetPosition(),
				animationEnemy->GetScale(),
				animationEnemy->GetTransform(),
				animationEnemy->GetAngle()
			);
			sprite->Render(viewport);
		}

		for (int i = 0; i < 3; i++)
			if (bullets[i]->GetAllowDraw())
				bullets[i]->Render(viewport);

		if (enemyState == Dying)
		{
			explosion->Render(viewport);
			collapse->Render(viewport);
			item->Render(viewport);
		}
	}
	else
	{
		if (!Collision::isCollision(positionStart.x, positionStart.y, viewport->GetBound()) && !item->GetAppear())
		{
			New(positionStart);
		}
	}

}