#pragma once
#include"exif.h"

/*#include "atlimage.h"
#include "istream"*/
static CString s;
// CDlgAfter 对话框

class CDlgAfter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAfter)

public:
	CDlgAfter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAfter();

// 对话框数据
	enum { IDD = IDD_DLGAFTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	EXIFINFO m_exifinfo;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButton1();
	bool PromptForFileName(CString& fileName, UINT nIDSTitle, DWORD dwFlags, bool bOpenFileDialog, int* pType);
	void ShowInfo(void);
	CStatic m_ShowPicture;

	afx_msg void OnBnClickedButtonAddpic();
};
