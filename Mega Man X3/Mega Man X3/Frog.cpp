#include "Frog.h"



Frog::Frog()
{
}
Frog::Frog(MegaMan *megaman, Sprite *frog_sprite, Sprite *item, Sprite *explosion, SpriteSheet *frog_sheet, SpriteSheet *item_sheet, SpriteSheet *explosion_sheet)
{
	tag = Tag::Enemys;
	this->megaMan = megaman;
	sprite = frog_sprite;
	animationEnemy = new Animation(frog_sheet);
	for (int i = 0; i < 4; i++) {

		bullets[i] = new Bullet(frog_sprite,frog_sheet);

	}
	numBullet = 0;
	this->item = new Item(megaman,item,item_sheet);
	this->explosion = new Explosion(explosion,explosion_sheet);
	this->collapse = new Collapse(frog_sprite,frog_sheet);


}
void Frog::New(D3DXVECTOR2 pos) {
	Enemy::New(pos);
	FrogAction = Action::Standing;
	shoot = false;
	jump = false;
	damage = 2;
	HP = 3;

}
void Frog::ChangeAnimation(Keyboard *key) {

	SetBound(30, 30);
	switch (FrogAction)
	{

	case Frog::Standing:
		animationEnemy->SetFrame(position, flipFlag, 0, 0, 0, false);
		break;
	case Frog::TargetSkew:
		animationEnemy->SetFrame(position, flipFlag, 5, 0, 2, false);
		break;
	case Frog::TargetVertical:
		animationEnemy->SetFrame(position, flipFlag, 5, 0, 4, false);
		break;
	case Frog::BackShootingSkew:
		animationEnemy->SetFrame(position, flipFlag, 10, 7, 9, false);
		break;
	case Frog::BackShootingVertical:
		animationEnemy->SetFrame(position, flipFlag, 10, 5, 9, false);
		break;
	case Frog::ShootingVertical:
		animationEnemy->SetFrame(position, flipFlag, 15, 10, 11, true);
		break;
	case Frog::ShootingSkew:
		animationEnemy->SetFrame(position, flipFlag, 15, 12, 13, true);
		break;
	case Frog::Moving:
		animationEnemy->SetFrame(position, flipFlag, 10, 14, 18, false);
		break;
	default:
		break;
	}

}

void Frog::Update(float dt,Keyboard *key) {

	Enemy::Update(dt, key);

	if (enemyState != Dying)
	{
		if (!jump)
		{
			if (delay <= 0)
				delay = 40;
			delay--;

			if (delay <= 0)
			{
				switch (FrogAction)
				{
				case Frog::Standing:
				{
					if (abs(megaMan->GetPosition().x - position.x) < 150)
					{
						FrogAction = Moving;
						if (abs(megaMan->GetPosition().x - position.x) < 100 && !shoot)
						{
							FrogAction = TargetSkew;
							if (abs(megaMan->GetPosition().x - position.x) < 50)
							{
								FrogAction = TargetVertical;
							}
						}
					}

					if (position.x < megaMan->GetPosition().x)
						flipFlag = true;
					else
						flipFlag = false;
					break;
				}
				case Frog::TargetSkew:
				{
					shoot = true;
					FrogAction = ShootingSkew;
					break;
				}
				case Frog::TargetVertical:
				{
					shoot = true;
					FrogAction = ShootingVertical;
					break;
				}
				case Frog::ShootingSkew:
				{
					if (!bullets[numBullet]->GetAllowDraw())
					{
						bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), flipFlag, Bullet::BulletFrog);
						if (flipFlag) bullets[numBullet]->SetVelocity(2, 2);
						else bullets[numBullet]->SetVelocity(-2, 2);
						numBullet++;
						if (numBullet > 2)
						{
							numBullet = 0;
							FrogAction = BackShootingSkew;
						}
					}
					break;
				}
				case Frog::ShootingVertical:
				{
					if (!bullets[numBullet]->GetAllowDraw())
					{
						bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), flipFlag, Bullet::BulletFrog);
						if (flipFlag) bullets[numBullet]->SetVelocity(1, 3);
						else bullets[numBullet]->SetVelocity(-1, 3);
						numBullet++;
						if (numBullet > 2)
						{
							numBullet = 0;
							FrogAction = BackShootingVertical;
						}
					}
					break;
				}
				case Frog::BackShootingSkew:
				case Frog::BackShootingVertical:
				{
					FrogAction = Standing;
				    shoot = false;
					break;
				}
				case Frog::Moving:
				{
					if (flipFlag)
						SetVelocity(1.5f, 1.5f);
					else
						SetVelocity(-1.5f, 1.5f);
					jump = true;
					break;
				}
				default:
					break;
				}
			}
		}
		else
			AddVelocity(0, -0.1);
	}

	//Update đạn
	for (int i = 0; i < 3; i++)
	{
		if (bullets[i]->GetAllowDraw())
		{
			bullets[i]->Update(dt, key);
			bullets[i]->AddVelocity(0, -0.3);
			if (Collision::isCollision(bullets[i]->GetBound(), megaMan->GetBound()))
			{
				int side;
				if (position.x > megaMan->GetPosition().x)
					side = 1;
				else
					side = -1;
				megaMan->GetStateMegaman()->BleedState(side, damage);
				bullets[i]->OnCollision();
			}
		}
	}
}

void Frog::OnCollision(Object *obj) {

	HP -= obj->GetDamage();

	if (HP <= 0)
	{
		HP = 0;
		enemyState = Dying;
		//nổ
		explosion->NewExplosion(position);
		//tan rã
		collapse->NewCollapse(position, Collapse::CollapseNotorBanger);
		//item
		item->NewItem(position);
	}

}
void Frog::OnCollision(Object *obj, D3DXVECTOR2 distance) {


	RECT board = this->GetBoard(distance);

	//Nếu other trong vùng di chuyển
	if (Collision::isCollision(board, obj->GetBound()))
	{
		if (!Collision::isNested(GetBound(), obj->GetBound()))
		{
			//Lấy cạnh va chạm
			D3DXVECTOR2 sideCollision;

			//Lấy thời gian va chạm
			float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

			//Bé hơn 1 thì có va chạm
			if (time < 1.0f)
			{
				if (sideCollision.x != 0.0f)
				{
					position.x += distance.x * time;
					velocity.x = 0;
				}
				else if (sideCollision.y != 0)
				{
					position.y += distance.y * time;
				}

				if (sideCollision.y == 1) // va cham duoi
				{
					SetVelocity(0, 0);
					FrogAction = Standing;
					jump = false;
				}
			}
		}
	}

	item->OnCollision(obj);

}
void Frog::Render(Viewport *view) {

	if (view->isContains(bound))
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
			sprite->Render(view);
		}

		for (int i = 0; i < 3; i++)
			if (bullets[i]->GetAllowDraw())
				bullets[i]->Render(view);

		if (enemyState == Dying)
		{
			explosion->Render(view);
			collapse->Render(view);
			item->Render(view);
		}
	}
	else
	{
		if (!Collision::isCollision(positionStart.x, positionStart.y, view->GetBound()) && !item->GetAppear())
		{
			New(positionStart);
		}
	}

}
Frog::~Frog()
{
}
