#pragma once
#include <afxwin.h>

__interface IGameObject {
	void Draw(CDC* pDC);
	void Draw(CDC* pDC, CBrush* brush);
	void Move(int dx, int dy);
	bool IsOffScreen();

	CRect& GetRect();
	bool ChechCollision(IGameObject& obj);
};