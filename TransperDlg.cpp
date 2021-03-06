
// TransperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Transper.h"
#include "TransperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransperDlg 对话框

TCHAR text_temp[1024], class_temp[1024];

CTransperDlg::CTransperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSPER_DIALOG, pParent)
	, text(_T(""))
	, cname(_T(""))
	, alpha(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, text);
	DDX_Text(pDX, IDC_EDIT2, cname);
	DDX_Slider(pDX, IDC_SLIDER1, alpha);
}

BEGIN_MESSAGE_MAP(CTransperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTransperDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTransperDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CTransperDlg::OnTRBNThumbPosChangingSlider1)
END_MESSAGE_MAP()


// CTransperDlg 消息处理程序

BOOL CTransperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	::CreateThread(NULL, NULL, [](LPVOID param)->DWORD {
		auto me = reinterpret_cast<CTransperDlg*>(param);
		POINT pt;
		while (true) {
			Sleep(100);
			GetCursorPos(&pt);
			auto handle = ::WindowFromPoint(pt);
			::GetWindowText(handle, text_temp, 1024);
			::GetClassName(handle, class_temp, 1024);
			::PostMessage(me->m_hWnd, WM_TIMER, 0, 0);
		};
		}, this, NULL, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTransperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTransperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTransperDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CTransperDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CTransperDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}

void CTransperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->text = text_temp;
	this->cname = class_temp;
	this->UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}


void CTransperDlg::OnTRBNThumbPosChangingSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
