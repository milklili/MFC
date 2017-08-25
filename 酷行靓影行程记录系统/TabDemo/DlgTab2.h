#pragma once


// CDlgTab2 对话框

class CDlgTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab2)

public:
	CDlgTab2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTab2();

// 对话框数据
	enum { IDD = IDD_DIALOG_TAB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList22(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list;
	//int InitListCtrlStyle(void);
	//int RefreshListCtrlData(void);
	afx_msg void OnBnClickedButtonLoadpic();
	afx_msg void OnBnClickedBigpic();
	CStatic m_picture;
	afx_msg void OnBnClickedButtonReadnote();
	afx_msg void OnBnClickedButtonSavenote();
	afx_msg void OnNMClickList22(NMHDR *pNMHDR, LRESULT *pResult);
};
