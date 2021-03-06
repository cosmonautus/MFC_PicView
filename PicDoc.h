
// PicDoc.h: интерфейс класса CPicDoc 
//


#pragma once
#include <memory>
#include <vector>

using ImagePtr = std::shared_ptr<CImage>;

class CPicDoc : public CDocument
{
protected: // создать только из сериализации
	CPicDoc() noexcept;
	DECLARE_DYNCREATE(CPicDoc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Реализация
public:
	virtual ~CPicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    int m_currImg = -1;
    std::vector<ImagePtr> m_images;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
    void viewPicFromFile(const CString aFileName);
    void viewPicFromFolder(const CString aFolderName);
    ImagePtr getCurrPic();
    void showNextPic();
};
