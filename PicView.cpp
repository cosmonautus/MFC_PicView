
// PicView.cpp: реализация класса CPicView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Pic.h"
#endif

#include "PicDoc.h"
#include "PicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicView

IMPLEMENT_DYNCREATE(CPicView, CView)

BEGIN_MESSAGE_MAP(CPicView, CView)
    ON_WM_ERASEBKGND()
    ON_WM_TIMER()
    ON_WM_CREATE()
END_MESSAGE_MAP()

// Создание или уничтожение CPicView

CPicView::CPicView() noexcept
{
	// TODO: добавьте код создания

}

CPicView::~CPicView()
{
}

BOOL CPicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// Рисование CPicView
void insertRectFromTo(const CRect aFrom, CRect& aTo)
{
    float scale = min((float)aTo.Width() / aFrom.Width(), (float)aTo.Height() / aFrom.Height());
    CRect rNew{ 0, 0, int(aFrom.Width() * scale), int(aFrom.Height() * scale) };
    rNew.OffsetRect((aTo.Width() - rNew.Width()) / 2, (aTo.Height() - rNew.Height()) / 2);
    aTo = rNew;
}

const auto COLOR_PIC_BACKGROUND = RGB(0xFF, 0xFF, 0xE0);

void CPicView::OnDraw(CDC* pDC)
{
    CMemDC memDC(*pDC, this);
    CDC& dc = memDC.GetDC();
    CRect rDst;
    GetClientRect(rDst);
    dc.FillSolidRect(rDst, COLOR_PIC_BACKGROUND);
    CPicDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
    {
        dc.DrawText(_T("НЕТ ДОКУМЕНТА"), rDst, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return;
    }
    ImagePtr img = pDoc->getCurrPic();
    if (img == nullptr || img->IsNull())
    {
        dc.DrawText(_T("НЕТ КАРТИНКИ"), rDst, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return;
    }
    CRect rSrc{ 0, 0, img->GetWidth(), img->GetHeight() };
    insertRectFromTo(rSrc, rDst);

    dc.SetStretchBltMode(HALFTONE);
    img->StretchBlt(dc, rDst, SRCCOPY);
}


// Диагностика CPicView

#ifdef _DEBUG
void CPicView::AssertValid() const
{
	CView::AssertValid();
}

void CPicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicDoc* CPicView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicDoc)));
	return (CPicDoc*)m_pDocument;
}
#endif //_DEBUG

// Обработчики сообщений CPicView

BOOL CPicView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

int CPicView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetTimer(0, 2000, nullptr);

    return 0;
}

void CPicView::OnTimer(UINT_PTR nIDEvent)
{
    GetDocument()->showNextPic();
    CView::OnTimer(nIDEvent);
}

