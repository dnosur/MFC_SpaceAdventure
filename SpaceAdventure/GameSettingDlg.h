#pragma once
#include "afxdialogex.h"


// Диалоговое окно GameSettingDlg

class GameSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GameSettingDlg)

	bool success;

	int speed, fireCooldown, astreoidCooldown;

	void SetSlider(int& value, int sliderId, int staticId, int sliderSize = 30);
	void SetSliderPos(int value, int sliderId, int staticId, int sliderSize = 30);
public:
	GameSettingDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~GameSettingDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMCustomdrawSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawBoolteCooldownSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawAsteroidCooldownSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
