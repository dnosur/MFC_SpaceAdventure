
// SpaceAdventureDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "SpaceAdventure.h"
#include "SpaceAdventureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Диалоговое окно CSpaceAdventureDlg

void CSpaceAdventureDlg::Start()
{
	GameSettingDlg gameSetting;
	if (!gameSetting.DoModal() || !gameSetting.success) {
		return EndDialog(IDOK);
	}

	speed -= gameSetting.speed - speed;

	fireCooldownMax = gameSetting.fireCooldown;
	asteroidCooldownMax = gameSetting.astreoidCooldown;

	score = 0;
	start = true;

	ship.SetRect(CRect(250, 500, 300, 550));
	
	bullets.clear();
	asteroids.clear();

	SetTimer(1, speed, nullptr);
	SetTimer(2, 50, nullptr);

	Invalidate();
}

void CSpaceAdventureDlg::End()
{
	KillTimer(1);

	start = false;
	GameOverDlg gameOver(score);

	if (!gameOver.DoModal() || !gameOver.retry) {
		return EndDialog(IDOK);
	}

	Start();
}

CSpaceAdventureDlg::CSpaceAdventureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPACEADVENTURE_DIALOG, pParent),
	left(false), right(false), up(false), down(false),
	start(false), score(0), speed(50),
	asteroidCooldownMax(20), fireCooldownMax(10),
	backgroundBrush(BACKGROUND_COLOR),
	asteroidBrush(ASTEROID_COLOR), 
	bulletBrush(BULLET_COLOR),
	shipBrush(SHIP_COLOR)
{
	ship.SetRect(CRect(250, 500, 300, 550));
	scoreFont.CreatePointFont(200, _T("Arial"));
}

void CSpaceAdventureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceAdventureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// Обработчики сообщений CSpaceAdventureDlg

BOOL CSpaceAdventureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowPos(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOZORDER);
	Start();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CSpaceAdventureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSpaceAdventureDlg::OnPaint()
{
	if (!start) {
		return;
	}

	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect, &backgroundBrush);

	ship.Draw(&dc, &shipBrush);

	for (Bullet& bullet : bullets) {
		if (bullet.IsShooted()) {
			continue;
		}
		bullet.Draw(&dc, &bulletBrush);
	}

	for (Asteroid& asteroid : asteroids) {
		if (asteroid.IsShooted()) {
			continue;
		}
		asteroid.Draw(&dc, &asteroidBrush);
	}

	CFont* pOldFont = dc.SelectObject(&scoreFont);

	dc.SetTextColor(RGB(255, 255, 0));
	dc.SetBkMode(TRANSPARENT);

	CString scoreText;
	scoreText.Format(_T("Score: %d"), score);
	dc.TextOut(10, 10, scoreText);

	dc.SelectObject(pOldFont);
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSpaceAdventureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSpaceAdventureDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {

		int speed = shift ? 10 : 0;
		if (left) {
			ship.Move(-(15 + speed), 0);
		}

		if (right) {
			ship.Move(15 + speed, 0);
		}

		if (up) {
			ship.Move(0, -(15 + speed));
		}

		if (down) {
			ship.Move(0, 15 + speed);
		}

		static double asteroidCooldown = 0;
		if (asteroidCooldown++ >= asteroidCooldownMax * 1.0 - score / 100) {
			asteroidCooldown = .0;
			asteroids.push_back(GenerateAsteroid());
		}

		for (Asteroid& asteroid : asteroids) {
			asteroid.Move(0, 5);

			score += CheckShooted(bullets, asteroid) ? 1 : 0;
		}

		asteroids.erase(
			std::remove_if(
				asteroids.begin(), 
				asteroids.end(), 
				[](Asteroid& a) { 
					return a.IsOffScreen() || a.IsShooted(); 
				}
			), 
			asteroids.end()
		);

		for (Asteroid& asteroid : asteroids) {
			if (!ship.ChechCollision(asteroid)) {
				continue;
			}

			return End();
		}

		Invalidate();
	}

	if (nIDEvent == 2) {
		static double fireCooldown = 0;
		if (fireCooldown++ >= fireCooldownMax) {
			fireCooldown = .0;
			bullets.push_back(ship.Shoot());
		}

		for (Bullet& bullet : bullets) {
			bullet.Move(0, -10);
		}

		bullets.erase(
			std::remove_if(
				bullets.begin(),
				bullets.end(),
				[](Bullet& b) {
					return b.IsOffScreen() || b.IsShooted();
				}
			),
			bullets.end()
		);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CSpaceAdventureDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == LEFT_KEY) {
		left = false;
	}

	if (nChar == RIGHT_KEY) {
		right = false;
	}

	if (nChar == UP_KEY) {
		up = false;
	}

	if (nChar == DOWN_KEY) {
		down = false;
	}

	if (nChar == SHIFT_KEY) {
		shift = false;
	}

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CSpaceAdventureDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if (nChar == LEFT_KEY) {
		left = true;
	}
		
	if (nChar == RIGHT_KEY) {
		right = true;
	}
		
	if (nChar == UP_KEY) {
		up = true;
	}
		
	if (nChar == DOWN_KEY) {
		down = true;
	}

	if (nChar == SHIFT_KEY) {
		shift = true;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CSpaceAdventureDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillRect(&rect, &backgroundBrush);
	return CDialogEx::OnEraseBkgnd(pDC);
}
