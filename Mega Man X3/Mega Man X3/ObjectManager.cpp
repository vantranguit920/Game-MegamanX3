#include "ObjectManager.h"
#include "string.h"

ObjectManager::ObjectManager()
{
}
ObjectManager::~ObjectManager()
{
	delete megaMan;
	delete map;
	delete viewport;
	mQuadTree->Clear();
	delete mQuadTree;
	delete lifebar;

	delete sprite_MegaMan;
	delete sprite_Effect;
	delete sprite_Weapons_And_Items;
	delete sprite_Enemy;

}

//Load Game
void ObjectManager::Init(Graphic* graphic)
{
	sprite_MegaMan = new Sprite(graphic, MegaManPNG);
	sprite_Effect = new Sprite(graphic, EffectPNG);
	sprite_Weapons_And_Items = new Sprite(graphic, WeaponsAndItemsPNG);
	
	sprite_Lifebar = new Sprite(graphic, WeaponsAndItemsPNG);

	spriteSheetMegaMan = new SpriteSheet(MegaManXML);
	spriteSheetEffect = new SpriteSheet(EffectXML);
	spriteSheetWeaponsAndItems = new SpriteSheet(WeaponsAndItemsEffectXML);

	smokesprite = new Sprite(graphic,SmokePNG);
	smokesheet = new SpriteSheet(SmokeXML);


	sprite_Explosion = new Sprite(graphic, ExplosionPNG);
	spriteSheet_Explosion = new SpriteSheet(ExplosionXML);


	/*Quai*/
	sprt_HeadGun = new Sprite(graphic, HeadGunnerPNG);
	sprtsh_Head = new SpriteSheet(HeadGunnerXML);

	HelicSprite = new Sprite(graphic, HelicPNG);
	HelicSheet = new SpriteSheet(HelicXML);

	FrogSprite = new Sprite(graphic,FrogPNG);
	FrogSheet = new SpriteSheet(FrogXML);

	
	//
	megaMan = new MegaMan(sprite_MegaMan, sprite_Effect, sprite_Weapons_And_Items,
		spriteSheetMegaMan, spriteSheetEffect, spriteSheetWeaponsAndItems);

	//Thang may
	sprite_Elevator = new Sprite(graphic,ElevatorPNG);
	spritesheet_Elevator = new SpriteSheet(ElevatorXML);
	elevator = new EleVaTor(megaMan,sprite_Elevator,spritesheet_Elevator, D3DXVECTOR2(896, 1086));


	
	//boss
	ongchuaSprite = new Sprite(graphic,OngchuaPNG);
	ongchuaSheet = new SpriteSheet(OngchuaXML);
	ongchua = new OngChua(megaMan,ongchuaSprite,ongchuaSheet, D3DXVECTOR2(7880, 180));




	nguoimaysprite = new Sprite(graphic,NguoimayPNG);
	nguoimaysheet = new SpriteSheet(NguoimayXML);
	nguoimay = new NguoiMay(nguoimaysprite,smokesprite,sprite_Explosion,nguoimaysheet,smokesheet,spriteSheet_Explosion, D3DXVECTOR2(5830, 890));


	starsprite = new Sprite(graphic,BossStarPNG);
	starSheet = new SpriteSheet(BossStarXML);
	starboss = new StarBoss(megaMan,starsprite,starSheet, D3DXVECTOR2(2480, 870));

	//
	
	viewport = new Viewport(0, 1248);

	map = new Map(graphic);

	//Tạo quadtree và đọc
	mQuadTree = new QuadTree();
	TiXmlDocument doc(QuadTreeXML);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load QuadTree.xml file", "Error", MB_OK);
		return;
	}
	TiXmlElement* root = doc.RootElement();
	ReadQuadTree(root, mQuadTree, NULL, -1);
	mQuadTree->GetObjectsCollideAble(listObjectCollison, listWall, viewport->GetBound());
	prePosView = viewport->GetPosition();

	lifebar = new Lifebar(sprite_Lifebar, spriteSheetWeaponsAndItems);
}

