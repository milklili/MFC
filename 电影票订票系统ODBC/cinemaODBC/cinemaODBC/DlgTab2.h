#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new

// CDlgTab2 对话框

class CDlgTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab2)

public:
	CDlgTab2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTab2();

// 对话框数据
	enum { IDD = IDD_DLGTAB_CINEMA};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CDatabase m_db;//new
public:
	CListCtrl m_ListCinema;
	CString VariantToCString(CDBVariant*var);//new
	afx_msg void OnLvnItemchangedListCinema(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_EditTid;
	CString m_EditTname;
	CString m_EditAddress;
	afx_msg void OnBnClickedButtonSavecinema();
	afx_msg void OnBnClickedButtonDelecinema();
	afx_msg void OnNMDblclkListCinema(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAltercinema();
	virtual BOOL OnInitDialog();
};
