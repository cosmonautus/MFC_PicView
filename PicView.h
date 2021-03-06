
// PicView.h: интерфейс класса CPicView
//

#pragma once


class CPicView : public CView
{
protected: // создать только из сериализации
	CPicView() noexcept;
	DECLARE_DYNCREATE(CPicView)

// Атрибуты
public:
	CPicDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CPicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
//    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // версия отладки в PicView.cpp
inline CPicDoc* CPicView::GetDocument() const
   { return reinterpret_cast<CPicDoc*>(m_pDocument); }
#endif

