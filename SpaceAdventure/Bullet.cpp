#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(): shooted(false)
{
}

Bullet::Bullet(CRect rect) : rect(rect), shooted(false)
{
}

void Bullet::Draw(CDC* pDC)
{
	pDC->Ellipse(&rect);
}

void Bullet::Draw(CDC* pDC, CBrush* brush)
{
	pDC->Ellipse(&rect);
	pDC->FillRect(&rect, brush);
}

void Bullet::Move(int dx, int dy)
{
	rect.OffsetRect(0, -10);
}

bool Bullet::IsOffScreen()
{
	return rect.bottom < 0;
}

CRect& Bullet::GetRect()
{
	return rect;
}

bool Bullet::ChechCollision(IGameObject& obj)
{
	CRect temp = obj.GetRect();
	return temp.IntersectRect(&rect, &obj.GetRect());
}

void Bullet::Shooted()
{
	shooted = true;
}

bool Bullet::IsShooted()
{
	return shooted;
}

Bullet& Bullet::operator=(const Bullet& other)
{
	rect = other.rect;
	shooted = other.shooted;
	return *this;
}
