// GameSettingDlg.cpp: файл реализации
//

#include "pch.h"
#include "SpaceAdventure.h"
#include "afxdialogex.h"
#include "GameSettingDlg.h"


// Диалоговое окно GameSettingDlg

IMPLEMENT_DYNAMIC(GameSettingDlg, CDialogEx)

void GameSettingDlg::SetSlider(int& value, int sliderId, int staticId, int sliderSize)
{
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(sliderId);
	CStatic* label = (CStatic*)GetDlgItem(staticId);

	slider->SetRange(0, sliderSize);
	value = slider->GetPos();

	CString str;
	str.Format(L"%d", value);
	label->SetWindowTextW(str);
}

void GameSettingDlg::SetSliderPos(int value, int sliderId, int staticId, int sliderSize)
{
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(sliderId);
	CStatic* label = (CStatic*)GetDlgItem(staticId);

	slider->SetRange(0, sliderSize);
	slider->SetPos(value);

	CString str;
	str.Format(L"%d", value);
	label->SetWindowTextW(str);
}

GameSettingDlg::GameSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent), success(false),
	speed(50), fireCooldown(10), astreoidCooldown(20)
{

}

GameSettingDlg::~GameSettingDlg()
{
}

void GameSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GameSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GameSettingDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SPEED_SLIDER, &GameSettingDlg::OnNMCustomdrawSpeedSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BULLET_COOLDOWN_SLIDER, &GameSettingDlg::OnNMCustomdrawBoolteCooldownSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ASTEROID_COOLDOWN_SLIDER2, &GameSettingDlg::OnNMCustomdrawAsteroidCooldownSlider2)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// Обработчики сообщений GameSettingDlg


void GameSettingDlg::OnBnClickedOk()
{
	success = true;
	CDialogEx::OnOK();
}


void GameSettingDlg::OnBnClickedCancel()
{
	success = false;
	CDialogEx::OnCancel();
}


void GameSettingDlg::OnNMCustomdrawSpeedSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(speed, IDC_SPEED_SLIDER, IDC_SPEED_EDIT, 100);
	*pResult = 0;
}


void GameSettingDlg::OnNMCustomdrawBoolteCooldownSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(fireCooldown, IDC_BULLET_COOLDOWN_SLIDER, IDC_BULLET_COOLDOWN_EDIT, 100);
	*pResult = 0;
}


void GameSettingDlg::OnNMCustomdrawAsteroidCooldownSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(astreoidCooldown, IDC_ASTEROID_COOLDOWN_SLIDER2, IDC_ASTEROID_COOLDOWN_EDIT2, 100);
	*pResult = 0;
}


void GameSettingDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	SetSliderPos(speed, IDC_SPEED_SLIDER, IDC_SPEED_EDIT, 100);
	SetSliderPos(fireCooldown, IDC_BULLET_COOLDOWN_SLIDER, IDC_BULLET_COOLDOWN_EDIT, 100);
	SetSliderPos(astreoidCooldown, IDC_ASTEROID_COOLDOWN_SLIDER2, IDC_ASTEROID_COOLDOWN_EDIT2, 100);
}
