#pragma once
#include <vector>

#include "IGameObject.h"
#include "Bullet.h"

#include "Screen.h"

class Asteroid : public IGameObject
{
	CRect rect;
	bool shooted;
public:
	Asteroid();
	Asteroid(CRect rect);

	void Draw(CDC* pDC);
	void Draw(CDC* pDC, CBrush* brush);
	void Move(int dx, int dy);
	bool IsOffScreen();

	CRect& GetRect();
	bool ChechCollision(IGameObject& obj);

	void Shooted();
	bool IsShooted();

	Asteroid& operator=(const Asteroid& other);
};

Asteroid GenerateAsteroid();
bool CheckShooted(std::vector<Bullet> bullets, Asteroid& asteroid);