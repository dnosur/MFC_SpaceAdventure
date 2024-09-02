
// SpaceAdventure.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CSpaceAdventureApp:
// Сведения о реализации этого класса: SpaceAdventure.cpp
//

class CSpaceAdventureApp : public CWinApp
{
public:
	CSpaceAdventureApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSpaceAdventureApp theApp;
