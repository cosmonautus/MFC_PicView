
// Pic.h: основной файл заголовка для приложения Pic
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#include "PicDoc.h"

// CPicApp:
// Сведения о реализации этого класса: Pic.cpp
//

class CPicApp : public CWinApp
{
    UINT_PTR m_timer;
public:
	CPicApp() noexcept;
    CPicDoc* getDocument();


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
    afx_msg void OnViewPic();
    afx_msg void OnViewFolder();
    afx_msg void OnUpdateCmd(CCmdUI *pCmdUI);
};

extern CPicApp theApp;