//Update Game
void ObjectManager::Update(float dt, Keyboard* keyboard)
{
	megaMan->ChangeAnimation(dt, keyboard);
	
	//Kiểm tra va chạm
	if (prePosView != viewport->GetPosition())
	{
		prePosView = viewport->GetPosition();
		listWall.clear();
		//List lưu đối tượng quái còn trong màn hình trước đó
		mQuadTree->GetObjectsCollideAble(listObject, listWall, viewport->GetBound());
		//Đổi 2 vector
		listObjectCollison.swap(listObject);
	}
	listObject.clear();

	//Va chạm Man với tường
	for (size_t i = 0; i < listWall.size(); i++)
	{
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		megaMan->OnCollision(listWall.at(i), disMan, disMan);
	}

	//Va chạm Object
	for (size_t i = 0; i < listObjectCollison.size(); i++)
	{
		for (size_t j = 0; j < listWall.size(); j++)
		{
			D3DXVECTOR2 disEnemy = listObjectCollison.at(i)->Distance(dt);
			listObjectCollison.at(i)->OnCollision(listWall.at(j), disEnemy);
		}

		//Va chạm của quái
		if (listObjectCollison.at(i)->tag == Object::Tag::Enemys && listObjectCollison.at(i)->GetAllowDraw())
		{
			//Mega Man
			D3DXVECTOR2 disMan = megaMan->Distance(dt);
			D3DXVECTOR2 distance = disMan - listObjectCollison.at(i)->Distance(dt);
			megaMan->OnCollision(listObjectCollison.at(i), distance, disMan);

			//Đạn Mega Man
			for (int j = 0; j < 4; j++)
			{	
				if (megaMan->bullets[j]->GetAllowDraw() && megaMan->bullets[j]->GetBulletState() == Bullet::Firing)
				{
					if (Collision::isCollision(megaMan->bullets[j]->GetBound(), listObjectCollison.at(i)->GetBound()))
					{
						listObjectCollison.at(i)->OnCollision(megaMan->bullets[j]);
						megaMan->bullets[j]->OnCollision();
					}
				}
			}

			//Kiểm tra con quái nào còn trong màn hình và chưa chết
			if (viewport->isContains(listObjectCollison.at(i)->GetBound()))
				listObject.push_back(listObjectCollison.at(i));
		}

		//Update
		listObjectCollison.at(i)->Update(dt, keyboard);
	}


	//Len Thang May
	if (elevator->GetAllowDraw()) {

		elevator->OnCollision(megaMan);
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - elevator->Distance(dt);

		megaMan->OnCollision(elevator, distance, disMan);
		elevator->Update(dt,keyboard);

	}
	//Boss Ong Chua
	if (ongchua->GetAllowDraw()) {
		for (size_t i = 0; i < listWall.size(); i++) {


			D3DXVECTOR2 disOngChua = ongchua->Distance(dt);

			ongchua->OnCollision(listWall.at(i), disOngChua);

			for (int k = 0; k < 5; k++) {
				D3DXVECTOR2 disOng = ongchua->List[k]->Distance(dt);
				ongchua->List[k]->OnCollision(listWall.at(i),disOng);
			}



		}

		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - ongchua->Distance(dt);
		megaMan->OnCollision(ongchua, distance, disMan);

		ongchua->Update(dt, keyboard);
	}

	//Boss Nguoi May

	if (nguoimay->GetAllowDraw()) {
		for (size_t i = 0; i < listWall.size(); i++) {


			D3DXVECTOR2 disNguoimay = nguoimay->Distance(dt);

			nguoimay->OnCollision(listWall.at(i), disNguoimay);			
		}

		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - nguoimay->Distance(dt);
		megaMan->OnCollision(nguoimay, distance, disMan);

		nguoimay->Update(dt, keyboard);
	}

	//BossStar


	if (starboss->GetAllowDraw()) {
		for (size_t i = 0; i < listWall.size(); i++) {


			D3DXVECTOR2 disstar = starboss->Distance(dt);

			starboss->OnCollision(listWall.at(i), disstar);
		}

		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - starboss->Distance(dt);
		megaMan->OnCollision(starboss, distance, disMan);

		starboss->Update(dt, keyboard);
	}



	//


	megaMan->Update(dt, keyboard);
	if(megaMan->GetPosition().x >= 7734) {

		ongchua->SetAllowDraw(true);
	}
	else if (megaMan->GetPosition().x >= 5380) {

		nguoimay->SetAllowDraw(true);
	}
	else if (megaMan->GetPosition().x >= 2400) {

		starboss->SetAllowDraw(true);
	}

	viewport->Update(dt, keyboard, megaMan->GetPosition(), megaMan->GetVelocity(), map->listStage);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);

	megaMan->Render(viewport);

	ongchua->Render(viewport);

	nguoimay->Render(viewport);
	starboss->Render(viewport);

	elevator->Render(viewport);

	//Vẽ Object
	for (size_t i = 0; i < listObjectCollison.size(); i++)
	{
		listObjectCollison.at(i)->Render(viewport);
	}

	lifebar->Render(megaMan->GetHP(),megaMan->GetHPMax());

}

