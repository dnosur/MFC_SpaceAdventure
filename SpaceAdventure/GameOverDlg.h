#pragma once
#include "afxdialogex.h"


// Диалоговое окно GameOverDlg

class GameOverDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GameOverDlg)

	int score;

	bool retry;

	CFont m_fontGameOver;
	CFont m_fontScore;
	COLORREF m_colorGameOver;
	COLORREF m_colorScore;
	CString m_strScore;
public:
	GameOverDlg(int score, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~GameOverDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
};
