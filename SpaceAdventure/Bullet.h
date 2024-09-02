#pragma once
#include "IGameObject.h"

class Bullet : public IGameObject
{
	CRect rect;
	bool shooted;
public:
	Bullet();
	Bullet(CRect rect);

	void Draw(CDC* pDC);
	void Draw(CDC* pDC, CBrush* brush);
	void Move(int dx, int dy);
	bool IsOffScreen();

	CRect& GetRect();
	bool ChechCollision(IGameObject& obj);

	void Shooted();
	bool IsShooted();

	Bullet& operator=(const Bullet& other);
};