bool IsExist(int id, int indexNode, QuadTree *node, QuadTree *father)
{
	if (!father)
		return false;
	for (int i = 0; i < indexNode; i++)
	{
		for (size_t j = 0; j < father->Nodes[i]->mListObject.size(); j++)
		{
			if (father->Nodes[i]->mListObject.at(j)->id == id)
			{
				node->mListObject.push_back(father->Nodes[i]->mListObject.at(j));
				return true;
			}
		}
	}

	return false;
}

void ObjectManager::ReadQuadTree(TiXmlElement *root, QuadTree *node, QuadTree *father, int indexNode)
{
	if (!root)
		return;
	RECT r;
	int left, top, right, bottom, numObj;
	root->QueryIntAttribute("left", &left);
	root->QueryIntAttribute("top", &top);
	root->QueryIntAttribute("right", &right);
	root->QueryIntAttribute("bottom", &bottom);
	r.left = left;
	r.right = right;
	r.top = top;
	r.bottom = bottom;
	node->Bound = r;
	root->QueryIntAttribute("level", &node->mLevel);
	root->QueryIntAttribute("numObj", &numObj);
	TiXmlElement *child = root->FirstChildElement();
	for (size_t i = 0; i < numObj; i++)
	{
		int id;
		child->QueryIntAttribute("id", &id);
		if (!IsExist(id, indexNode, node, father))
		{

			float x, y, w, h;
			child->QueryFloatAttribute("x", &x);
			child->QueryFloatAttribute("y", &y);
			child->QueryFloatAttribute("w", &w);
			child->QueryFloatAttribute("h", &h);

			string name = (char*)child->Attribute("name");
			Object::Tag tag = Object::GetTag(name);
			
			if (name == "HeadGunner")
			{
				HeadGun *enemy = new HeadGun(megaMan,sprt_HeadGun, sprite_Weapons_And_Items, sprite_Explosion,
					sprtsh_Head, spriteSheetWeaponsAndItems, spriteSheet_Explosion);

				enemy->SetFlipFlag(false);
				enemy->NewII(D3DXVECTOR2(x, y));


			
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else 
			if(name=="Helit")
			{
				Helicope *enemy = new Helicope(megaMan,HelicSprite,sprite_Weapons_And_Items,sprite_Explosion,HelicSheet,
					spriteSheetWeaponsAndItems,spriteSheet_Explosion);
				enemy->SetFlipFlag(false);
				enemy->Newhelic(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);

			}
			else if(name == "Frog")
			{
				Frog *enemy = new Frog(megaMan, FrogSprite, sprite_Weapons_And_Items, sprite_Explosion, FrogSheet,
					spriteSheetWeaponsAndItems, spriteSheet_Explosion);

				enemy->SetFlipFlag(false);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			
			else
			{
				Object *obj = new Object();
				child->QueryIntAttribute("id", &obj->id);
				obj->SetTag(name);
				obj->SetPosition(D3DXVECTOR2(x, y));
				obj->SetBound(w, h);
				obj->SetName(name);
				obj->SetPositionStart(D3DXVECTOR2(x, y));
				obj->id = id;
				node->mListObject.push_back(obj);
			}
		}
		child = child->NextSiblingElement();
	}
	if (child)
	{
		node->Nodes = new QuadTree*[4];
		for (int i = 0; i < 4; i++)
		{
			node->Nodes[i] = new QuadTree();
			ReadQuadTree(child, node->Nodes[i], node, i);
			child = child->NextSiblingElement();
		}
	}
}
