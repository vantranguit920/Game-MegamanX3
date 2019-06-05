#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "Text.h"
#include "MegaMan.h"
#include "Viewport.h"
#include "Map.h"
#include "QuadTree.h"
#include "Enemy.h"
#include "Lifebar.h"
#include "HeadGun.h"
#include "EleVaTor.h"
#include "Helicope.h"
#include "Frog.h"
#include "OngChua.h"
#include "NguoiMay.h"
#include "StarBoss.h"
class ObjectManager
{
protected:
	MegaMan *megaMan;

	Viewport* viewport;
	Map* map;
	QuadTree  *mQuadTree;
	Lifebar *lifebar;

	vector <Object*> listObjectCollison;
	vector <Object*> listWall;
	vector <Object*> listObject;
	D3DXVECTOR2 prePosView;

	Sprite *sprite_MegaMan;
	Sprite *sprite_Effect;
	Sprite *sprite_Weapons_And_Items;
	Sprite *sprite_Enemy;
	Sprite *sprite_Lifebar;
	Sprite * sprite_Explosion;
	SpriteSheet * spriteSheet_Explosion;
	SpriteSheet* spriteSheetMegaMan;
	SpriteSheet* spriteSheetEffect;
	SpriteSheet* spriteSheetWeaponsAndItems;
	SpriteSheet* spriteSheetEnemy;

	Sprite *smokesprite;
	SpriteSheet *smokesheet;

	//Quai
	Sprite *sprt_HeadGun;
	SpriteSheet *sprtsh_Head;

	Sprite *HelicSprite;
	SpriteSheet *HelicSheet;


	Sprite *FrogSprite;
	SpriteSheet *FrogSheet;



	//Bos
	OngChua *ongchua;
	Sprite *ongchuaSprite;
	SpriteSheet *ongchuaSheet;

	NguoiMay *nguoimay;
	Sprite *nguoimaysprite;
	SpriteSheet *nguoimaysheet;

	StarBoss *starboss;
	Sprite *starsprite;
	SpriteSheet *starSheet;



	//Thang May
	EleVaTor *elevator;
	Sprite *sprite_Elevator;
	SpriteSheet *spritesheet_Elevator;

	
public:
	ObjectManager();
	~ObjectManager();

	void Init(Graphic* graphic);

	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);

	//Vẽ Object lên màn hình
	void Render();

	void ReadQuadTree(TiXmlElement *root, QuadTree *node, QuadTree *father, int indexNode);
};
