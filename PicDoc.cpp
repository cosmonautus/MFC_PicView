
// PicDoc.cpp: реализация класса CPicDoc 
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Pic.h"
#endif

#include "PicDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPicDoc

IMPLEMENT_DYNCREATE(CPicDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CPicDoc

CPicDoc::CPicDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CPicDoc::~CPicDoc()
{
}

BOOL CPicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}

// Сериализация CPicDoc

void CPicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

// Диагностика CPicDoc

#ifdef _DEBUG
void CPicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CPicDoc


void CPicDoc::viewPicFromFile(const CString aFileName)
{
    m_currImg = -1;
    m_images.clear();
    ImagePtr img = std::make_shared<CImage>();
    if (img->Load(aFileName) != S_OK)
        ::AfxMessageBox(CString(_T("Невозможно загрузить файл: ")) + aFileName, MB_ICONERROR + MB_OK);
    else
    {
        m_images.push_back(img);        
        m_currImg = 0;
    }
    UpdateAllViews(nullptr);
}

void getListFiles(const CString aMask, CStringArray& aList)
{
    CFileFind find;
    bool isWorking = find.FindFile(aMask);
    while (isWorking)
    {
        isWorking = find.FindNextFileW();
        if (find.IsDots() | find.IsDirectory())
            continue;
        aList.Add(find.GetFilePath());
    }
}

void CPicDoc::viewPicFromFolder(const CString aFolderName)
{
    m_currImg = -1;
    m_images.clear();
    CStringArray list;
    getListFiles(aFolderName + _T("\\*.jpeg"), list);
    getListFiles(aFolderName + _T("\\*.jpg"), list);
    getListFiles(aFolderName + _T("\\*.bmp"), list);
    for (int i = 0; i < list.GetCount(); i++)
    {
        ImagePtr img = std::make_shared<CImage>();
        if (img->Load(list[i]) != S_OK)
            ::AfxMessageBox(CString(_T("Невозможно загрузить файл: ")) + list[i], MB_ICONERROR + MB_OK);
        else
            m_images.push_back(img);
    }
    if (m_images.size() > 0)
    {
        m_currImg = 0;
    }
    UpdateAllViews(nullptr);
}

ImagePtr CPicDoc::getCurrPic()
{
    if ((m_currImg >= 0) && (m_images.size() > 0))
        return m_images[m_currImg];
    else
        return nullptr;
}

void CPicDoc::showNextPic()
{
    if (m_images.size() == 0)
        m_currImg = -1;
    else
    {
        if (++m_currImg >= m_images.size())
            m_currImg = 0;
    }
    UpdateAllViews(NULL);
}
