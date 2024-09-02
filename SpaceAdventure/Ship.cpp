#include "pch.h"
#include "Ship.h"

void Ship::Draw(CDC* pDC)
{
	pDC->Rectangle(&rect);
}

void Ship::Draw(CDC* pDC, CBrush* brush)
{
	pDC->Ellipse(&rect);
	pDC->FillRect(&rect, brush);
}

void Ship::Move(int dx, int dy)
{
	rect.OffsetRect(dx, dy);
}

bool Ship::IsOffScreen()
{
	return rect.top > 600 || rect.bottom < 0;
}

CRect& Ship::GetRect()
{
	return rect;
}

bool Ship::ChechCollision(IGameObject& obj)
{
	CRect temp = obj.GetRect();
	return temp.IntersectRect(&rect, &obj.GetRect());
}

void Ship::SetRect(CRect rect)
{
	this->rect = rect;
}

Bullet Ship::Shoot()
{
	return Bullet(CRect(rect.left + 20, rect.top - 10, rect.right - 20, rect.top));
}
