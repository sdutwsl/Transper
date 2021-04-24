
// TransperDlg.h: 头文件
//

#pragma once


// CTransperDlg 对话框
class CTransperDlg : public CDialogEx
{
// 构造
public:
	CTransperDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// 标题
	CString text;
	// 类名
	CString cname;
	// 透明度
	int alpha;
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTRBNThumbPosChangingSlider1(NMHDR* pNMHDR, LRESULT* pResult);
};
