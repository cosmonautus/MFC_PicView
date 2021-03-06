
// Pic.cpp: определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Pic.h"
#include "MainFrm.h"

#include "PicDoc.h"
#include "PicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicApp

BEGIN_MESSAGE_MAP(CPicApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPicApp::OnAppAbout)
    ON_COMMAND(ID_VIEW_PIC, &CPicApp::OnViewPic)
    ON_COMMAND(ID_VIEW_FOLDER, &CPicApp::OnViewFolder)
    ON_UPDATE_COMMAND_UI(ID_VIEW_PIC, &CPicApp::OnUpdateCmd)
    ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDER, &CPicApp::OnUpdateCmd)
END_MESSAGE_MAP()


// Создание CPicApp

CPicApp::CPicApp() noexcept
{
	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("Pic.AppID.NoVersion"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CPicApp

CPicApp theApp;


// Инициализация CPicApp

BOOL CPicApp::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	//LoadStdProfileSettings(4);  // Загрузите стандартные параметры INI-файла (включая MRU)


	// Зарегистрируйте шаблоны документов приложения.  Шаблоны документов
	//  выступают в роли посредника между документами, окнами рамок и представлениями
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPicDoc),
		RUNTIME_CLASS(CMainFrame),       // основное окно рамки SDI
		RUNTIME_CLASS(CPicView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;

	// Синтаксический разбор командной строки на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Команды диспетчеризации, указанные в командной строке.  Значение FALSE будет возвращено, если
	// приложение было запущено с параметром /RegServer, /Register, /Unregserver или /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// Обработчики сообщений CPicApp


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CPicApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Обработчики сообщений CPicApp

void CPicApp::OnViewPic()
{
    CFileDialog dlg(TRUE, nullptr, nullptr, 6UL, _T("Графические файлы|*.jpg;*.jpeg;*.bmp|"), this->GetMainWnd());
    if (dlg.DoModal() == IDOK)
    {
        getDocument()->viewPicFromFile(dlg.GetFolderPath() + _T("\\") + dlg.GetFileName());
    }
}

void CPicApp::OnViewFolder()
{
    CFolderPickerDialog dlg(nullptr, 0, this->GetMainWnd());
    if (dlg.DoModal() == IDOK)
    {
        //GetMainWnd()->SetTimer(0, 2000);
        getDocument()->viewPicFromFolder(dlg.GetFolderPath());
    }
}

void CPicApp::OnUpdateCmd(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

CPicDoc* CPicApp::getDocument()
{
    POSITION pos = GetFirstDocTemplatePosition();
    while (pos != NULL)
    {
        CDocTemplate* cd = GetNextDocTemplate(pos);
        if (cd != NULL)
        {
            POSITION DocPos = cd->GetFirstDocPosition();
            while (DocPos != NULL)
            {
                CDocument* cdoc = cd->GetNextDoc(DocPos);
                if (cdoc != NULL)
                {
                    return dynamic_cast<CPicDoc*>(cdoc);
                }
            }
        }
    }
    return nullptr;
}
