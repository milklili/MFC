#pragma once


// CDlgBefore 对话框

class CDlgBefore : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBefore)

public:
	CDlgBefore(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBefore();

// 对话框数据
	enum { IDD = IDD_DLGBEFORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csID;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditId();
	afx_msg void OnEnChangeEdit1();
};
