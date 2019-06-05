#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::Sprite(Graphic* graphic, const char* pathpng)
{
	this->graphic = graphic;
	texture = this->graphic->LoadTexture(pathpng, D3DCOLOR_XRGB(0, 0, 0));
	this->scale = D3DXVECTOR2(1, 1);
	transform = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2(0, 0);
	color = D3DCOLOR_XRGB(225, 225, 225);
	angle = 0;
	flipFlag = false;
}

Sprite::~Sprite()
{
}

float Sprite::GetWidth()
{
	return this->width;
}

void Sprite::SetWidth(float width)
{
	this->width = width;
}

float Sprite::GetHeight()
{
	return this->height;
}

void Sprite::SetHeight(float height)
{
	this->height = height;
}


void Sprite::SetTexture(const char* pathpng)
{
	texture = graphic->LoadTexture(pathpng, D3DCOLOR_XRGB(0, 0, 0));
}

float Sprite::GetWidthFrame()
{
	return rect.right - rect.left;
}
float Sprite::GetHeightFrame()
{
	return rect.bottom - rect.top;
}

RECT Sprite::GetRect()
{
	return this->rect;
}
void Sprite::SetRect(RECT rect)
{
	this->rect = rect;
}


D3DXVECTOR2 Sprite::GetPosition()
{
	return position;
}
void Sprite::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}


D3DXVECTOR2 Sprite::GetCenter()
{
	return center;
}
void Sprite::SetCenter(D3DXVECTOR2 center)
{
	this->center = center;
}

D3DXVECTOR2 Sprite::GetScale()
{
	return scale;
}
void Sprite::SetScale(D3DXVECTOR2 scale)
{
	this->scale = scale;
}


D3DXVECTOR2 Sprite::GetTransform()
{
	return transform;
}
void Sprite::SetTransform(float x, float y)
{
	transform.x = x;
	transform.y = y;
}


float Sprite::GetAngle()
{
	return angle;
}
void Sprite::SetAngle(float angle)
{
	this->angle = angle;
}


void Sprite::SetFlipFlag(bool flag)
{
	this->flipFlag = flag;
}


void Sprite::Flip(bool flag)
{
	if (flag)
	{
		scale = D3DXVECTOR2(-1, 1);
	}
	else scale = D3DXVECTOR2(1, 1);
}

void Sprite::SetColor(D3DCOLOR color)
{
	this->color = color;
}

void Sprite::SetData(RECT rect, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle)
{
	this->rect = rect;
	this->center = center;
	this->position = position;
	this->scale = scale;
	this->angle = angle;
	this->transform = transform;
}

void Sprite::Update(float dt, Keyboard* key)
{
}


void Sprite::Render()
{
	graphic->DrawTexture(texture, rect, center, position, scale, transform, angle, color);
}


void Sprite::Render(Viewport* viewport)
{
	graphic->DrawTexture(texture, rect, center, viewport->TransformPosition(position), scale, transform, angle, color);
}
