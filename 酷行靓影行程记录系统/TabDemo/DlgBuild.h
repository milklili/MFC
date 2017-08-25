#pragma once
//CString workname;

// CDlgBuild 对话框

class CDlgBuild : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBuild)

public:
	CDlgBuild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBuild();

// 对话框数据
	enum { IDD = IDD_DLGBUILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
