// GameOverDlg.cpp: файл реализации
//

#include "pch.h"
#include "SpaceAdventure.h"
#include "afxdialogex.h"
#include "GameOverDlg.h"


// Диалоговое окно GameOverDlg

IMPLEMENT_DYNAMIC(GameOverDlg, CDialogEx)

GameOverDlg::GameOverDlg(int score, CWnd* pParent /*=nullptr*/)
	: score(score), CDialogEx(IDD_DIALOG2, pParent)
{

}

GameOverDlg::~GameOverDlg()
{
}

void GameOverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameOverDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GameOverDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GameOverDlg::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Обработчики сообщений GameOverDlg


void GameOverDlg::OnBnClickedOk()
{
	retry = true;
	CDialogEx::OnOK();
}


void GameOverDlg::OnBnClickedCancel()
{
	retry = false;
	CDialogEx::OnCancel();
}


void GameOverDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
    m_fontGameOver.CreatePointFont(300, _T("Arial"));
    m_colorGameOver = RGB(255, 0, 0);

    m_fontScore.CreatePointFont(200, _T("Arial"));
    m_colorScore = RGB(229, 200, 130);

    m_strScore.Format(_T("Score: %d"), score);

    CFont* pOldFont = dc.SelectObject(&m_fontGameOver);
    dc.SetTextColor(m_colorGameOver);
    dc.SetBkMode(TRANSPARENT);

    CRect rectGameOver;
    GetClientRect(&rectGameOver);
    rectGameOver.top = 20;
    rectGameOver.bottom = 100;
    dc.DrawText(_T("Game Over!"), &rectGameOver, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    dc.SelectObject(&m_fontScore);
    dc.SetTextColor(m_colorScore);

    CRect rectScore;
    GetClientRect(&rectScore);
    rectScore.top = 100;
    rectScore.bottom = 180;
    dc.DrawText(m_strScore, &rectScore, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    dc.SelectObject(pOldFont);
}
