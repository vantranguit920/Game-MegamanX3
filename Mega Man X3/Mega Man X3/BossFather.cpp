#include "BossFather.h"



BossFather::BossFather()
{
}


BossFather::~BossFather()
{
	delete anim;
}
void BossFather::Update(float time,Keyboard *key) {
	Object::Update(time, key);

}
void BossFather::Render(Viewport *view) {

}
void BossFather::OnCollision() {

}
void BossFather::OnCollision(Object *obj) {

}
void BossFather::OnCollision(Object *obj,D3DXVECTOR2 posDistance) {

}
void BossFather::ChangeAnimation(Keyboard *key) {

}
