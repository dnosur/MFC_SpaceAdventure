#pragma once
#include "IGameObject.h"

#include "Bullet.h"

class Ship : public IGameObject
{
	CRect rect;
public:
	void Draw(CDC* pDC);
	void Draw(CDC* pDC, CBrush* brush);
	void Move(int dx, int dy);
	bool IsOffScreen();

	CRect& GetRect();
	bool ChechCollision(IGameObject& obj);

	void SetRect(CRect rect);
	Bullet Shoot();
};