
// SpaceAdventureDlg.h: файл заголовка
//

#pragma once
#include <vector>

#include "GameSettingDlg.h"
#include "GameOverDlg.h"

#include "IGameObject.h"

#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"

#include "Keys.h"
#include "Colors.h"
#include "Screen.h"


// Диалоговое окно CSpaceAdventureDlg
class CSpaceAdventureDlg : public CDialogEx
{
	Ship ship;

	std::vector<Bullet> bullets;
	std::vector<Asteroid> asteroids;

	bool left, right, up, down, shift;
	int score;

	int speed;
	int asteroidCooldownMax, fireCooldownMax;

	bool start;

	CBrush backgroundBrush;
	CBrush asteroidBrush;
	CBrush bulletBrush;
	CBrush shipBrush;

	CFont scoreFont;

	void Start();
	void End();
// Создание
public:
	CSpaceAdventureDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPACEADVENTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
