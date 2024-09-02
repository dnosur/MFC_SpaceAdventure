#include "pch.h"
#include "Asteroid.h"

Asteroid::Asteroid(): shooted(false)
{
}

Asteroid::Asteroid(CRect rect) : rect(rect), shooted(false)
{
}

void Asteroid::Draw(CDC* pDC)
{
	pDC->Ellipse(&rect);
}

void Asteroid::Draw(CDC* pDC, CBrush* brush)
{
	pDC->Ellipse(&rect);
	pDC->FillRect(&rect, brush);
}

void Asteroid::Move(int dx, int dy)
{
	rect.OffsetRect(0, 5);
}

bool Asteroid::IsOffScreen()
{
	return rect.top > 600;
}

CRect& Asteroid::GetRect()
{
	return rect;
}

bool Asteroid::ChechCollision(IGameObject& obj)
{
	CRect temp = obj.GetRect();
	return temp.IntersectRect(&rect, &obj.GetRect());
}

void Asteroid::Shooted()
{
	shooted = true;
}

bool Asteroid::IsShooted()
{
	return shooted;
}

Asteroid& Asteroid::operator=(const Asteroid& other)
{
	rect = other.rect;
	shooted = other.shooted;
	return *this;
}

Asteroid GenerateAsteroid()
{
	int size = rand() % 50 + 20;
	int x = rand() % SCREEN_WIDTH;

	return Asteroid(CRect(x, 0, x + size, size));
}

bool CheckShooted(std::vector<Bullet> bullets, Asteroid& asteroid)
{
	for (Bullet& bullet : bullets) {
		if (!asteroid.ChechCollision(bullet)) {
			continue;
		}

		bullet.Shooted();
		asteroid.Shooted();
		return true;
	}
	return false;
}
